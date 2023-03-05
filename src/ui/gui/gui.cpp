#include "../../../includes/ui/gui/gui.hpp"
#include "../../../includes/gameruler.hpp"
#include "../../../includes/pieces/piece.hpp"
#include <experimental/filesystem>

struct RGBA
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
};

RGBA getColorFromHEX(Uint32 hex)
{
    RGBA rgb;
    rgb.r = (hex >> 16) & 0xFF;
    rgb.g = (hex >> 8) & 0xFF;
    rgb.b = hex & 0xFF;
    return rgb;
}

RGBA tileColor(int i, int j)
{
    RGBA color;
    if ((i + j) % 2 == 0)
        color = getColorFromHEX(0x6D523B);
    else
        color = getColorFromHEX(0x90826c);
    return color;
}

GUI::GUI() : Game(), m_ltexture{LTexture()}, m_window{nullptr}, m_renderer{nullptr}
{
    // get current directory
    init();
    m_ltexture.loadTextures(this->m_renderer);
    // set anti-aliasing
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

GUI::~GUI() {}

void GUI::run()
{
    std::cout << *this;
    SDL_Event event;
    SDL_PollEvent(&event);
    render();
    while (SDL_WaitEvent(&event))
    {
        render();
        handleEvents(&event);
    }
}

void GUI::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    else
    {
        m_window = SDL_CreateWindow("chess-cpp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
        if (m_window)
        {
            this->m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
            if (this->m_renderer)
            {
                SDL_SetRenderDrawColor(this->m_renderer, 255, 255, 255, 255);
            }
            else
            {
                std::cout << "Renderer could not be created" << std::endl;
                SDL_DestroyRenderer(this->m_renderer);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            std::cout << "Window could not be created" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (TTF_Init() == -1)
        {
            std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            m_font = TTF_OpenFont("ttf/Inter-SemiBold.otf", 110);
            if (m_font == NULL)
            {
                std::cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

void GUI::update()
{
    render();
    this->updateStatus();
    std::cout << "Turn: " << this->getNumTurns() << std::endl;
    std::cout << "Check: " << (this->getCheck() ? "TRUE" : "FALSE ") << std::endl;
}

void GUI::handleEvents(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        this->end();
        break;
    case SDL_MOUSEBUTTONDOWN:
    {
        grabPiece();
        break;
    }
    case SDL_MOUSEBUTTONUP:
        if (movePiece())
        {
            update();
            if (this->getCheckMate())
                this->end();
            else if (this->getStaleMate())
                this->end();
            this->m_selectedPiece = nullptr;
            break;
        }
        break;
    }
}

void GUI::followMouse()
{
    static SDL_Rect rect;
    if (this->m_selectedPiece != nullptr)
    {
        // draw a little rectangle that follows the mouse
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        // printf("x: %d y: %d\n", mouseX, mouseY);
        //  center the rect on the middle of the mouse
        rect.x = mouseX - 35;
        rect.y = mouseY - 35;
        rect.w = 75;
        rect.h = 75;

        // copy the texture of the selected piece to the rect
        std::string key;
        key.push_back(tolower(this->m_selectedPiece->getType()));
        key.push_back(this->m_selectedPiece->getColor() == Color::WHITE ? 'w' : 'b');
        if (SDL_RenderCopy(this->m_renderer, this->m_ltexture.getTexture(key), NULL, &rect) < 0)
        {
            std::cout << "SDL could not copy texture! SDL_Error: " << SDL_GetError() << std::endl;
            exit(1);
        }
    }
}

void GUI::render()
{
    SDL_RenderClear(this->m_renderer);
    drawBoard();
    drawPieces();
    // followMouse();
    this->showPossibleMoves();
    SDL_RenderPresent(this->m_renderer);
}

void GUI::end()
{
    TTF_CloseFont(this->m_font);
    TTF_Quit();
    SDL_DestroyRenderer(this->m_renderer);
    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();
}

void GUI::drawBoard()
{
    SDL_SetRenderDrawColor(this->m_renderer, 0, 0, 0, 255);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            RGBA color = tileColor(i, j);
            SDL_SetRenderDrawColor(this->m_renderer, color.r, color.g, color.b, 255);
            SDL_Rect rect = {i * this->getSizeSquare(), j * this->getSizeSquare(), this->getSizeSquare(),
                             this->getSizeSquare()};
            SDL_RenderFillRect(this->m_renderer, &rect);
            // draw text (a-h, 1-8)
            if (i == 7 || j == 7)
                drawTextInTile(i, j);
        }
    }
}

void GUI::drawTextInTile(int i, int j)
{
    int textWidth = 0;
    int textHeight = 0;
    std::string text = i == 7 ? std::to_string(8 - j) : j == 7 ? std::string(1, 'a' + i) : "";
    SDL_Color textColor = {240, 240, 240};
    SDL_Surface *textSurface = TTF_RenderText_Blended(this->m_font, text.c_str(), textColor);
    if (textSurface == NULL)
    {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(this->m_renderer, textSurface);
    if (textTexture == NULL)
    {
        std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError()
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_Rect textRect;
    if (SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight) < 0)
    {
        std::cout << "Unable to query texture! SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    // display number on the right side of the tile in the last column
    if (i == 7)
        textRect = {i * this->getSizeSquare() + this->getSizeSquare() - 8, j * this->getSizeSquare(),
                    (int)(textWidth / 8), (int)(textHeight / 8)};
    // display letter on the bottom right of the tile in the last row
    else if (j == 7)
        textRect = {(i + 1) * this->getSizeSquare() - (int)(textWidth / 8) - 2,
                    j * this->getSizeSquare() + this->getSizeSquare() - 17, (int)(textWidth / 8),
                    (int)(textHeight / 8)};
    if (SDL_RenderCopy(this->m_renderer, textTexture, NULL, &textRect) < 0)
    {
        std::cout << "SDL could not copy texture! SDL_Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void GUI::drawPieces()
{
    for (int i = 8; i > 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->getBoard().getArray()[j][i - 1].getPiece() != nullptr)
            {
                Color pieceColor = (Color)this->getBoard().getArray()[j][i - 1].getPiece()->getColor();
                char pieceType = this->getBoard().getArray()[j][i - 1].getPiece()->getType();
                std::string key;
                key.push_back(tolower(pieceType));
                key += pieceColor == Color::WHITE ? "w" : "b";

                // coordinates of rect needs to be relative to the window
                SDL_Rect rect = {j * this->getSizeSquare(), (8 - i) * this->getSizeSquare(),
                                 this->getSizeSquare(), this->getSizeSquare()};
                if (SDL_RenderCopy(this->m_renderer, this->m_ltexture.getTexture(key), NULL, &rect) != 0)
                {
                    std::cout << "Error rendering texture: " << SDL_GetError() << std::endl;
                    std::cout << key << std::endl;
                    std::cout << this->m_ltexture.getTexture(key) << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

void GUI::grabPiece()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    // get the coordinates of the piece that was clicked according to the screen
    int i = x / this->getSizeSquare();
    int j = y / this->getSizeSquare();
    // convert i and j to the coordinates of the board
    j = 7 - j;
    if (this->getPieceHandler().getPieceAt(*this, i, j) != nullptr &&
        this->getPieceHandler().getPieceAt(*this, i, j)->getColor() == this->getTurn())
    {
        this->m_selectedPiece = this->getPieceHandler().getPieceAt(*this, i, j);
        std::cout << *(this->m_selectedPiece) << std::endl;
    }
}

void GUI::showPossibleMoves()
{
    if (this->m_selectedPiece == nullptr)
        return;
    std::vector<std::pair<int, int>> moves =
        this->m_selectedPiece->getValidMoves(this->getBoard().getArray());
    for (auto move : moves)
    {
        SDL_Rect rect = {move.first * this->getSizeSquare(), (7 - move.second) * this->getSizeSquare(),
                         this->getSizeSquare(), this->getSizeSquare()};
        // rect is transparent
        SDL_SetRenderDrawBlendMode(this->m_renderer, SDL_BLENDMODE_BLEND);
        RGBA move_possible = getColorFromHEX(0x2465ff);
        SDL_SetRenderDrawColor(this->m_renderer, move_possible.r, move_possible.g, move_possible.b, 100);
        SDL_RenderFillRect(this->m_renderer, &rect);
    }
}

void drawCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    while (offsety >= offsetx)
    {
        SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);
        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx++;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety--;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety--;
            offsetx++;
        }
    }
    // fill it
    SDL_RenderDrawLine(renderer, x - radius, y, x + radius, y);
    for (int i = 1; i < radius; i++)
    {
        SDL_RenderDrawLine(renderer, x - radius, y + i, x + radius, y + i);
        SDL_RenderDrawLine(renderer, x - radius, y - i, x + radius, y - i);
    }
}

bool GUI::movePiece()
{
    // place grabbed piece at mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);
    int i = x / this->getSizeSquare();
    int j = y / this->getSizeSquare();
    // convert i and j to the coordinates of the board
    j = 7 - j;
    if (this->m_selectedPiece != nullptr &&
        this->getPieceHandler().movePieceAt(*this, this->m_selectedPiece, i, j) &&
        this->m_selectedPiece->getColor() == this->getTurn())
    {
        this->m_selectedPiece = nullptr;
        return true;
    }
    return false;
}

int GUI::getWidth() const
{
    int w;
    SDL_GetWindowSize(this->m_window, &w, NULL);
    return w;
}

int GUI::getHeight() const
{
    int h;
    SDL_GetWindowSize(this->m_window, NULL, &h);
    return h;
}

int GUI::getSizeSquare() const { return this->getWidth() / 8; }

void GUI::promotePawn(std::shared_ptr<Piece> &toPromote) {}
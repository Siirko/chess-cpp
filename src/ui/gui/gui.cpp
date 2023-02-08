#include "../../../includes/ui/gui/gui.hpp"
#include "../../../includes/gameruler.hpp"
#include "../../../includes/pieces/piece.hpp"
#include <experimental/filesystem>

GUI::GUI()
    : Game(), m_ltexture{LTexture()}, m_window{nullptr}, m_renderer{nullptr}, m_sourceRectangle{nullptr}
{
    // get current directory
    init();
    m_ltexture.loadTextures(this->m_renderer);
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
            this->m_renderer = SDL_CreateRenderer(m_window, -1, 0);
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
    }
}

void GUI::update()
{
    render();
    this->updateTurn();
    this->updateNumTurns();
    std::cout << *this;
    this->setCheck(
        GameRuler::getInstance().isKingInCheck(this->getBoard().getBoard(), (Color)this->getTurn()));
    this->setCheckMate(
        GameRuler::getInstance().isKingInCheckMate(this->getBoard().getBoard(), (Color)this->getTurn()));
    this->setStaleMate(
        GameRuler::getInstance().isKingInStaleMate(this->getBoard().getBoard(), (Color)this->getTurn()));
}

void GUI::handleEvents(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        this->clean();
        break;
    case SDL_MOUSEMOTION:
        render();
        break;
    case SDL_MOUSEBUTTONDOWN:
        grabPiece();
        break;
    case SDL_MOUSEBUTTONUP:
        if (movePiece())
        {
            update();
            if (this->getCheckMate())
                this->clean();
            if (this->getStaleMate())
                this->clean();
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
        printf("x: %d y: %d\n", mouseX, mouseY);
        // center the rect on the middle of the mouse
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
    followMouse();
    this->showPossibleMoves();
    SDL_RenderPresent(this->m_renderer);
}

void GUI::clean()
{
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
            if ((i + j) % 2 == 0)
                SDL_SetRenderDrawColor(this->m_renderer, 144, 130, 109, 255);
            else
                SDL_SetRenderDrawColor(this->m_renderer, 109, 82, 59, 255);

            SDL_Rect rect = {i * 75, j * 75, 75, 75};
            SDL_RenderFillRect(this->m_renderer, &rect);
        }
    }
}

void GUI::drawPieces()
{
    for (int i = 8; i > 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->getBoard().getBoard()[j][i - 1].getPiece() != nullptr)
            {
                Color pieceColor = (Color)this->getBoard().getBoard()[j][i - 1].getPiece()->getColor();
                char pieceType = this->getBoard().getBoard()[j][i - 1].getPiece()->getType();
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
        m_sourceRectangle = new SDL_Rect();
        m_sourceRectangle->x = i * this->getSizeSquare();
        m_sourceRectangle->y = j * this->getSizeSquare();
        m_sourceRectangle->w = this->getSizeSquare();
        m_sourceRectangle->h = this->getSizeSquare();
        this->m_selectedPiece = this->getPieceHandler().getPieceAt(*this, i, j);
        std::cout << *(this->m_selectedPiece) << std::endl;
    }
}

void GUI::showPossibleMoves()
{
    if (this->m_selectedPiece == nullptr)
        return;
    std::vector<std::pair<int, int>> moves =
        this->m_selectedPiece->getValidMoves(this->getBoard().getBoard());
    for (auto move : moves)
    {
        SDL_Rect rect = {move.first * this->getSizeSquare(), (7 - move.second) * this->getSizeSquare(),
                         this->getSizeSquare(), this->getSizeSquare()};
        // rect is transparent
        SDL_SetRenderDrawBlendMode(this->m_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(this->m_renderer, 0, 0, 255, 100);
        SDL_RenderFillRect(this->m_renderer, &rect);
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
        delete m_sourceRectangle;
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
#include "../../../includes/ui/gui/gui.hpp"
#include "../../../includes/gameruler.hpp"
#include "../../../includes/pieces/piece.hpp"

GUI::GUI()
    : Game(), m_ltexture{LTexture("/home/yanovskyy/Documents/projects/chess-cpp/tex")}, m_window{nullptr},
      m_renderer{nullptr}, m_sourceRectangle{nullptr}
{
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
        handleEvents(&event);
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
            break;
        }
        break;
    }
}

void GUI::render()
{
    SDL_RenderClear(this->m_renderer);
    drawBoard();
    drawPieces();
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
                SDL_Rect rect = {j * 75, (8 - i) * 75, 75, 75};
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
    int i = x / 75;
    int j = y / 75;
    // convert i and j to the coordinates of the board
    j = 7 - j;
    if (this->getPieceHandler().getPieceAt(*this, i, j) != nullptr &&
        this->getPieceHandler().getPieceAt(*this, i, j)->getColor() == this->getTurn())
    {
        m_sourceRectangle = new SDL_Rect();
        m_sourceRectangle->x = i * 75;
        m_sourceRectangle->y = j * 75;
        m_sourceRectangle->w = 75;
        m_sourceRectangle->h = 75;
        this->m_selectedPiece = this->getPieceHandler().getPieceAt(*this, i, j);
        std::cout << *(this->m_selectedPiece) << std::endl;
    }
}

bool GUI::movePiece()
{
    // place grabbed piece at mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);
    int i = x / 75;
    int j = y / 75;
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
#include "../../../includes/ui/gui/gui.hpp"
#include "../../../includes/gameruler.hpp"
#include "../../../includes/pieces/piece.hpp"

GUI::GUI() : Game()
{
    m_isRunning = false;
    m_window = nullptr;
    m_renderer = nullptr;
    m_texture = nullptr;
    m_sourceRectangle = nullptr;
    m_destinationRectangle = nullptr;
    init();
}

GUI::~GUI() { clean(); }

void GUI::run()
{
    while (m_isRunning)
    {
        handleEvents();
        update();
        render();
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
            m_renderer = SDL_CreateRenderer(m_window, -1, 0);
            if (m_renderer)
            {
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
            }
            else
            {
                std::cout << "Renderer could not be created" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            std::cout << "Window could not be created" << std::endl;
            exit(EXIT_FAILURE);
        }
        m_isRunning = true;
    }
}

void GUI::update() { render(); }

void GUI::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_KEYDOWN:
        m_isRunning = false;
        break;
    default:
        break;
    }
}

void GUI::render()
{
    SDL_RenderClear(m_renderer);
    drawBoard();
    drawPieces();
    SDL_RenderPresent(m_renderer);
}

void GUI::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void GUI::drawBoard()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                SDL_SetRenderDrawColor(m_renderer, 144, 130, 109, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(m_renderer, 109, 82, 59, 255);
            }
            SDL_Rect rect = {i * 75, j * 75, 75, 75};
            SDL_RenderFillRect(m_renderer, &rect);
        }
    }
}

std::string getPiecePathTex(PieceType pieceType, Color pieceColor)
{
    std::string woorking_path = SDL_GetBasePath();
    // remove build/ from the path
    woorking_path = woorking_path.substr(0, woorking_path.size() - 6);
    std::string piecePath = woorking_path + "tex/";
    switch (pieceType)
    {
    case PieceType::PAWN:
        piecePath += "pawn";
        break;
    case PieceType::TOWER:
        piecePath += "tower";
        break;
    case PieceType::KNIGHT:
        piecePath += "knight";
        break;
    case PieceType::BISHOP:
        piecePath += "bishop";
        break;
    case PieceType::QUEEN:
        piecePath += "queen";
        break;
    case PieceType::KING:
        piecePath += "roi";
        break;
    default:
        break;
    }
    piecePath += pieceColor == Color::WHITE ? "_white.png" : "_black.png";
    return piecePath;
}

void GUI::drawPieces()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->getBoard().getBoard()[i][j].getPiece() != nullptr)
            {
                char pieceType = this->getBoard().getBoard()[i][j].getPiece()->getType();
                Color pieceColor = (Color)this->getBoard().getBoard()[i][j].getPiece()->getColor();
                std::string piecePath = getPiecePathTex((PieceType)pieceType, pieceColor);
                SDL_Surface *surface = IMG_Load(piecePath.c_str());
                if (surface == nullptr)
                {
                    std::cout << "Error loading image: " << IMG_GetError() << std::endl;
                    exit(EXIT_FAILURE);
                }
                SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
                if (texture == nullptr)
                {
                    std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
                    exit(EXIT_FAILURE);
                }
                SDL_Rect rect = {i * 75, j * 75, 75, 75};
                SDL_RenderCopy(m_renderer, texture, NULL, &rect);
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);
            }
        }
    }
}
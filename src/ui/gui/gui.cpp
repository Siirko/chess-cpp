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
    initTextureMap();
}

GUI::~GUI() { clean(); }

void GUI::run()
{
    std::cout << *this;
    m_isRunning = true;
    SDL_Event event;
    SDL_PollEvent(&event);
    // wait next input from user
    while (SDL_WaitEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_MOUSEBUTTONDOWN:
            grabPiece();
            break;
        case SDL_MOUSEBUTTONUP:
            movePiece();
            break;
        }
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
    case SDL_MOUSEBUTTONDOWN:
        grabPiece();
        break;
    case SDL_MOUSEBUTTONUP:
        movePiece();
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

void GUI::initTextureMap()
{
    std::vector<std::string> piecePaths;
    piecePaths.push_back(getPiecePathTex(PieceType::PAWN, Color::WHITE));
    piecePaths.push_back(getPiecePathTex(PieceType::TOWER, Color::WHITE));
    piecePaths.push_back(getPiecePathTex(PieceType::KNIGHT, Color::WHITE));
    piecePaths.push_back(getPiecePathTex(PieceType::BISHOP, Color::WHITE));
    piecePaths.push_back(getPiecePathTex(PieceType::QUEEN, Color::WHITE));
    piecePaths.push_back(getPiecePathTex(PieceType::KING, Color::WHITE));

    piecePaths.push_back(getPiecePathTex(PieceType::PAWN, Color::BLACK));
    piecePaths.push_back(getPiecePathTex(PieceType::TOWER, Color::BLACK));
    piecePaths.push_back(getPiecePathTex(PieceType::KNIGHT, Color::BLACK));
    piecePaths.push_back(getPiecePathTex(PieceType::BISHOP, Color::BLACK));
    piecePaths.push_back(getPiecePathTex(PieceType::QUEEN, Color::BLACK));
    piecePaths.push_back(getPiecePathTex(PieceType::KING, Color::BLACK));

    for (auto path : piecePaths)
    {
        SDL_Surface *surface = IMG_Load(path.c_str());
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
        std::string key = path.find("white") != std::string::npos ? "white" : "black";
        key += path.find("pawn") != std::string::npos     ? "pawn"
               : path.find("tower") != std::string::npos  ? "tower"
               : path.find("knight") != std::string::npos ? "knight"
               : path.find("bishop") != std::string::npos ? "bishop"
               : path.find("queen") != std::string::npos  ? "queen"
                                                          : "king";
        std::cout << key << std::endl;
        m_textureMap.insert(std::pair<std::string, SDL_Texture *>(key, texture));
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
                char pieceType = this->getBoard().getBoard()[j][i - 1].getPiece()->getType();
                Color pieceColor = (Color)this->getBoard().getBoard()[j][i - 1].getPiece()->getColor();
                std::string key = pieceColor == Color::WHITE ? "white" : "black";
                key += (PieceType)pieceType == PieceType::PAWN     ? "pawn"
                       : (PieceType)pieceType == PieceType::TOWER  ? "tower"
                       : (PieceType)pieceType == PieceType::KNIGHT ? "knight"
                       : (PieceType)pieceType == PieceType::BISHOP ? "bishop"
                       : (PieceType)pieceType == PieceType::QUEEN  ? "queen"
                                                                   : "king";

                // coordinates of rect needs to be relative to the window
                SDL_Rect rect = {j * 75, (8 - i) * 75, 75, 75};
                if (SDL_RenderCopy(m_renderer, m_textureMap[key], NULL, &rect) != 0)
                {
                    std::cout << "Error rendering texture: " << SDL_GetError() << std::endl;
                    std::cout << key << std::endl;
                    std::cout << m_textureMap[key] << std::endl;
                    std::cout << m_textureMap.size() << std::endl;
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
    if (this->getPieceHandler().getPieceAt(*this, i, j) != nullptr)
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

void GUI::movePiece()
{
    // place grabbed piece at mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);
    int i = x / 75;
    int j = y / 75;
    // convert i and j to the coordinates of the board
    j = 7 - j;
    if (this->getPieceHandler().movePieceAt(*this, this->m_selectedPiece, i, j))
    {
        this->m_selectedPiece = nullptr;
        delete m_sourceRectangle;
    }
}
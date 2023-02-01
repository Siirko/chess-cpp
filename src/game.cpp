#include "../includes/game.hpp"
#include "../includes/gameruler.hpp"
#include "../includes/parser.hpp"
#include "../includes/pieces/bishop.hpp"
#include "../includes/pieces/knight.hpp"
#include "../includes/pieces/pawn.hpp"
#include "../includes/pieces/queen.hpp"
#include "../includes/pieces/roi.hpp"
#include "../includes/pieces/tower.hpp"
#include <iostream>
#include <regex>
#include <string>

// TODO:: Refactor the big shit i've made, do Steelmate, refactor Board display
// game too

Game::Game() : board{}, turn{1}, num_turns{0}, check{false}, checkMate{false}, staleMate{false} { init(); }

Game::~Game() { std::cout << "Game destructor" << std::endl; }

void Game::init()
{
    std::cout << "Game init" << std::endl;
    this->board = Board();
    this->black_eaten_pieces = std::vector<std::shared_ptr<Piece>>();
    this->white_eaten_pieces = std::vector<std::shared_ptr<Piece>>();
    this->forsythGeneration("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    GameRuler::getInstance().setGame(this);
}

std::shared_ptr<Roi> Game::getWhiteKing() const
{
    for (auto piece : this->alive_pieces)
    {
        if (piece->getColor() == Color::WHITE && piece->getType() == PieceType::KING)
            return std::dynamic_pointer_cast<Roi>(piece);
    }
    throw std::runtime_error("No white king found");
}

std::shared_ptr<Roi> Game::getBlackKing() const
{
    for (auto piece : this->alive_pieces)
    {
        if (piece->getColor() == Color::BLACK && piece->getType() == PieceType::KING)
            return std::dynamic_pointer_cast<Roi>(piece);
    }
    throw std::runtime_error("No black king found");
}

void Game::printInfo()
{
    std::cout << "White eaten pieces: " << this->white_eaten_pieces.size() << std::endl;
    std::cout << "Black eaten pieces: " << this->black_eaten_pieces.size() << std::endl;
    std::cout << "Turn: ";
    if (this->turn == 0)
        std::cout << "BLACK" << std::endl;
    else
        std::cout << "WHITE" << std::endl;
}

void Game::run()
{
    std::cout << "Game running" << std::endl;
    this->board.printBoard();
    this->printInfo();
    std::string input;
    do
    {
        if (input.empty())
            continue;
        Parser::UpdateCoords coords = Parser::parseInput(input);
        std::shared_ptr<Piece> piece = this->choosePiece(coords.from.x, coords.from.y);
        if (piece != nullptr && piece->getColor() == this->turn)
        {
            if (this->movePieceAt(piece, coords.to.x, coords.to.y))
            {
                this->turn = (this->turn + 1) % 2;
                this->num_turns++;
                this->board.printBoard();
                this->printInfo();
                this->check =
                    GameRuler::getInstance().isKingInCheck(this->board.getBoard(), (Color)this->turn);
                this->checkMate =
                    GameRuler::getInstance().isKingInCheckMate(this->board.getBoard(), (Color)this->turn);
                this->staleMate =
                    GameRuler::getInstance().isKingInStaleMate(this->board.getBoard(), (Color)this->turn);
                if (this->checkMate)
                    break;
                if (this->staleMate)
                    break;
            }
        }
        else if (piece == nullptr)
        {
            std::cout << "No piece at this position" << std::endl;
        }
        else if (piece->getColor() != this->turn)
        {
            std::cout << (piece->getColor() == Color::WHITE ? "BLACK" : "WHITE") << " turn" << std::endl;
        }
    } while ((input = Parser::getInput()) != "/exit" && this->checkMate != true);
    if (this->checkMate)
    {
        std::string color = this->turn == Color::BLACK ? "WHITE" : "BLACK";
        std::cout << "Checkmate, " << color << " Won !" << std::endl;
    }
    else if (this->staleMate)
        std::cout << "Stalemate, Draw !" << std::endl;
}

bool Game::movePieceAt(std::shared_ptr<Piece> piece, int x, int y)
{
    bool valid = true;
    try
    {
        std::shared_ptr<Piece> eatenPiece = this->board.movePiece(piece, x, y);
        if (eatenPiece != nullptr && eatenPiece->getType() != PieceType::KING)
        {
            if (eatenPiece->getColor() == Color::WHITE)
                this->black_eaten_pieces.push_back(eatenPiece);
            else
                this->white_eaten_pieces.push_back(eatenPiece);
            this->removeAlivePiece(eatenPiece);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        valid = false;
    }
    return valid;
}

void Game::forsythGeneration(std::string fen)
{
    int x = 0;
    int y = 0;
    for (size_t i = 0; i < fen.length(); i++)
    {
        if (fen[i] == '/')
        {
            x = 0;
            y++;
        }
        else if (fen[i] >= '1' && fen[i] <= '8')
        {
            x += fen[i] - '0';
        }
        else
        {
            std::shared_ptr<Piece> piece = nullptr;
            switch (fen[i])
            {
            case 'p':
                piece = std::make_shared<Pawn>(x, y, Color::WHITE);
                break;
            case 'P':
                piece = std::make_shared<Pawn>(x, y, Color::BLACK);
                break;
            case 'r':
                piece = std::make_shared<Tower>(x, y, Color::WHITE);
                break;
            case 'R':
                piece = std::make_shared<Tower>(x, y, Color::BLACK);
                break;
            case 'n':
                piece = std::make_shared<Knight>(x, y, Color::WHITE);
                break;
            case 'N':
                piece = std::make_shared<Knight>(x, y, Color::BLACK);
                break;
            case 'b':
                piece = std::make_shared<Bishop>(x, y, Color::WHITE);
                break;
            case 'B':
                piece = std::make_shared<Bishop>(x, y, Color::BLACK);
                break;
            case 'q':
                piece = std::make_shared<Queen>(x, y, Color::WHITE);
                break;
            case 'Q':
                piece = std::make_shared<Queen>(x, y, Color::BLACK);
                break;
            case 'k':
                piece = std::make_shared<Roi>(x, y, Color::WHITE);
                break;
            case 'K':
                piece = std::make_shared<Roi>(x, y, Color::BLACK);
                break;
            default:
                break;
            }
            if (piece != nullptr)
            {
                this->board.setPiece(piece);
                this->addAlivePiece(piece);
                x++;
            }
        }
    }
}

std::shared_ptr<Piece> Game::choosePiece(int x, int y)
{
    auto piece = this->board.getTile(x, y).getPiece();
    return piece != nullptr ? piece : nullptr;
}

std::vector<std::shared_ptr<Piece>> Game::getAlivePieces() const { return this->alive_pieces; }

void Game::addAlivePiece(std::shared_ptr<Piece> piece) { this->alive_pieces.push_back(piece); }

void Game::removeAlivePiece(std::shared_ptr<Piece> piece)
{
    this->alive_pieces.erase(std::remove(this->alive_pieces.begin(), this->alive_pieces.end(), piece),
                             this->alive_pieces.end());
}
#include "../includes/game.hpp"
#include "../includes/gamewatcher.hpp"
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

Game::Game() : board{}, turn{1}, num_turns{0}, check{false}, checkMate{false} { init(); }

Game::~Game() { std::cout << "Game destructor" << std::endl; }

void Game::init()
{
    std::cout << "Game init" << std::endl;
    this->board = Board();
    this->black_eaten_pieces = std::vector<std::shared_ptr<Piece>>();
    this->white_eaten_pieces = std::vector<std::shared_ptr<Piece>>();
    this->forythGeneration("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

std::string getInput()
{
    std::string input;
    std::cout << "Enter your move: ";
    std::cin >> input;
    if (input == "/exit")
        return input;
    std::regex pattern("[a-h][1-8][a-h][1-8]");
    if (!std::regex_match(input, pattern))
    {
        std::cout << "Invalid input" << std::endl;
        return "";
    }
    return input;
}

void Game::printInfo()
{
    std::cout << "White eaten pieces: " << this->white_eaten_pieces.size() << std::endl;
    std::cout << "Black eaten pieces: " << this->black_eaten_pieces.size() << std::endl;
    std::cout << "Turn: ";
    if (this->turn == 0)
    {
        std::cout << "BLACK" << std::endl;
    }
    else
    {
        std::cout << "WHITE" << std::endl;
    }
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
        int x = input[0] - 'a';
        int y = input[1] - '1';
        int x2 = input[2] - 'a';
        int y2 = input[3] - '1';
        std::shared_ptr<Piece> piece = this->choosePiece(x, y);
        if (piece != nullptr && piece->getColor() == this->turn)
        {
            if (this->play_piece_at(piece, x2, y2))
            {
                this->turn = (this->turn + 1) % 2;
                this->num_turns++;
                this->board.printBoard();
                this->printInfo();
                this->check =
                    GameWatcher::getInstance().isKingInCheck(this->board.getBoard(), (Color)this->turn);
                this->checkMate =
                    GameWatcher::getInstance().isKingInCheckMate(this->board.getBoard(), (Color)this->turn);
                if (this->checkMate)
                    break;
            }
        }
        else
        {
            std::cout << "Invalid move" << std::endl;
        }
    } while ((input = getInput()) != "/exit" && this->checkMate != true);
    if (this->checkMate)
    {
        std::string color = this->turn == Color::BLACK ? "WHITE" : "BLACK";
        std::cout << "Checkmate, " << color << " Won !" << std::endl;
    }
    std::cout << "end" << std::endl;
}

bool Game::play_piece_at(std::shared_ptr<Piece> piece, int x, int y)
{
    bool valid = true;
    try
    {
        std::shared_ptr<Piece> eatenPiece = this->board.movePiece(piece, x, y);
        if (eatenPiece != nullptr && eatenPiece->getType() != 'R')
        {
            if (eatenPiece->getColor() == Color::WHITE)
            {
                this->black_eaten_pieces.push_back(eatenPiece);
            }
            else
            {
                this->white_eaten_pieces.push_back(eatenPiece);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        valid = false;
    }
    return valid;
}

void Game::forythGeneration(std::string fen)
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
                x++;
            }
        }
    }
    GameWatcher::getInstance().setWhiteKing(std::dynamic_pointer_cast<Roi>(this->choosePiece(4, 0)));
    GameWatcher::getInstance().setBlackKing(std::dynamic_pointer_cast<Roi>(this->choosePiece(4, 7)));
}

std::shared_ptr<Piece> Game::choosePiece(int x, int y)
{
    auto piece = this->board.getTile(x, y).getPiece();
    return piece != nullptr ? piece : nullptr;
}
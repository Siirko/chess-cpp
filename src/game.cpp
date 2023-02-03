#include "../includes/game.hpp"
#include "../includes/gameruler.hpp"
#include "../includes/parser.hpp"
#include "../includes/piecehandler.hpp"
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
    this->piece_handler = PieceHandler();
    this->piece_handler.forsythGeneration(*this, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
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
        std::shared_ptr<Piece> piece = this->piece_handler.getPieceAt(*this, coords.from.x, coords.from.y);
        if (piece != nullptr && piece->getColor() == this->turn)
        {
            if (this->piece_handler.movePieceAt(*this, piece, coords.to.x, coords.to.y))
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

std::vector<std::shared_ptr<Piece>> Game::getAlivePieces() const { return this->alive_pieces; }

void Game::addAlivePiece(std::shared_ptr<Piece> piece) { this->alive_pieces.push_back(piece); }

void Game::removeAlivePiece(std::shared_ptr<Piece> piece)
{
    this->alive_pieces.erase(std::remove(this->alive_pieces.begin(), this->alive_pieces.end(), piece),
                             this->alive_pieces.end());
}

Board &Game::getBoard() { return this->board; }

std::vector<std::shared_ptr<Piece>> &Game::getWhiteEatenPieces() { return this->white_eaten_pieces; }

std::vector<std::shared_ptr<Piece>> &Game::getBlackEatenPieces() { return this->black_eaten_pieces; }

PieceHandler &Game::getPieceHandler() { return this->piece_handler; }
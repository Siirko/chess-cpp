#include "../includes/game.hpp"
#include "../includes/gameruler.hpp"
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

Game::Game()
    : board{Board()},
      piece_handler{PieceHandler()}, turn{1}, num_turns{0}, check{false}, checkMate{false}, staleMate{false}
{
    init();
}

Game::~Game() { std::cout << "Game destructor" << std::endl; }

void Game::init()
{
    std::cout << "Game init" << std::endl;
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

std::vector<std::shared_ptr<Piece>> Game::getAlivePieces() const { return this->alive_pieces; }

void Game::addAlivePiece(std::shared_ptr<Piece> piece) { this->alive_pieces.push_back(piece); }

void Game::removeAlivePiece(std::shared_ptr<Piece> piece)
{
    this->alive_pieces.erase(std::remove(this->alive_pieces.begin(), this->alive_pieces.end(), piece),
                             this->alive_pieces.end());
}

Board &Game::getBoard() { return this->board; }

Board Game::getBoard() const { return this->board; }

std::vector<std::shared_ptr<Piece>> &Game::getWhiteEatenPieces() { return this->white_eaten_pieces; }

std::vector<std::shared_ptr<Piece>> &Game::getBlackEatenPieces() { return this->black_eaten_pieces; }

PieceHandler &Game::getPieceHandler() { return this->piece_handler; }

int Game::getTurn() const { return this->turn; }

void Game::updateTurn() { this->turn = (this->turn + 1) % 2; }

int Game::getNumTurns() const { return this->num_turns; }

void Game::updateNumTurns() { this->num_turns++; }

bool Game::getCheck() const { return this->check; }

void Game::setCheck(bool check) { this->check = check; }

bool Game::getCheckMate() const { return this->checkMate; }

void Game::setCheckMate(bool checkMate) { this->checkMate = checkMate; }

bool Game::getStaleMate() const { return this->staleMate; }

void Game::setStaleMate(bool staleMate) { this->staleMate = staleMate; }

std::ostream &operator<<(std::ostream &os, const Game &game)
{
    os << game.getBoard();
    os << "White eaten pieces: " << game.white_eaten_pieces.size() << std::endl;
    os << "Black eaten pieces: " << game.black_eaten_pieces.size() << std::endl;
    os << "Turn: " << (game.turn == 0 ? "BLACK" : "WHITE") << std::endl;
    return os;
}
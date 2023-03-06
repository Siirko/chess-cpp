#include "../includes/game.hpp"
#include "../includes/gameruler.hpp"
#include "../includes/piecehandler.hpp"
#include "../includes/pieces/bishop.hpp"
#include "../includes/pieces/king.hpp"
#include "../includes/pieces/knight.hpp"
#include "../includes/pieces/pawn.hpp"
#include "../includes/pieces/queen.hpp"
#include "../includes/pieces/rook.hpp"
#include <iostream>
#include <regex>
#include <string>

Game::Game()
    : board{Board()}, piece_handler{PieceHandler()}, turn{1}, num_turns{0}, check{false}, checkMate{false},
      staleMate{false}, resigned{false}
{
    init();
}

Game::~Game()
{
    if (this->getCheckMate())
    {
        std::string color = this->getTurn() == Color::BLACK ? "WHITE" : "BLACK";
        std::cout << "Checkmate, " << color << " Won !" << std::endl;
    }
    else if (this->getStaleMate())
        std::cout << "Stalemate, Draw !" << std::endl;
    else if (this->getResigned())
        std::cout << "Resignation, " << (this->getTurn() == Color::BLACK ? "WHITE" : "BLACK") << " Won !"
                  << std::endl;
    else if (this->getDraw())
        std::cout << "Draw !" << std::endl;

    std::cout << std::endl << this->endResult() << std::endl;
}

Color Game::whoResigned() const
{
    if (this->resigned)
    {
        if (this->turn == Color::WHITE)
            return Color::BLACK;
        else
            return Color::WHITE;
    }
    return (Color)-1;
}

void Game::updateStatus()
{
    this->updateTurn();
    this->updateNumTurns();
    std::cout << *this << std::flush;
    this->setCheck(
        GameRuler::getInstance().isKingInCheck(this->getBoard().getArray(), (Color)this->getTurn()));
    this->setCheckMate(
        GameRuler::getInstance().isKingInCheckMate(this->getBoard().getArray(), (Color)this->getTurn()));
    this->setStaleMate(
        GameRuler::getInstance().isKingInStaleMate(this->getBoard().getArray(), (Color)this->getTurn()));
}

void Game::init()
{
    std::cout << "Game init" << std::endl;
    // init rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
    this->piece_handler.forsythGeneration(*this, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    GameRuler::getInstance().setGame(this);
}

std::string Game::endResult() const
{
    std::string res = "";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            auto piece = this->getBoard().getArray()[j][i].getPiece();
            if (piece != nullptr)
            {
                res.append((piece->getColor() == Color::WHITE ? "w" : "b"));
                res.append(1, piece->getType());
            }
            res.append(",");
        }
    }
    if (this->getCheckMate() || this->getResigned())
    {
        if (this->getTurn() == Color::WHITE)
            res.append(" 0-1"); // black wins
        else
            res.append(" 1-0"); // white wins
    }
    else if (this->getStaleMate() || this->getDraw())
    {
        res.append(" 1/2-1/2");
    }
    else
    {
        res.append(" ?-?"); // game ended by /quit
    }
    return res;
}

std::shared_ptr<King> Game::getWhiteKing() const
{
    for (auto piece : this->alive_pieces)
    {
        if (piece->getColor() == Color::WHITE && piece->getType() == PieceType::KING)
            return std::dynamic_pointer_cast<King>(piece);
    }
    throw std::runtime_error("No white king found");
}

std::shared_ptr<King> Game::getBlackKing() const
{
    for (auto piece : this->alive_pieces)
    {
        if (piece->getColor() == Color::BLACK && piece->getType() == PieceType::KING)
            return std::dynamic_pointer_cast<King>(piece);
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

PieceHandler Game::getPieceHandler() const { return this->piece_handler; }

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
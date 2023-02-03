#include "../../includes/pieces/pawn.hpp"
#include "../../includes/gameruler.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <string>

Pawn::Pawn(int x, int y, int color) : Piece(x, y, color), value{1} { this->setFirstMove(false); }

Pawn::~Pawn() {}

Piece::PieceMove Pawn::isValidMove(std::array<std::array<Tile, 8>, 8> board, int x, int y)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    if (this->getColor() == Color::WHITE)
    {
        // Check if we can move 2 tiles
        if (this->getNumMoves() == 0 && x == this->getX() && y == this->getY() + 2 &&
            board[x][y].getPiece() == nullptr && board[x][y - 1].getPiece() == nullptr)
        {
            result = {true, board[x][y].getPiece()};
        }
        // Check if we can move 1 tile
        else if (x == this->getX() && y == this->getY() + 1 && board[x][y].getPiece() == nullptr)
        {
            result = {true, board[x][y].getPiece()};
        }
        // Check if the pawn can eat a piece
        else if ((x == this->getX() + 1 || x == this->getX() - 1) && y == this->getY() + 1 &&
                 board[x][y].getPiece() != nullptr && board[x][y].getPiece()->getColor() == Color::BLACK)
        {
            result = {true, board[x][y].getPiece()};
        }
        // Check if the pawn can do "en passant" right
        else if (x == this->getX() + 1 && y == this->getY() + 1 && board[x][y].getPiece() == nullptr &&
                 board[this->getX() + 1][this->getY()].getPiece() != nullptr &&
                 board[this->getX() + 1][this->getY()].getPiece()->getColor() == Color::BLACK &&
                 board[this->getX() + 1][this->getY()].getPiece()->getType() == PieceType::PAWN)
        {
            std::shared_ptr<Pawn> pawn =
                std::dynamic_pointer_cast<Pawn>(board[this->getX() + 1][this->getY()].getPiece());
            if (pawn->getNumMoves() == 1)
            {
                result = {true, pawn};
            }
        }
        // left
        else if (x == this->getX() - 1 && y == this->getY() + 1 && board[x][y].getPiece() == nullptr &&
                 board[this->getX() - 1][this->getY()].getPiece() != nullptr &&
                 board[this->getX() - 1][this->getY()].getPiece()->getColor() == Color::BLACK &&
                 board[this->getX() - 1][this->getY()].getPiece()->getType() == PieceType::PAWN)
        {
            std::shared_ptr<Pawn> pawn =
                std::dynamic_pointer_cast<Pawn>(board[this->getX() - 1][this->getY()].getPiece());
            if (pawn->getNumMoves() == 1)
            {
                result = {true, pawn};
            }
        }
    }
    // black pawn
    else
    {
        // Check if we can move 2 tiles
        if (this->getNumMoves() == 0 && x == this->getX() && y == this->getY() - 2 &&
            board[x][y].getPiece() == nullptr && board[x][y + 1].getPiece() == nullptr)
        {
            result = {true, board[x][y].getPiece()};
        }
        // Check if we can move 1 tile
        else if (x == this->getX() && y == this->getY() - 1 && board[x][y].getPiece() == nullptr)
        {
            result = {true, board[x][y].getPiece()};
        }
        // Check if the pawn can eat a piece
        else if ((x == this->getX() + 1 || x == this->getX() - 1) && y == this->getY() - 1 &&
                 board[x][y].getPiece() != nullptr && board[x][y].getPiece()->getColor() == Color::WHITE)
        {
            result = {true, board[x][y].getPiece()};
        }
        // Check if the pawn can do "en passant" right
        else if (x == this->getX() + 1 && y == this->getY() - 1 && board[x][y].getPiece() == nullptr &&
                 board[this->getX() + 1][this->getY()].getPiece() != nullptr &&
                 board[this->getX() + 1][this->getY()].getPiece()->getColor() == Color::WHITE &&
                 board[this->getX() + 1][this->getY()].getPiece()->getType() == PieceType::PAWN)
        {
            std::shared_ptr<Pawn> pawn =
                std::dynamic_pointer_cast<Pawn>(board[this->getX() + 1][this->getY()].getPiece());
            if (pawn->getNumMoves() == 1)
            {
                result = {true, pawn};
            }
        }
        // left
        else if (x == this->getX() - 1 && y == this->getY() - 1 && board[x][y].getPiece() == nullptr &&
                 board[this->getX() - 1][this->getY()].getPiece() != nullptr &&
                 board[this->getX() - 1][this->getY()].getPiece()->getColor() == Color::WHITE &&
                 board[this->getX() - 1][this->getY()].getPiece()->getType() == PieceType::PAWN)
        {
            std::shared_ptr<Pawn> pawn =
                std::dynamic_pointer_cast<Pawn>(board[this->getX() - 1][this->getY()].getPiece());
            if (pawn->getNumMoves() == 1)
            {
                result = {true, pawn};
            }
        }
    }
    result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}

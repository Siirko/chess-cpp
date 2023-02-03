#include "../../includes/pieces/pawn.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/gameruler.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <string>

Pawn::Pawn(int x, int y, int color) : Piece(x, y, color), value{1} { this->setFirstMove(false); }

Pawn::~Pawn() {}

void Pawn::checkDoubleMove(array2d<Tile, 8, 8> board, PieceMove &result, int x, int y)
{
    int y_offset = this->getColor() == Color::WHITE ? 2 : -2;
    int y_offset2 = this->getColor() == Color::WHITE ? -1 : 1;
    if (this->getNumMoves() == 0 && x == this->getX() && y == this->getY() + y_offset &&
        board[x][y].getPiece() == nullptr && board[x][y + y_offset2].getPiece() == nullptr)
    {
        result = {true, board[x][y].getPiece()};
    }
}

void Pawn::checkMove(array2d<Tile, 8, 8> board, PieceMove &result, int x, int y)
{
    int y_offset = this->getColor() == Color::WHITE ? 1 : -1;
    if (x == this->getX() && y == this->getY() + y_offset && board[x][y].getPiece() == nullptr)
    {
        result = {true, board[x][y].getPiece()};
    }
}

void Pawn::checkCapture(array2d<Tile, 8, 8> board, PieceMove &result, int x, int y)
{
    int y_offset = this->getColor() == Color::WHITE ? 1 : -1;
    if ((x == this->getX() + 1 || x == this->getX() - 1) && y == this->getY() + y_offset &&
        board[x][y].getPiece() != nullptr && board[x][y].getPiece()->getColor() != this->getColor())
    {
        result = {true, board[x][y].getPiece()};
    }
}

void Pawn::checkEnPassant(array2d<Tile, 8, 8> board, PieceMove &result, int x, int y)
{
    // check left and right for black and white
    int y_offset = this->getColor() == Color::WHITE ? 1 : -1;
    if ((x == this->getX() + 1 || x == this->getX() - 1) && y == this->getY() + y_offset &&
        board[x][y].getPiece() == nullptr && board[x][y - y_offset].getPiece() != nullptr &&
        board[x][this->getY()].getPiece()->getColor() != this->getColor() &&
        board[x][this->getY()].getPiece()->getType() == PieceType::PAWN &&
        board[x][this->getY()].getPiece()->getNumMoves() == 1)
    {
        result = {true, board[x][this->getY()].getPiece()};
    }
}

Piece::PieceMove Pawn::isValidMove(array2d<Tile, 8, 8> board, int x, int y)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    this->checkDoubleMove(board, result, x, y);
    this->checkMove(board, result, x, y);
    this->checkCapture(board, result, x, y);
    this->checkEnPassant(board, result, x, y);
    // this->checkPromotion(board, result, x, y);
    result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}

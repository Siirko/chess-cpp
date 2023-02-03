#include "../../includes/pieces/knight.hpp"
#include "../../includes/gameruler.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <string>

Knight::Knight(int x, int y, int color) : Piece(x, y, color), value{3} { this->setFirstMove(false); }

Knight::~Knight() {}

Piece::PieceMove Knight::isValidMove(std::array<std::array<Tile, 8>, 8> board, int x, int y)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    if (x == this->getX() + 1 && y == this->getY() + 2)
        result = {true, board[x][y].getPiece()};
    else if (x == this->getX() + 2 && y == this->getY() + 1)
        result = {true, board[x][y].getPiece()};
    else if (x == this->getX() + 2 && y == this->getY() - 1)
        result = {true, board[x][y].getPiece()};
    else if (x == this->getX() + 1 && y == this->getY() - 2)
        result = {true, board[x][y].getPiece()};
    else if (x == this->getX() - 1 && y == this->getY() - 2)
        result = {true, board[x][y].getPiece()};
    else if (x == this->getX() - 2 && y == this->getY() - 1)
        result = {true, board[x][y].getPiece()};
    else if (x == this->getX() - 2 && y == this->getY() + 1)
        result = {true, board[x][y].getPiece()};
    else if (x == this->getX() - 1 && y == this->getY() + 2)
        result = {true, board[x][y].getPiece()};
    result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}
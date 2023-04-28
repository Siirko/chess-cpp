#include "../../includes/pieces/knight.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/gameruler.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <string>

Knight::Knight(int x, int y, int color) : Piece(x, y, color), value{3} { this->setFirstMove(false); }

Knight::~Knight() {}

Piece::PieceMove Knight::isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (this->checkOutOfBounds(x, y))
        return result;
    // Check if the move is to the same position
    if (this->checkSamePosition(this->getX(), this->getY(), x, y))
        return result;
    // Check if the move is to the same position
    this->callCheckLshape(*this, board, result, x, y);
    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}
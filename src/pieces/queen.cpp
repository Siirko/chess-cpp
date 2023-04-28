#include "../../includes/pieces/queen.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <string>

Queen::Queen(int x, int y, int color) : Piece(x, y, color), value{9} { this->setFirstMove(false); }

Queen::~Queen() {}

Piece::PieceMove Queen::isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck)
{
    PieceMove result = {false, nullptr};
    if (this->checkOutOfBounds(x, y))
        return result;
    if (this->checkSamePosition(this->getX(), this->getY(), x, y))
        return result;

    this->callCheckRows(*this, board, result, x, y);
    this->callCheckDiagonals(*this, board, result, x, y);
    this->callCheckColumns(*this, board, result, x, y);

    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}
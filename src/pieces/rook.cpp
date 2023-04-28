#include "../../includes/pieces/rook.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/gameruler.hpp"
#include "../../includes/pieces/king.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>

Rook::Rook(int x, int y, int color) : Piece(x, y, color), value{5} { this->setFirstMove(false); }

Rook::~Rook() {}

Piece::PieceMove Rook::isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck)
{
    PieceMove result = {false, nullptr};
    if (this->checkOutOfBounds(x, y))
        return result;
    if (this->checkSamePosition(this->getX(), this->getY(), x, y))
        return result;

    this->callCheckRows(*this, board, result, x, y);
    this->callCheckColumns(*this, board, result, x, y);

    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}

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

// TODO: need to decide who check if king is in check (board or the piece itself)
Piece::PieceMove Rook::isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (this->checkOutOfBounds(x, y))
        return result;
    // Check if the move is to the same position
    if (this->checkSamePosition(this->getX(), this->getY(), x, y))
        return result;

    // Check if we can move in the same column (up or down)
    this->callCheckRows(*this, board, result, x, y);
    this->callCheckColumns(*this, board, result, x, y);
    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}

#include "../../includes/pieces/tower.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include "../../includes/pieces/roi.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>

Tower::Tower(int x, int y, int color) : Piece(x, y, color), value{5} { this->setFirstMove(false); }

Tower::~Tower() {}

// TODO: need to decide who check if king is in check (board or the piece itself)
Piece::PieceMove Tower::isValidMove(array2d<Tile, 8, 8> board, int x, int y)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;

    // Check if we can move in the same column (up or down)
    this->callCheckRows(*this, board, result, x, y);
    this->callCheckColumns(*this, board, result, x, y);
    result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}

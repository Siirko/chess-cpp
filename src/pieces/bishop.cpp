#include "../../includes/pieces/bishop.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include "../../includes/utilities.hpp"
#include <array>
#include <iostream>
#include <string>

Bishop::Bishop(int x, int y, int color) : Piece(x, y, color), value{3} { this->setFirstMove(false); }

Bishop::~Bishop() {}

Piece::PieceMove Bishop::isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    this->callCheckDiagonals(*this, board, result, x, y);
    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}
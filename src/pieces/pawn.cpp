#include "../../includes/pieces/pawn.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/gameruler.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <string>

Pawn::Pawn(int x, int y, int color) : Piece(x, y, color), value{1} { this->setFirstMove(false); }

Pawn::~Pawn() {}

Piece::PieceMove Pawn::isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    this->callCheckDoubleMove(*this, board, result, x, y);
    this->callCheckStraight(*this, board, result, x, y);
    this->callCheckDiagonalCapture(*this, board, result, x, y);
    this->callCheckEnPassant(*this, board, result, x, y);
    // this->callCheckPromotion(*this, board, result, x, y);
    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    if (result.valid_move)
        this->setFirstMove(true);
    return result;
}

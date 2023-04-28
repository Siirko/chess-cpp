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
    if (this->checkOutOfBounds(x, y))
        return result;
    // Check if the move is to the same position
    if (this->checkSamePosition(this->getX(), this->getY(), x, y))
        return result;
    this->callCheckDoubleMove(*this, board, result, x, y);
    this->callCheckStraight(*this, board, result, x, y);
    this->callCheckDiagonalCapture(*this, board, result, x, y);
    this->callCheckEnPassant(*this, board, result, x, y);
    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    if (result.valid_move && this->getNumMoves() == 0)
        this->setFirstMove(true);
    return result;
}

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
    if (this->checkOutOfBounds(x, y))
        return result;
    if (this->checkSamePosition(this->getX(), this->getY(), x, y))
        return result;

    this->callCheckDiagonals(*this, board, result, x, y);

    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}

std::shared_ptr<Piece> Bishop::copy()
{
    std::shared_ptr<Piece> result = std::make_shared<Bishop>(this->getX(), this->getY(), this->getColor());
    result->setFirstMove(this->getFirstMove());
    return result;
}
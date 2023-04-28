#pragma once
#include "../board/tile.hpp"
#include "../check/checkmove.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

class KnightChecker : public CheckMove
{
  private:
    void callCheckLshape(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        this->checkLshape(self, board, result, x, y);
    }
    friend class Knight;
};
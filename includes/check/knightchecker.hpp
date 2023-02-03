#pragma once
#include "../board/tile.hpp"
#include "../check/checkmove.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

class KnightChecker
{
  private:
    static void callCheckLshape(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                int y)
    {
        CheckMove c = CheckMove();
        c.checkLshape(self, board, result, x, y);
    }
    friend class Knight;
};
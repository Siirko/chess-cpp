#pragma once
#include "../board/tile.hpp"
#include "../check/checkmove.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

class BishopChecker
{
  private:
    static void callCheckDiagonals(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                   int y)
    {
        CheckMove c = CheckMove();
        c.checkDiagonals(self, board, result, x, y);
    }
    friend class Bishop;
};
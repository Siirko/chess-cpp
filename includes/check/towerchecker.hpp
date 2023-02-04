#pragma once
#include "../board/tile.hpp"
#include "../check/checkmove.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

class TowerChecker
{
  private:
    static void callCheckRows(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        CheckMove c = CheckMove();
        c.checkRows(self, board, result, x, y);
    }
    static void callCheckColumns(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                 int y)
    {
        CheckMove c = CheckMove();
        c.checkColumns(self, board, result, x, y);
    }
    friend class Tower;
};
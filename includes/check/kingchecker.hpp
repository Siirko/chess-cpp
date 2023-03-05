#pragma once
#include "../board/tile.hpp"
#include "../check/checkmove.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

class KingChecker
{
  private:
    static void callCheckSquaresMoves(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                      int y)
    {
        CheckMove c = CheckMove();
        c.checkSquareMoves(self, board, result, x, y);
    }
    static void callCheckCastling(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                  int y)
    {
        CheckMove c = CheckMove();
        c.checkCastling(self, board, result, x, y);
    }
    friend class King;
};
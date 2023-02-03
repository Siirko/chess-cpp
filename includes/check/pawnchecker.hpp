#pragma once
#include "../board/tile.hpp"
#include "../check/checkmove.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

class PawnChecker
{
  public:
  private:
    static void callCheckEnPassant(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                   int y)
    {
        CheckMove c = CheckMove();
        c.checkEnPassant(self, board, result, x, y);
    }
    static void callCheckPromotion(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                   int y)
    {
        CheckMove c = CheckMove();
        c.checkPromotion(self, board, result, x, y);
    }
    static void callCheckStraight(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                  int y)
    {
        CheckMove c = CheckMove();
        c.checkStraight(self, board, result, x, y);
    }
    static void callCheckDoubleMove(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                    int y)
    {
        CheckMove c = CheckMove();
        c.checkDoubleMove(self, board, result, x, y);
    }
    static void callCheckDiagonalCapture(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result,
                                         int x, int y)
    {
        CheckMove c = CheckMove();
        c.checkDiagonalCapture(self, board, result, x, y);
    }
    friend class Pawn;
};
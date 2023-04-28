#pragma once
#include "../board/tile.hpp"
#include "../check/checkmove.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

class PawnChecker : public CheckMove
{
  private:
    void callCheckEnPassant(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        this->checkEnPassant(self, board, result, x, y);
    }
    void callCheckStraight(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        this->checkStraight(self, board, result, x, y);
    }
    void callCheckDoubleMove(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        this->checkDoubleMove(self, board, result, x, y);
    }
    void callCheckDiagonalCapture(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                  int y)
    {
        this->checkDiagonalCapture(self, board, result, x, y);
    }
    friend class Pawn;
};
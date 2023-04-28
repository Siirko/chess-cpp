#pragma once
#include "../board/tile.hpp"
#include "../check/checkmove.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

class QueenChecker : public CheckMove
{
  private:
    void callCheckRows(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        this->checkRows(self, board, result, x, y);
    }
    void callCheckColumns(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        this->checkColumns(self, board, result, x, y);
    }
    void callCheckDiagonals(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        this->checkDiagonals(self, board, result, x, y);
    }
    friend class Queen;
};
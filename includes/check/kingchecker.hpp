#pragma once
#include "../board/tile.hpp"
#include "../check/checkmove.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

class KingChecker : public CheckMove
{
  private:
    void callCheckSquaresMoves(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        this->checkSquareMoves(self, board, result, x, y);
    }
    void callCheckCastling(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
    {
        this->checkCastling(self, board, result, x, y);
    }
    friend class King;
};
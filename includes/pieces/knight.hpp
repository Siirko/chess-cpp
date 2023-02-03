#pragma once
#include "../board/tile.hpp"
#include "../check/knightchecker.hpp"
#include "piece.hpp"

class Knight : public Piece, public KnightChecker
{
  private:
    int value;

  public:
    Knight(int x, int y, int color);
    ~Knight();
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y) override;
};
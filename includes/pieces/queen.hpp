#pragma once
#include "../board/tile.hpp"
#include "piece.hpp"

class Queen : public Piece
{
  private:
    int value;

  public:
    Queen(int x, int y, int color);
    ~Queen();
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y) override;
};
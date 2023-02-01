#pragma once
#include "../board/tile.hpp"
#include "piece.hpp"

class Tower : public Piece
{
  private:
    int value;

  public:
    Tower(int x, int y, int color);
    ~Tower();
    virtual PieceMove isValidMove(std::array<std::array<Tile, 8>, 8> board, int x, int y) override;
};
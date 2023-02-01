#pragma once
#include "../board/tile.hpp"
#include "piece.hpp"

class Knight : public Piece
{
  private:
    int value;

  public:
    Knight(int x, int y, int color);
    ~Knight();
    virtual PieceMove isValidMove(std::array<std::array<Tile, 8>, 8> board, int x, int y) override;
};
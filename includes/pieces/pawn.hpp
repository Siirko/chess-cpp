#pragma once
#include "../board/tile.hpp"
#include "piece.hpp"

class Pawn : public Piece
{
  private:
    int value;

  public:
    Pawn(int x, int y, int color);
    ~Pawn();
    virtual PieceMove isValidMove(std::array<std::array<Tile, 8>, 8> board,
                                                                int x, int y) override;
};
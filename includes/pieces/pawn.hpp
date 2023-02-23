#pragma once
#include "../board/tile.hpp"
#include "../check/pawnchecker.hpp"
#include "piece.hpp"

class Pawn : public Piece, public PawnChecker
{
  private:
    int value;

  public:
    Pawn(int x, int y, int color);
    ~Pawn();
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck) override;
};
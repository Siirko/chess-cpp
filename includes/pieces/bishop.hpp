#pragma once
#include "../board/tile.hpp"
#include "../check/bishopchecker.hpp"
#include "piece.hpp"

class Bishop : public Piece, public BishopChecker
{
  private:
    int value;

  public:
    Bishop(int x, int y, int color);
    ~Bishop();
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck) override;
};
#pragma once
#include "../board/tile.hpp"
#include "../check/roichecker.hpp"
#include "piece.hpp"

class Roi : public Piece, public RoiChecker
{
  private:
    int value;

  public:
    Roi(int x, int y, int color);
    ~Roi();
    bool isCheck(array2d<Tile, 8, 8> board, int x, int y);
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck) override;
};
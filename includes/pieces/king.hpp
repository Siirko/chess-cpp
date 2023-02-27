#pragma once
#include "../board/tile.hpp"
#include "../check/kingchecker.hpp"
#include "piece.hpp"

class King : public Piece, public KingChecker
{
  private:
    int value;

  public:
    King(int x, int y, int color);
    ~King();
    bool isCheck(array2d<Tile, 8, 8> board, int x, int y);
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck) override;
};
#pragma once
#include "../board/tile.hpp"
#include "../check/rookchecker.hpp"
#include "piece.hpp"

class Rook : public Piece, public RookChecker
{
  private:
    int value;

  public:
    Rook(int x, int y, int color);
    ~Rook();
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck) override;
    virtual std::shared_ptr<Piece> copy() override;
};
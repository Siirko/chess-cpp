#pragma once
#include "../board/tile.hpp"
#include "piece.hpp"

class Pawn : public Piece
{
  private:
    int value;
    void checkEnPassant(array2d<Tile, 8, 8> board, PieceMove &result, int x, int y);
    void checkPromotion(array2d<Tile, 8, 8> board, PieceMove &result, int x, int y);
    void checkMove(array2d<Tile, 8, 8> board, PieceMove &result, int x, int y);
    void checkDoubleMove(array2d<Tile, 8, 8> board, PieceMove &result, int x, int y);
    void checkCapture(array2d<Tile, 8, 8> board, PieceMove &result, int x, int y);

  public:
    Pawn(int x, int y, int color);
    ~Pawn();
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y) override;
};
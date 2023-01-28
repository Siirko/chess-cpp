#pragma once
#include "../board/tile.hpp"
#include "piece.hpp"

class Roi : public Piece
{
  private:
    int value;

  public:
    Roi(int x, int y, int color);
    ~Roi();
    bool isCheck(std::array<std::array<Tile, 8>, 8> board, int x, int y);
    virtual std::pair<bool, std::shared_ptr<Piece>> isValidMove(std::array<std::array<Tile, 8>, 8> board,
                                                                int x, int y) override;
};
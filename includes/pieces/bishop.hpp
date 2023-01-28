#pragma once
#include "../board/tile.hpp"
#include "piece.hpp"

class Bishop : public Piece
{
  private:
    int value;

  public:
    Bishop(int x, int y, int color);
    ~Bishop();
    virtual std::pair<bool, std::shared_ptr<Piece>> isValidMove(std::array<std::array<Tile, 8>, 8> board,
                                                                int x, int y) override;
};
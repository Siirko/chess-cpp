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
    /**
     * @brief Check if the king is in check given the board and coordinates.
     * @param board The board to check the king on.
     * @param x The x coordinate of the king.
     * @param y The y coordinate of the king.
     * @return True if the king is in check, false otherwise.
     * @note King can be not in (x,y) coordinate, so it will create a temporary king in (x,y) and check if it
     * is in check.
     */
    bool isCheck(array2d<Tile, 8, 8> board, int x, int y);
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck) override;
    virtual std::shared_ptr<Piece> copy() override;
};
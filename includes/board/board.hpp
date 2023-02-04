#pragma once
#include "../board/tile.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"
#include <array>
#include <memory>
class Board
{
  private:
    array2d<Tile, 8, 8> board;
    void initBoard();

  public:
    Board();
    ~Board();
    Tile getTile(int x, int y) const;
    std::array<std::array<Tile, 8>, 8> getBoard() const;
    void setPiece(std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> movePiece(std::shared_ptr<Piece> piece, int x, int y);
    void doCastling(std::shared_ptr<Piece> piece, Color color, int x, int y);
    void doPromotion(std::shared_ptr<Piece> piece, int x, int y);
    void updatePiece(std::shared_ptr<Piece> piece, int x, int y);
    friend std::ostream &operator<<(std::ostream &os, const Board &game);
};
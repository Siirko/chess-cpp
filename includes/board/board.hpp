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
    std::array<std::array<Tile, 8>, 8> getArray() const;
    void setPiece(std::shared_ptr<Piece> piece);
    /**
     * @brief Move a piece to a new position on the board.
     * @param piece The piece to move.
     * @param x The x coordinate to move to.
     * @param y The y coordinate to move to.
     * @return The piece that was captured, or nullptr if no piece was captured.
     */
    std::shared_ptr<Piece> movePiece(std::shared_ptr<Piece> piece, int x, int y);
    void doCastling(std::shared_ptr<Piece> piece, int x, int y);
    /**
     * @brief Update the piece's position on the board.
     * @param piece The piece to update.
     * @param x The x coordinate to move to.
     * @param y The y coordinate to move to.
     */
    void updatePiece(std::shared_ptr<Piece> piece, int x, int y);
    friend std::ostream &operator<<(std::ostream &os, const Board &game);
};
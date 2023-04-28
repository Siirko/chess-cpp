#pragma once
#include "../board/tile.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

/**
 * @brief CheckMove class is responsible for checking if a move is valid.
 * @note following this idea:
 * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Friendship_and_the_Attorney-Client
 */

class Piece;
class CheckMove
{
    // Those two functions is herited by all the checkers and can be used directly by the pieces.
  public:
    /**
     * @brief Check if the piece is going out of bounds.
     * @param x The x position of the piece.
     * @param y The y position of the piece.
     * @return true if the piece is going out of bounds.
     * @return false if the piece is not going out of bounds.
     */
    bool checkOutOfBounds(int x, int y) { return x < 0 || x > 7 || y < 0 || y > 7; }
    /**
     * @brief Check if the piece is going to the same position.
     * @param x The x position of the piece.
     * @param y The y position of the piece.
     * @param x2 The x position of the move.
     * @param y2 The y position of the move.
     * @return true if the piece is going to the same position.
     */
    bool checkSamePosition(int x, int y, int x2, int y2) { return x == x2 && y == y2; }

  private:
    friend class PawnChecker;
    void checkEnPassant(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
    void checkStraight(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
    void checkDoubleMove(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
    void checkDiagonalCapture(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);

    friend class RookChecker;
    void checkRows(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
    void checkColumns(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);

    friend class QueenChecker;
    friend class BishopChecker;
    /**
     * @brief Check if the piece can move diagonally (up, down, left, right).
     */
    void checkDiagonals(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);

    friend class KnightChecker;
    void checkLshape(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);

    friend class KingChecker;
    void checkSquareMoves(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
    void checkCastling(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
};
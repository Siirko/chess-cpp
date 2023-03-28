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
  private:
    friend class PawnChecker;
    void checkEnPassant(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
    void checkPromotion(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
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
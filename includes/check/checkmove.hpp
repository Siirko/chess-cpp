#pragma once
#include "../board/tile.hpp"
#include "../pieces/piece.hpp"
#include "../utilities.hpp"

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

    friend class TowerChecker;
    void checkRows(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
    void checkColumns(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);

    friend class QueenChecker;
    friend class BishopChecker;
    void checkDiagonals(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);

    friend class KnightChecker;
    void checkLshape(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);

    friend class RoiChecker;
    void checkSquareMoves(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
    void checkCastling(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y);
};
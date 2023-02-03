#pragma once
#include "../utilities.hpp"
#include <array>
#include <memory>

enum Color
{
    BLACK = 0,
    WHITE = 1
};

enum PieceType
{
    PAWN = 'P',
    TOWER = 'T',
    KNIGHT = 'K',
    BISHOP = 'B',
    QUEEN = 'Q',
    KING = 'R'
};

class Tile;
class Piece : public std::enable_shared_from_this<Piece>
{
  private:
    int x;
    int y;
    int color;
    bool firstMove;
    int num_moves = 0;

  public:
    struct PieceMove
    {
        bool valid_move;
        std::shared_ptr<Piece> eaten_piece;
    };
    Piece(int x, int y, int color);
    virtual ~Piece();
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    void setColor(int color);
    int getColor() const;
    bool getFirstMove() const;
    void setFirstMove(bool firstMove);
    char getType();
    int getNumMoves() const;
    void updateNumMoves();
    bool beforeCheckMove(array2d<Tile, 8, 8> board, PieceMove result, int x, int y);
    // Abstract method
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y) = 0;
    bool canMove(array2d<Tile, 8, 8> board);
    friend std::ostream &operator<<(std::ostream &os, const Piece &piece);
    std::shared_ptr<Piece> getptr() { return shared_from_this(); }
};

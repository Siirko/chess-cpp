#pragma once
#include "../board/tile.hpp"
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
    bool beforeCheckMove(std::array<std::array<Tile, 8>, 8> board,
                         std::pair<bool, std::shared_ptr<Piece>> result, int x, int y);
    // Abstract method
    virtual std::pair<bool, std::shared_ptr<Piece>> isValidMove(std::array<std::array<Tile, 8>, 8> board,
                                                                int x, int y) = 0;
    bool canMove(std::array<std::array<Tile, 8>, 8> board);
    friend std::ostream &operator<<(std::ostream &os, const Piece &piece);
    std::shared_ptr<Piece> getptr() { return shared_from_this(); }
};

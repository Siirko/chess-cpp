#pragma once
#include "../pieces/piece.hpp"
#include <climits>
#include <memory>

class Piece;
class Tile {
    private:
        int x;
        int y;
        std::shared_ptr<Piece> piece;
    public:
        Tile();
        ~Tile();
        void setPiece(std::shared_ptr<Piece> piece);
        std::shared_ptr<Piece> getPiece() const;
        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);
};
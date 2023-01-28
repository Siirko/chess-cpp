#pragma once
#include <array>
#include <memory>
#include "tile.hpp"

class Board{
    private:
        std::array<std::array <Tile, 8>, 8> board;
        void initBoard();  
    public:
        Board();
        ~Board();
        Tile getTile(int x, int y) const;
        std::array<std::array <Tile, 8>, 8> getBoard() const;
        void setPiece(std::shared_ptr<Piece> piece);
        std::shared_ptr<Piece> movePiece(std::shared_ptr<Piece> piece, int x, int y);
        void printBoard();
        friend std::ostream& operator<<(std::ostream& os, const Board& game);
};
#include "../../includes/pieces/bishop.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include "../../includes/utilities.hpp"
#include <array>
#include <iostream>
#include <string>

Bishop::Bishop(int x, int y, int color) : Piece(x, y, color), value{3} { this->setFirstMove(false); }

Bishop::~Bishop() {}

std::pair<bool, std::shared_ptr<Piece>> Bishop::isValidMove(std::array<std::array<Tile, 8>, 8> board, int x,
                                                            int y)
{
    std::pair<bool, std::shared_ptr<Piece>> result = std::pair<bool, std::shared_ptr<Piece>>(false, nullptr);
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;

    if (abs(x - this->getX()) == abs(y - this->getY()))
    {
        // Check if the path is clear
        int xDir = (x - this->getX()) / abs(x - this->getX());
        int yDir = (y - this->getY()) / abs(y - this->getY());
        int i = this->getX() + xDir;
        int j = this->getY() + yDir;
        while (i != x && j != y)
        {
            if (board[i][j].getPiece() != nullptr)
                return result;
            i += xDir;
            j += yDir;
        }
        // Check if the move is valid
        if (board[x][y].getPiece() == nullptr || board[x][y].getPiece()->getColor() != this->getColor())
        {
            result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
        }
    }
    return result;
}

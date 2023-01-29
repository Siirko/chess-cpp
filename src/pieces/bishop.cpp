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
        int i = this->getX();
        int j = this->getY();
        int x_step = (x - i) / abs(x - i);
        int y_step = (y - j) / abs(y - j);
        while (i != x && j != y)
        {
            i += x_step;
            j += y_step;
            if (board[i][j].getPiece() != nullptr)
                return result;
        }
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    }
    return result;
}

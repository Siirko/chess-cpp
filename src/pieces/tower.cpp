#include "../../includes/pieces/tower.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include "../../includes/pieces/roi.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>

Tower::Tower(int x, int y, int color) : Piece(x, y, color), value{5} { this->setFirstMove(false); }

Tower::~Tower() {}

// TODO: need to decide who check if king is in check (board or the piece itself)
Piece::PieceMove Tower::isValidMove(std::array<std::array<Tile, 8>, 8> board, int x, int y)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;

    // Check if we can move in the same column (up or down)
    if (x == this->getX() && y != this->getY())
    {
        bool going_up = y > this->getY();
        int i;
        if (going_up)
        {
            for (i = this->getY() + 1; i < y; i++)
            {
                if (board[x][i].getPiece() != nullptr)
                    return result;
            }
        }
        else
        {
            for (i = this->getY() - 1; i > y; i--)
            {
                if (board[x][i].getPiece() != nullptr)
                    return result;
            }
        }
        result = {true, board[x][y].getPiece()};
    }
    // Check if we can move in the same row (right or left)
    else if (x != this->getX() && y == this->getY())
    {
        bool going_right = x > this->getX();
        int i;
        if (going_right)
        {
            for (i = this->getX() + 1; i < x; i++)
            {
                if (board[i][y].getPiece() != nullptr)
                    return result;
            }
        }
        else
        {
            for (i = this->getX() - 1; i > x; i--)
            {
                if (board[i][y].getPiece() != nullptr)
                    return result;
            }
        }
        result = {true, board[x][y].getPiece()};
    }
    result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}

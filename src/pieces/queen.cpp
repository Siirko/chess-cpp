#include "../../includes/pieces/queen.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <string>

Queen::Queen(int x, int y, int color) : Piece(x, y, color), value{9} { this->setFirstMove(false); }

Queen::~Queen() {}

Piece::PieceMove Queen::isValidMove(std::array<std::array<Tile, 8>, 8> board, int x, int y)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    // check left down diagonal
    if (x - this->getX() == y - this->getY())
    {
        for (int i = this->getX() - 1, j = this->getY() - 1; i > x && j > y; i--, j--)
        {
            if (board[i][j].getPiece() != nullptr)
                return result;
        }
        result = {true, board[x][y].getPiece()};
    }
    // check right up diagonal
    else if (this->getX() - x == this->getY() - y)
    {
        for (int i = this->getX() + 1, j = this->getY() + 1; i < x && j < y; i++, j++)
        {
            if (board[i][j].getPiece() != nullptr)
                return result;
        }
        result = {true, board[x][y].getPiece()};
    }
    // check left up diagonal
    else if (x - this->getX() == this->getY() - y)
    {
        for (int i = this->getX() - 1, j = this->getY() + 1; i > x && j < y; i--, j++)
        {
            if (board[i][j].getPiece() != nullptr)
                return result;
        }
        result = {true, board[x][y].getPiece()};
    }
    // check right down diagonal
    else if (this->getX() - x == y - this->getY())
    {
        for (int i = this->getX() + 1, j = this->getY() - 1; i < x && j > y; i++, j--)
        {
            if (board[i][j].getPiece() != nullptr)
                return result;
        }
        result = {true, board[x][y].getPiece()};
    }
    // Check if the move is horizontal
    else if (x == this->getX())
    {
        // Check if is going up
        if (y > this->getY())
        {
            // Check if there is a piece in the way
            for (int i = this->getY() + 1; i < y; i++)
            {
                if (board[x][i].getPiece() != nullptr)
                    return result;
            }
            result = {true, board[x][y].getPiece()};
        }
        // Check if is going down
        else
        {
            // Check if there is a piece in the way
            for (int i = this->getY() - 1; i > y; i--)
            {
                if (board[x][i].getPiece() != nullptr)
                    return result;
            }
            result = {true, board[x][y].getPiece()};
        }
    }
    // Check if the move is vertical
    else if (y == this->getY())
    {
        // Check if is going right
        if (x > this->getX())
        {
            // Check if there is a piece in the way
            for (int i = this->getX() + 1; i < x; i++)
            {
                if (board[i][y].getPiece() != nullptr)
                    return result;
            }
            result = {true, board[x][y].getPiece()};
        }
        // Check if is going left
        else
        {
            // Check if there is a piece in the way
            for (int i = this->getX() - 1; i > x; i--)
            {
                if (board[i][y].getPiece() != nullptr)
                    return result;
            }
            result = {true, board[x][y].getPiece()};
        }
        result = {true, board[x][y].getPiece()};
    }
    result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}
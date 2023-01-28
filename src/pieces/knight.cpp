#include "../../includes/pieces/knight.hpp"
#include "../../includes/pieces/piece.hpp"
#include "../../includes/board/tile.hpp"
#include <array>
#include <string>
#include <iostream>

Knight::Knight(int x, int y, int color)
: Piece(x, y, color)
, value { 3 }
{
    this->setFirstMove(false);
}

Knight::~Knight()
{
}

std::pair<bool, std::shared_ptr<Piece>> Knight::isValidMove(std::array<std::array<Tile, 8>, 8> board, int x, int y)
{
    std::pair <bool, std::shared_ptr<Piece>> result = std::pair<bool, std::shared_ptr<Piece>>(false, nullptr);
    // Check if the move is out of the board
    if(x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    if (x == this->getX() + 1 && y == this->getY() + 2)
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    else if (x == this->getX() + 2 && y == this->getY() + 1)
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    else if (x == this->getX() + 2 && y == this->getY() - 1)
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    else if (x == this->getX() + 1 && y == this->getY() - 2)
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    else if (x == this->getX() - 1 && y == this->getY() - 2)
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    else if (x == this->getX() - 2 && y == this->getY() - 1)
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    else if (x == this->getX() - 2 && y == this->getY() + 1)
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    else if (x == this->getX() - 1 && y == this->getY() + 2)
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    return result;
}
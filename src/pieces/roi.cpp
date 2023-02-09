#include "../../includes/pieces/roi.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <set>
#include <string>

Roi::Roi(int x, int y, int color) : Piece(x, y, color), value{5} { this->setFirstMove(false); }

Roi::~Roi() {}

bool Roi::isCheck(array2d<Tile, 8, 8> board, int x, int y)
{
    auto tmp = board[x][y].getPiece();
    board[x][y].setPiece(std::make_shared<Roi>(x, y, this->getColor()));
    // Check if any opponent piece is attacking the king
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].getPiece() != nullptr && board[i][j].getPiece()->getColor() != this->getColor())
            {
                PieceMove result = board[i][j].getPiece()->isValidMove(board, x, y);
                // std::cout << board[i][j].getPiece()->getType() << ", " << *(result.second) << std::endl;
                if (result.valid_move)
                {
                    board[x][y].setPiece(tmp);
                    return true;
                }
            }
        }
    }
    board[x][y].setPiece(tmp);
    return false;
}

Piece::PieceMove Roi::isValidMove(array2d<Tile, 8, 8> board, int x, int y)
{
    PieceMove result = {false, nullptr};
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    // special rule, castle move
    this->callCheckCastling(*this, board, result, x, y);
    this->callCheckSquaresMoves(*this, board, result, x, y);
    result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}
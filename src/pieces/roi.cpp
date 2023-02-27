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
    if (x != this->getX() && y != this->getY())
        board[x][y].setPiece(std::make_shared<Roi>(x, y, this->getColor()));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            auto enemy_piece = board[i][j].getPiece();
            if (enemy_piece != nullptr && enemy_piece->getColor() != this->getColor())
            {
                if (enemy_piece->isValidMove(board, x, y, false).valid_move)
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

Piece::PieceMove Roi::isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck)
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
    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}
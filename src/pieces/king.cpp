#include "../../includes/pieces/king.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <set>
#include <string>

King::King(int x, int y, int color) : Piece(x, y, color), value{5} { this->setFirstMove(false); }

King::~King() {}

bool King::isCheck(array2d<Tile, 8, 8> board, int x, int y)
{
    auto tmp = board[x][y].getPiece();
    board[x][y].setPiece(std::make_shared<King>(x, y, this->getColor()));
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

Piece::PieceMove King::isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck)
{
    PieceMove result = {false, nullptr};
    if (this->checkOutOfBounds(x, y))
        return result;
    if (this->checkSamePosition(this->getX(), this->getY(), x, y))
        return result;

    this->callCheckCastling(*this, board, result, x, y);
    this->callCheckSquaresMoves(*this, board, result, x, y);

    if (beforeCheck)
        result.valid_move = this->beforeCheckMove(board, result, x, y);
    return result;
}

std::shared_ptr<Piece> King::copy()
{
    std::shared_ptr<Piece> result = std::make_shared<King>(this->getX(), this->getY(), this->getColor());
    result->setFirstMove(this->getFirstMove());
    return result;
}
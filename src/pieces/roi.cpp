#include "../../includes/pieces/roi.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <set>
#include <string>

Roi::Roi(int x, int y, int color) : Piece(x, y, color), value{5} { this->setFirstMove(false); }

Roi::~Roi() {}

bool Roi::isCheck(std::array<std::array<Tile, 8>, 8> board, int x, int y)
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
                std::pair<bool, std::shared_ptr<Piece>> result =
                    board[i][j].getPiece()->isValidMove(board, x, y);
                // std::cout << board[i][j].getPiece()->getType() << ", " << *(result.second) << std::endl;
                if (result.first)
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

std::pair<bool, std::shared_ptr<Piece>> Roi::isValidMove(std::array<std::array<Tile, 8>, 8> board, int x,
                                                         int y)
{
    std::pair<bool, std::shared_ptr<Piece>> result = std::pair<bool, std::shared_ptr<Piece>>(false, nullptr);
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;

    // special rule, castle move
    if (this->getNumMoves() == 0 && board[x][y].getPiece() != nullptr &&
        board[x][y].getPiece()->getType() == PieceType::TOWER && board[x][y].getPiece()->getNumMoves() == 0)
    {
        std::set<int> coord_to_check = x == 7 ? std::set<int>{5, 6} : std::set<int>{1, 2, 3};
        for (auto coord : coord_to_check)
        {
            if (board[coord][y].getPiece() != nullptr)
                throw std::invalid_argument("can't move king");
            if (this->isCheck(board, coord, y))
                throw std::invalid_argument("can't move king");
        }
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
    }
    // Check if the move is one tile away
    if (abs(x - this->getX()) <= 1 && abs(y - this->getY()) <= 1)
    {
        // Check if the tile is empty or if there is an opponent piece
        if (board[x][y].getPiece() == nullptr || board[x][y].getPiece()->getColor() != this->getColor())
        {
            // check if the king is not in check
            if (!this->isCheck(board, x, y))
            {
                // check if the king is not in check
                result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
            }
            else
            {
                throw std::invalid_argument("can't move king");
            }
        }
    }
    result.first = this->beforeCheckMove(board, result, x, y);
    return result;
}
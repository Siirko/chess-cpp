#include "../../includes/pieces/tower.hpp"
#include "../../includes/board/tile.hpp"
#include "../../includes/pieces/piece.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>

Tower::Tower(int x, int y, int color) : Piece(x, y, color), value{5} { this->setFirstMove(false); }

Tower::~Tower() {}

// TODO: need to decide who check if king is in check (board or the piece itself)
std::pair<bool, std::shared_ptr<Piece>> Tower::isValidMove(std::array<std::array<Tile, 8>, 8> board, int x,
                                                           int y)
{
    std::pair<bool, std::shared_ptr<Piece>> result = std::pair<bool, std::shared_ptr<Piece>>(false, nullptr);
    // Check if the move is out of the board
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return result;
    // Check if the move is to the same position
    if (x == this->getX() && y == this->getY())
        return result;
    int max_size = (int)board.max_size();
    // Check if the move is a castling move (for white)
    if (this->getNumMoves() == 0 && (this->getX() == 0 || this->getX() == max_size) && this->getY() == 0 &&
        board[x][y].getPiece() != nullptr && board[x][y].getPiece()->getType() == 'R')
    {
        // Check if the king has moved
        std::shared_ptr<Piece> king = board[x][y].getPiece();
        if (king->getNumMoves() == 0)
        {
            // Check if there is a piece in the way
            if (this->getX() == 0)
            {
                for (int i = 1; i < 4; i++)
                {
                    if (board[i][0].getPiece() != nullptr)
                        return result;
                }
                std::cout << "king eee" << std::endl;
                // Check if the king can move to the tower's position
                std::pair<bool, std::shared_ptr<Piece>> king_result = king->isValidMove(board, 2, 0);
                if (king_result.first == false)
                    return result;
                std::cout << "rook ?" << std::endl;
            }
            else
            {
                for (int i = 5; i < 7; i++)
                {
                    if (board[i][0].getPiece() != nullptr)
                        return result;
                }
                // Check if the king can move to the tower's position (initial position to 6)
                std::pair<bool, std::shared_ptr<Piece>> king_result = king->isValidMove(board, 6, 0);
                if (!king_result.first)
                    return result;
            }
            result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
            this->updateNumMoves();
        }
    }
    // castle for black
    else if (this->getNumMoves() == 0 && (this->getX() == 0 || this->getX() == max_size) &&
             this->getY() == max_size && board[x][y].getPiece() != nullptr &&
             board[x][y].getPiece()->getType() == 'R')
    {
        // Check if the king has moved
        std::shared_ptr<Piece> king = board[x][y].getPiece();
        if (king->getNumMoves() == 0)
        {
            // Check if there is a piece in the way
            if (this->getX() == 0)
            {
                for (int i = 1; i < 4; i++)
                {
                    if (board[i][max_size].getPiece() != nullptr)
                        return result;
                }
                // Check if the king can move to the tower's position
                std::pair<bool, std::shared_ptr<Piece>> king_result = king->isValidMove(board, 2, max_size);
                if (king_result.first == false)
                    return result;
            }
            else
            {
                for (int i = 5; i < 7; i++)
                {
                    if (board[i][max_size].getPiece() != nullptr)
                        return result;
                }
                // Check if the king can move to the tower's position (initial position to 6)
                std::pair<bool, std::shared_ptr<Piece>> king_result = king->isValidMove(board, 6, max_size);
                if (!king_result.first)
                    return result;
            }
            result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
            this->updateNumMoves();
        }
    }
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
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
        this->updateNumMoves();
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
        result = std::pair<bool, std::shared_ptr<Piece>>(true, board[x][y].getPiece());
        this->updateNumMoves();
    }
    return result;
}

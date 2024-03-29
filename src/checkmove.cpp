#include "../includes/check/checkmove.hpp"
#include "../includes/pieces/king.hpp"
#include "../includes/pieces/piece.hpp"
#include <cassert>
#include <set>

void CheckMove::checkDoubleMove(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                int y)
{
    int y_offset = self.getColor() == Color::WHITE ? 2 : -2;
    int y_offset2 = self.getColor() == Color::WHITE ? -1 : 1;
    if (self.getNumMoves() == 0 && x == self.getX() && y == self.getY() + y_offset &&
        board[x][y].getPiece() == nullptr && board[x][y + y_offset2].getPiece() == nullptr)
    {
        result = {true, board[x][y].getPiece()};
    }
}

void CheckMove::checkStraight(Piece &self, array2d<Tile, 8, 8> board, Piece::Piece::PieceMove &result, int x,
                              int y)
{
    int y_offset = self.getColor() == Color::WHITE ? 1 : -1;
    if (x == self.getX() && y == self.getY() + y_offset && board[x][y].getPiece() == nullptr)
    {
        result = {true, board[x][y].getPiece()};
    }
}

void CheckMove::checkDiagonalCapture(Piece &self, array2d<Tile, 8, 8> board, Piece::Piece::PieceMove &result,
                                     int x, int y)
{
    int y_offset = self.getColor() == Color::WHITE ? 1 : -1;
    if ((x == self.getX() + 1 || x == self.getX() - 1) && y == self.getY() + y_offset &&
        board[x][y].getPiece() != nullptr && board[x][y].getPiece()->getColor() != self.getColor())
    {
        result = {true, board[x][y].getPiece()};
    }
}

void CheckMove::checkEnPassant(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
{
    // check left and right for black and white
    int y_offset = self.getColor() == Color::WHITE ? 1 : -1;
    if ((x == self.getX() + 1 || x == self.getX() - 1) && y == self.getY() + y_offset &&
        board[x][y].getPiece() == nullptr && board[x][y - y_offset].getPiece() != nullptr &&
        board[x][self.getY()].getPiece()->getColor() != self.getColor() &&
        board[x][self.getY()].getPiece()->getType() == PieceType::PAWN &&
        board[x][self.getY()].getPiece()->getNumMoves() == 1)
    {
        auto pawn = board[x][self.getY()].getPiece();
        if (pawn->getFirstMove())
            result = {true, board[x][self.getY()].getPiece()};
    }
}

void CheckMove::checkCastling(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
{
    assert(self.getType() == PieceType::KING);
    King &king = dynamic_cast<King &>(self);
    if (self.getNumMoves() == 0 && board[x][y].getPiece() != nullptr &&
        board[x][y].getPiece()->getType() == PieceType::ROOK && board[x][y].getPiece()->getNumMoves() == 0)
    {
        if (king.isCheck(board, self.getX(), self.getY()))
            throw std::invalid_argument("can't move king");
        std::set<int> coord_to_check = x == 7 ? std::set<int>{5, 6} : std::set<int>{2, 3};
        for (auto coord : coord_to_check)
        {
            if (board[coord][y].getPiece() != nullptr)
                throw std::invalid_argument("can't move king");
            if (king.isCheck(board, coord, y))
                throw std::invalid_argument("can't move king");
        }
        result = {true, board[x][y].getPiece()};
    }
}

void CheckMove::checkSquareMoves(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x,
                                 int y)
{
    assert(self.getType() == PieceType::KING);
    King &king = dynamic_cast<King &>(self);
    // Check if the move is one tile away
    if (abs(x - self.getX()) <= 1 && abs(y - self.getY()) <= 1)
    {
        // check if is there opposite king
        if (board[x][y].getPiece() != nullptr && board[x][y].getPiece()->getType() == PieceType::KING &&
            board[x][y].getPiece()->getColor() != self.getColor())
        {
            throw std::invalid_argument("can't move king");
        }
        // Check if the tile is empty or if there is an opponent piece
        if (board[x][y].getPiece() == nullptr || board[x][y].getPiece()->getColor() != self.getColor())
        {
            if (king.isCheck(board, x, y))
                throw std::invalid_argument("can't move king");
            result = {true, board[x][y].getPiece()};
        }
    }
}

void CheckMove::checkLshape(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
{
    if (x == self.getX() + 1 && y == self.getY() + 2)
        result = {true, board[x][y].getPiece()};
    else if (x == self.getX() + 2 && y == self.getY() + 1)
        result = {true, board[x][y].getPiece()};
    else if (x == self.getX() + 2 && y == self.getY() - 1)
        result = {true, board[x][y].getPiece()};
    else if (x == self.getX() + 1 && y == self.getY() - 2)
        result = {true, board[x][y].getPiece()};
    else if (x == self.getX() - 1 && y == self.getY() - 2)
        result = {true, board[x][y].getPiece()};
    else if (x == self.getX() - 2 && y == self.getY() - 1)
        result = {true, board[x][y].getPiece()};
    else if (x == self.getX() - 2 && y == self.getY() + 1)
        result = {true, board[x][y].getPiece()};
    else if (x == self.getX() - 1 && y == self.getY() + 2)
        result = {true, board[x][y].getPiece()};
}

void CheckMove::checkColumns(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
{
    if (x == self.getX() && y != self.getY())
    {
        bool going_up = y > self.getY();
        int i = going_up ? self.getY() + 1 : self.getY() - 1;
        for (; i != y; going_up ? i++ : i--)
        {
            if (board[x][i].getPiece() != nullptr)
                return;
        }
        result = {true, board[x][y].getPiece()};
    }
}

void CheckMove::checkRows(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
{
    if (y == self.getY() && x != self.getX())
    {
        bool going_right = x > self.getX();
        int i = going_right ? self.getX() + 1 : self.getX() - 1;
        for (; i != x; going_right ? i++ : i--)
        {
            if (board[i][y].getPiece() != nullptr)
                return;
        }
        result = {true, board[x][y].getPiece()};
    }
}

void CheckMove::checkDiagonals(Piece &self, array2d<Tile, 8, 8> board, Piece::PieceMove &result, int x, int y)
{
    if (abs(x - self.getX()) == abs(y - self.getY()))
    {
        // Check if the path is clear
        int xDir = (x - self.getX()) / abs(x - self.getX());
        int yDir = (y - self.getY()) / abs(y - self.getY());
        int i = self.getX() + xDir;
        int j = self.getY() + yDir;
        for (; i != x && j != y; i += xDir, j += yDir)
        {
            if (board[i][j].getPiece() != nullptr)
                return;
        }
        // Check if the move is valid
        if (board[x][y].getPiece() == nullptr || board[x][y].getPiece()->getColor() != self.getColor())
        {
            result = {true, board[x][y].getPiece()};
        }
    }
}
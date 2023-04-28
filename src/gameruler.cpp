#include "../includes/gameruler.hpp"
#include "../includes/board/board.hpp"
#include "../includes/pieces/king.hpp"
#include "../includes/pieces/piece.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <vector>

void GameRuler::setGame(const Game *game)
{
    this->game = game;
    whiteKing = game->getKing(Color::WHITE);
    blackKing = game->getKing(Color::BLACK);
}

bool GameRuler::isKingInCheck(array2d<Tile, 8, 8> board, Color color)
{
    auto king = this->getKing(color);
    return king->isCheck(board, king->getX(), king->getY());
}

bool GameRuler::isKingInCheckAfterMove(array2d<Tile, 8, 8> board, std::shared_ptr<Piece> piece, bool canMove,
                                       int x, int y)
{
    if (canMove && piece->getType() != PieceType::KING)
    {
        auto fake_board = board;
        std::shared_ptr<Piece> tmp = game->getPieceHandler().makeCopy(piece);
        fake_board[x][y].setPiece(tmp);
        fake_board[tmp->getX()][tmp->getY()].setPiece(nullptr);
        tmp->setX(x);
        tmp->setY(y);
        return isKingInCheck(fake_board, (Color)piece->getColor());
    }
    return false;
}

bool GameRuler::isKingInCheckMate(array2d<Tile, 8, 8> board, Color color)
{
    if (isKingInCheck(board, color))
    {
        for (auto piece : this->game->getAlivePieces())
        {
            try
            {
                if (piece->getColor() == color && piece->getValidMoves(board).size() > 0)
                    return false;
            }
            catch (const std::exception &e)
            {
                // piece can't move
                continue;
            }
        }
        return true;
    }
    return false;
}

bool GameRuler::isKingInStaleMate(array2d<Tile, 8, 8> board, Color color)
{
    bool inCheck = isKingInCheck(board, color);
    if (!inCheck)
    {
        for (auto piece : this->game->getAlivePieces())
        {
            try
            {
                if (piece->getColor() == color && piece->getValidMoves(board).size() > 0)
                    return false;
            }
            catch (const std::exception &e)
            {
                // piece can't move
                continue;
            }
        }
    }
    return inCheck ? false : true;
}

std::shared_ptr<King> GameRuler::getKing(Color color) const
{
    return color == Color::WHITE ? whiteKing : blackKing;
}
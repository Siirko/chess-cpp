#include "../includes/gameruler.hpp"
#include "../includes/board/board.hpp"
#include "../includes/pieces/bishop.hpp"
#include "../includes/pieces/knight.hpp"
#include "../includes/pieces/pawn.hpp"
#include "../includes/pieces/piece.hpp"
#include "../includes/pieces/queen.hpp"
#include "../includes/pieces/roi.hpp"
#include "../includes/pieces/tower.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <vector>

void GameRuler::setGame(const Game *game)
{
    this->game = game;
    whiteKing = game->getWhiteKing();
    blackKing = game->getBlackKing();
}

bool GameRuler::isKingInCheck(array2d<Tile, 8, 8> board, Color color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].getPiece() != nullptr && board[i][j].getPiece()->getType() != PieceType::KING &&
                board[i][j].getPiece()->getColor() != color)
            {
                auto ennemy_piece = board[i][j].getPiece();
                if (ennemy_piece
                        ->isValidMove(board, this->getKing(color)->getX(), this->getKing(color)->getY())
                        .valid_move)
                    return true;
            }
        }
    }
    return false;
}

bool GameRuler::isKingInCheckAfterMove(array2d<Tile, 8, 8> board, std::shared_ptr<Piece> piece, bool canMove,
                                       int x, int y)
{
    if (canMove && piece->getType() != PieceType::KING)
    {
        auto fakeBoard = board;
        std::shared_ptr<Piece> tmp = game->getPieceHandler().makeCopy(piece);
        fakeBoard[x][y].setPiece(tmp);
        fakeBoard[tmp->getX()][tmp->getY()].setPiece(nullptr);
        tmp->setX(x);
        tmp->setY(y);
        auto king = this->getKing((Color)piece->getColor());
        return king->isCheck(fakeBoard, king->getX(), king->getY());
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
                if (piece->getColor() == color && piece->canMove(board))
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
                if (piece->getColor() == color && piece->canMove(board))
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

std::shared_ptr<Roi> GameRuler::getKing(Color color) const
{
    return color == Color::WHITE ? whiteKing : blackKing;
}
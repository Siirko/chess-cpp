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
            auto piece = board[i][j].getPiece();
            if (piece != nullptr)
            {
                if (piece->getType() == PieceType::KING)
                    continue;

                switch (color)
                {
                case Color::WHITE:
                    if (piece->getColor() == Color::BLACK)
                    {
                        if (piece->isValidMove(board, whiteKing->getX(), whiteKing->getY()).valid_move)
                        {
                            return true;
                        }
                    }
                    break;
                case Color::BLACK:
                    if (piece->getColor() == Color::WHITE)
                    {
                        if (piece->isValidMove(board, blackKing->getX(), blackKing->getY()).valid_move)
                        {
                            // i have no idea why i need to check only for
                            // for this color but it somehow works idk
                            if (!blackKing->isCheck(board, i, j))
                                return true;
                        }
                    }
                    break;
                }
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
        array2d<Tile, 8, 8> fakeBoard = board;
        std::shared_ptr<Piece> tmp = game->getPieceHandler().makeCopy(piece);
        fakeBoard[x][y].setPiece(tmp);
        fakeBoard[tmp->getX()][tmp->getY()].setPiece(nullptr);
        tmp->setX(x);
        tmp->setY(y);
        return piece->getColor() == Color::WHITE ? isKingInCheck(fakeBoard, Color::WHITE)
                                                 : isKingInCheck(fakeBoard, Color::BLACK);
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
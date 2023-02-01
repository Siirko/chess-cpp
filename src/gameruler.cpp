#include "../includes/gameruler.hpp"
#include "../includes/board/board.hpp"
#include "../includes/pieces/piece.hpp"
#include "../includes/pieces/roi.hpp"
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

bool GameRuler::isKingInCheck(std::array<std::array<Tile, 8>, 8> board, Color color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].getPiece() != nullptr)
            {
                switch (color)
                {
                case Color::WHITE:
                    if (board[i][j].getPiece()->getColor() == Color::BLACK)
                    {
                        if (board[i][j]
                                .getPiece()
                                ->isValidMove(board, whiteKing->getX(), whiteKing->getY())
                                .valid_move)
                        {
                            return true;
                        }
                    }
                    break;
                case Color::BLACK:
                    if (board[i][j].getPiece()->getColor() == Color::WHITE)
                    {
                        if (board[i][j]
                                .getPiece()
                                ->isValidMove(board, blackKing->getX(), blackKing->getY())
                                .valid_move)
                        {
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

bool GameRuler::isKingInCheck(std::array<std::array<Tile, 8>, 8> board, Color color,
                              std::shared_ptr<Roi> king)
{
    for (auto piece : this->game->getAlivePieces())
    {
        if (piece->getColor() == color)
        {
            if (piece->isValidMove(board, king->getX(), king->getY()).valid_move)
                return true;
        }
    }
    return false;
}

bool GameRuler::isKingInCheckAfterMove(std::array<std::array<Tile, 8>, 8> board, std::shared_ptr<Piece> piece,
                                       bool canMove, int x, int y)
{
    if (canMove)
    {
        // fake board
        std::array<std::array<Tile, 8>, 8> fakeBoard = board;
        fakeBoard[x][y].setPiece(piece);
        fakeBoard[piece->getX()][piece->getY()].setPiece(nullptr);
        if (piece->getType() == PieceType::KING)
        {
            // make a copy
            std::shared_ptr<Roi> king = std::make_shared<Roi>(*std::dynamic_pointer_cast<Roi>(piece));
            king->setX(x);
            king->setY(y);
            return piece->getColor() == Color::WHITE ? isKingInCheck(fakeBoard, Color::WHITE, king)
                                                     : isKingInCheck(fakeBoard, Color::BLACK, king);
        }
        else
            return piece->getColor() == Color::WHITE ? isKingInCheck(fakeBoard, Color::WHITE)
                                                     : isKingInCheck(fakeBoard, Color::BLACK);
    }

    return false;
}

bool GameRuler::isKingInCheckMate(std::array<std::array<Tile, 8>, 8> board, Color color)
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

bool GameRuler::isKingInStaleMate(std::array<std::array<Tile, 8>, 8> board, Color color)
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
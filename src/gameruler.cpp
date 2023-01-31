#include "../includes/gameruler.hpp"
#include "../includes/board/board.hpp"
#include "../includes/pieces/piece.hpp"
#include "../includes/pieces/roi.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <vector>

void GameRuler::setWhiteKing(std::shared_ptr<Roi> &&king)
{
    // copy reference to put in a unique_ptr in whiteKing
    whiteKing = std::move(king);
}
void GameRuler::setBlackKing(std::shared_ptr<Roi> &&king)
{
    // copy reference to put in a unique_ptr in blackKing
    blackKing = std::move(king);
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
                                .first)
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
                                .first)
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
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].getPiece() != nullptr)
            {
                if (board[i][j].getPiece()->isValidMove(board, king->getX(), king->getY()).first)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GameRuler::isKingInCheckAfterMove(std::array<std::array<Tile, 8>, 8> board, std::shared_ptr<Piece> piece,
                                       int x, int y)
{
    if (piece->isValidMove(board, x, y).first)
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
        // check if king can move to a safe tile
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                bool result;
                if (color == Color::WHITE)
                {
                    try
                    {
                        result =
                            whiteKing->isValidMove(board, whiteKing->getX() + i, whiteKing->getY() + j).first;
                    }
                    catch (const std::exception &e)
                    {
                        // king can't move
                        return true;
                    }
                    if (result)
                        return false;
                }
                else
                {
                    try
                    {
                        result =
                            whiteKing->isValidMove(board, whiteKing->getX() + i, whiteKing->getY() + j).first;
                    }
                    catch (const std::exception &e)
                    {
                        // king can't move
                        return true;
                    }
                    if (result)
                        return false;
                }
            }
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j].getPiece() != nullptr)
                {
                    switch (color)
                    {
                    case Color::WHITE:
                        if (board[i][j].getPiece()->getColor() == Color::WHITE)
                        {
                            if (board[i][j].getPiece()->isValidMove(board, i, j).first)
                            {
                                return false;
                            }
                        }
                        break;
                    case Color::BLACK:
                        if (board[i][j].getPiece()->getColor() == Color::BLACK)
                        {
                            if (board[i][j].getPiece()->isValidMove(board, i, j).first)
                            {
                                return false;
                            }
                        }
                        break;
                    }
                }
            }
        }
        return true;
    }
    return false;
}

bool GameRuler::isKingInStaleMate(std::array<std::array<Tile, 8>, 8> board, Color color)
{
    if (!isKingInCheck(board, color))
    {
        return true;
    }
    return false;
}
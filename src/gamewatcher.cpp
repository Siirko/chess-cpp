#include "../includes/gamewatcher.hpp"
#include "../includes/board/board.hpp"
#include "../includes/pieces/piece.hpp"
#include "../includes/pieces/roi.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <vector>

// singleton class

void GameWatcher::setWhiteKing(std::shared_ptr<Roi> &&king)
{
    // copy reference to put in a unique_ptr in whiteKing
    whiteKing = std::move(king);
}
void GameWatcher::setBlackKing(std::shared_ptr<Roi> &&king)
{
    // copy reference to put in a unique_ptr in blackKing
    blackKing = std::move(king);
}

bool GameWatcher::isKingInCheck(std::array<std::array<Tile, 8>, 8> board, Color color)
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

bool GameWatcher::isKingInCheckMate(std::array<std::array<Tile, 8>, 8> board, Color color)
{
    if (isKingInCheck(board, color))
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

bool GameWatcher::isKingInStaleMate(std::array<std::array<Tile, 8>, 8> board, Color color)
{
    if (!isKingInCheck(board, color))
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
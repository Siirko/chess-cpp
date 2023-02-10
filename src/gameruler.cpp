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

/**
 * @brief Check if the king is in check for the given color and board
 */
bool GameRuler::isKingInCheck(array2d<Tile, 8, 8> board, Color color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            auto ennemy_piece = board[i][j].getPiece();
            if (ennemy_piece == nullptr || ennemy_piece->getType() == PieceType::KING ||
                ennemy_piece->getColor() == color)
                continue;
            auto king = color == Color::WHITE ? whiteKing : blackKing;
            auto ennemy_king = color == Color::WHITE ? blackKing : whiteKing;
            if (ennemy_piece->isValidMove(board, king->getX(), king->getY()).valid_move)
            {
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
        array2d<Tile, 8, 8> fakeBoard = board;
        std::shared_ptr<Piece> tmp = game->getPieceHandler().makeCopy(piece);
        fakeBoard[x][y].setPiece(tmp);
        fakeBoard[tmp->getX()][tmp->getY()].setPiece(nullptr);
        tmp->setX(x);
        tmp->setY(y);
        return isKingInCheck(fakeBoard, (Color)piece->getColor());
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
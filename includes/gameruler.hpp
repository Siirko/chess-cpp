#pragma once
#include "board/board.hpp"
#include "game.hpp"
#include "pieces/piece.hpp"
#include "pieces/roi.hpp"
#include <array>
#include <memory>
#include <vector>

// singleton class that holds kings references and check if they are in check
class GameRuler
{
  private:
    GameRuler() = default;
    GameRuler(const GameRuler &) = delete;
    GameRuler &operator=(const GameRuler &) = delete;
    const Game *game = nullptr;
    std::shared_ptr<Roi> whiteKing = nullptr;
    std::shared_ptr<Roi> blackKing = nullptr;

  public:
    static GameRuler &getInstance()
    {
        static GameRuler instance;
        return instance;
    }
    void setGame(const Game *game);
    bool isKingInCheck(array2d<Tile, 8, 8> board, Color color);
    bool isKingInCheckAfterMove(array2d<Tile, 8, 8> board, std::shared_ptr<Piece> piece, bool canMove, int x,
                                int y);
    bool isKingInCheckMate(array2d<Tile, 8, 8> board, Color color);
    bool isKingInStaleMate(array2d<Tile, 8, 8> board, Color color);
};
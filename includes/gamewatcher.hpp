#pragma once
#include "board/board.hpp"
#include "game.hpp"
#include "pieces/piece.hpp"
#include "pieces/roi.hpp"
#include <array>
#include <memory>
#include <vector>

// singleton class that holds kings references and check if they are in check
class GameWatcher
{
  private:
    GameWatcher() = default;
    GameWatcher(const GameWatcher &) = delete;
    GameWatcher &operator=(const GameWatcher &) = delete;
    std::shared_ptr<Roi> whiteKing;
    std::shared_ptr<Roi> blackKing;

  public:
    static GameWatcher &getInstance()
    {
        static GameWatcher instance;
        return instance;
    }
    void setWhiteKing(std::shared_ptr<Roi> &&king);
    void setBlackKing(std::shared_ptr<Roi> &&king);
    bool isKingInCheck(std::array<std::array<Tile, 8>, 8> board, Color color);
    bool isKingInCheck(std::array<std::array<Tile, 8>, 8> board, Color color, std::shared_ptr<Roi> king);
    bool isKingInCheckAfterMove(std::array<std::array<Tile, 8>, 8> board, std::shared_ptr<Piece> piece, int x,
                                int y);
    bool isKingInCheckMate(std::array<std::array<Tile, 8>, 8> board, Color color);
    bool isKingInStaleMate(std::array<std::array<Tile, 8>, 8> board, Color color);
};
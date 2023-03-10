#pragma once
#include "board/board.hpp"
#include "game.hpp"
#include "pieces/king.hpp"
#include "pieces/piece.hpp"
#include <array>
#include <memory>
#include <vector>

/**
 * @brief GameRuler class is responsible for checking if a king is in check,
 * checkmate, or stalemate.
 * @note This class is a singleton class.
 */
class GameRuler
{
  private:
    GameRuler() = default;
    GameRuler(const GameRuler &) = delete;
    GameRuler &operator=(const GameRuler &) = delete;
    const Game *game = nullptr;
    std::shared_ptr<King> whiteKing = nullptr;
    std::shared_ptr<King> blackKing = nullptr;

  public:
    /**
     * @brief Gets the instance of the GameRuler singleton class.
     * @return The instance of the GameRuler singleton class.
     * @note This is a singleton class, so there can only be one instance of it.
     */
    static GameRuler &getInstance()
    {
        static GameRuler instance;
        return instance;
    }
    /**
     * @brief Sets the game to use for the GameRuler singleton class.
     * @param game The game to use for the GameRuler singleton class.
     */
    void setGame(const Game *game);
    /**
     * @brief Checks if the king of the given color is in check.
     * @param board The board to check if the king is in check.
     * @param color The color of the king to check if it is in check.
     * @return True if the king of the given color is in check, false otherwise.
     */
    bool isKingInCheck(array2d<Tile, 8, 8> board, Color color);
    /**
     * @brief Checks if the king of the given color is in check after the given move.
     * @param board The board to check if the king is in check.
     * @param piece The piece to move.
     * @param canMove True if the piece can move, false otherwise.
     * @param x The x coordinate to move the piece to.
     * @param y The y coordinate to move the piece to.
     * @return True if the king of the given color is in check after the given move,
     * false otherwise.
     */
    bool isKingInCheckAfterMove(array2d<Tile, 8, 8> board, std::shared_ptr<Piece> piece, bool canMove, int x,
                                int y);
    /**
     * @brief Checks if the king of the given color is in checkmate.
     * @param board The board to check if the king is in checkmate.
     * @param color The color of the king to check if it is in checkmate.
     * @return True if the king of the given color is in checkmate, false otherwise.
     */
    bool isKingInCheckMate(array2d<Tile, 8, 8> board, Color color);
    /**
     * @brief Checks if the king of the given color is in stalemate.
     * @param board The board to check if the king is in stalemate.
     * @param color The color of the king to check if it is in stalemate.
     * @return True if the king of the given color is in stalemate, false otherwise.
     */
    bool isKingInStaleMate(array2d<Tile, 8, 8> board, Color color);
    /**
     * @brief Gets the king of the given color.
     * @param color The color of the king to get.
     * @return The king of the given color.
     */
    std::shared_ptr<King> getKing(Color color) const;
    /**
     * @brief Gets the game reference to use for the GameRuler singleton class.
     * @return The game to use for the GameRuler singleton class.
     */
    Game &getGame() const { return *const_cast<Game *>(game); }
};
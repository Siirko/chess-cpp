#pragma once
#include "pieces/piece.hpp"
#include <memory>
#include <string>

/**
 * @brief PieceHandler class class is responsible for handling all the pieces in
 * the game. It is responsible for moving pieces, creating copies of pieces, and
 * promoting pieces.
 */

class Piece;
class Game;
class PieceHandler
{
  public:
    /**
     * @brief Populates the board with pieces based on the FEN string.
     * @param game The game to populate the board with pieces.
     * @param fen The FEN string to use to populate the board.
     */
    void forsythGeneration(Game &game, std::string fen);
    /**
     * @brief Moves a piece from one tile to another.
     * @param game The game to move the piece in.
     * @param piece The piece to move.
     * @param x The x coordinate to move the piece to.
     * @param y The y coordinate to move the piece to.
     * @return True if the piece was moved, false otherwise.
     */
    bool movePieceAt(Game &game, std::shared_ptr<Piece> piece, int x, int y);
    /**
     * @brief Gets the piece at the given coordinates.
     * @param game The game to get the piece from.
     * @param x The x coordinate to get the piece from.
     * @param y The y coordinate to get the piece from.
     * @return The piece at the given coordinates.
     */
    std::shared_ptr<Piece> getPieceAt(Game &game, int x, int y);
    /**
     * @brief Promotes the given piece to the given type.
     * @param toPromote The piece to promote.
     * @param type The type to promote the piece to.
     */
    void promotePiece(std::shared_ptr<Piece> &toPromote, PieceType type);
};
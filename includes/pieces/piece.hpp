#pragma once
#include "../utilities.hpp"
#include <array>
#include <memory>
#include <vector>

/**
 * @brief Piece class is the base class for all pieces.
 * @note This class is abstract.
 */

/**
 * @brief Enum representing the color of a piece.
 */
enum Color
{
    BLACK = 0,
    WHITE = 1
};

/**
 * @brief Enum representing the type of a piece.
 */
enum PieceType
{
    PAWN = 'P',
    ROOK = 'R',
    KNIGHT = 'N',
    BISHOP = 'B',
    QUEEN = 'Q',
    KING = 'K'
};

class Tile;
class Piece : public std::enable_shared_from_this<Piece>
{
  private:
    int x;
    int y;
    int color;
    bool firstMove;
    int num_moves = 0;

  public:
    struct PieceMove;
    Piece(int x, int y, int color);
    virtual ~Piece();
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    void setColor(int color);
    int getColor() const;
    bool getFirstMove() const;
    void setFirstMove(bool firstMove);
    /**
     * @brief Get the type of the piece.
     * @return The type of the piece.
     */
    char getType();
    int getNumMoves() const;
    void updateNumMoves();
    /**
     * @brief Get the valid moves of the piece.
     * @param board The board to check the valid moves on.
     * @return The valid moves of the piece.
     */
    std::vector<std::pair<int, int>> getValidMoves(array2d<Tile, 8, 8> board);
    /**
     * @brief Apply checks to the valid moves of the piece.
     * @param board The board to check the valid moves on.
     * @return True if the piece can move, false otherwise.
     */
    bool beforeCheckMove(array2d<Tile, 8, 8> board, PieceMove result, int x, int y);
    /**
     * @brief Check if the move is valid.
     * @param board The board to check the move on.
     * @param x The x coordinate of the move.
     * @param y The y coordinate of the move.
     * @param beforeCheck apply checks to the move if True.
     * @return True if the move is valid, false otherwise.
     */
    virtual PieceMove isValidMove(array2d<Tile, 8, 8> board, int x, int y, bool beforeCheck) = 0;
    /**
     * @brief Iterate through the valid moves of the piece.
     * @param board The board to check the valid moves on.
     * @return True if the piece can move, false otherwise.
     */
    bool canMove(array2d<Tile, 8, 8> board);
    friend std::ostream &operator<<(std::ostream &os, const Piece &piece);
    std::shared_ptr<Piece> getptr() { return shared_from_this(); }
};

struct Piece::PieceMove
{
    bool valid_move;
    std::shared_ptr<Piece> eaten_piece;
};
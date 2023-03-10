#pragma once
#include "../../pieces/piece.hpp"
#include <regex>
#include <string>
/**
 * @brief Parser class is responsible for parsing user input through the CLI.
 */

class Parser
{
  public:
    struct Coord;
    struct UpdateCoords;
    /**
     * @brief Check if the input is a castling move.
     * @param input The input to check.
     * @return True if the input is a castling move, false otherwise.
     */
    static bool checkCastling(std::string input);
    /**
     * @brief Receive the input from the user and return it if it is valid.
     */
    static std::string getInputMove();
    /**
     * @brief Receive the input from the user and return the piece type to promote to if it is valid.
     */
    static PieceType getInputPromotion();
    /**
     * @brief Convert the input to coordinates.
     * @param input The input to convert.
     * @param color The color of the player.
     * @return The coordinates of the input.
     */
    static UpdateCoords parseInput(std::string input, Color color);
};

struct Parser::Coord
{
    int x;
    int y;
};

struct Parser::UpdateCoords
{
    Coord from;
    Coord to;
};
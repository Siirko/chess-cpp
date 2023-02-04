#pragma once
#include "../../pieces/piece.hpp"
#include <regex>
#include <string>

class Parser
{
  public:
    struct Coord;
    struct UpdateCoords;
    static bool checkCastling(std::string input);
    static std::string getInput();
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
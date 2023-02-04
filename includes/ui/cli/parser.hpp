#pragma once
#include <string>

class Parser
{
  public:
    struct Coord;
    struct UpdateCoords;
    static std::string getInput();
    static UpdateCoords parseInput(std::string input);
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

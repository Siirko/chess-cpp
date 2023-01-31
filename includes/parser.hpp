#pragma once
#include <string>

class Parser
{
  public:
    struct Coord
    {
        int x;
        int y;
    };

    struct UpdateCoords
    {
        Coord from;
        Coord to;
    };

    static std::string getInput();
    static UpdateCoords parseInput(std::string input);
};

#include "../../../includes/ui/cli/parser.hpp"
#include <iostream>
#include <string>

const std::regex pattern("[a-h][1-8][a-h][1-8]");
const std::regex big_rook_pattern("(O|o|0)-(O|o|0)-(O|o|0)");
const std::regex little_rook_pattern("(O|o|0)-(O|o|0)");

std::string Parser::getInput()
{
    std::string input;
    std::cout << "Enter your move: ";
    std::cin >> input;
    if (input == "/quit")
        return input;
    if (!std::regex_match(input, pattern) && !std::regex_match(input, big_rook_pattern) &&
        !std::regex_match(input, little_rook_pattern))
    {
        std::cout << "Invalid input" << std::endl;
        return "";
    }
    return input;
}

Parser::UpdateCoords Parser::parseInput(std::string input, Color color)
{
    UpdateCoords coords;
    if (std::regex_match(input, big_rook_pattern))
    {
        if (color == Color::WHITE)
            coords = UpdateCoords{Coord{4, 0}, Coord{0, 0}};
        else
            coords = UpdateCoords{Coord{4, 7}, Coord{0, 7}};
    }
    else if (std::regex_match(input, little_rook_pattern))
    {
        if (color == Color::WHITE)
            coords = UpdateCoords{Coord{4, 0}, Coord{7, 0}};
        else
            coords = UpdateCoords{Coord{4, 7}, Coord{7, 7}};
    }
    else
    {
        int x = input[0] - 'a';
        int y = input[1] - '1';
        int x2 = input[2] - 'a';
        int y2 = input[3] - '1';
        coords = UpdateCoords{Coord{x, y}, Coord{x2, y2}};
    }
    return coords;
}
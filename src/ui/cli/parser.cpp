#include "../../../includes/ui/cli/parser.hpp"
#include <iostream>
#include <regex>
#include <string>

std::string Parser::getInput()
{
    std::string input;
    std::cout << "Enter your move: ";
    std::cin >> input;
    if (input == "/exit")
        return input;
    std::regex pattern("[a-h][1-8][a-h][1-8]");
    /*
    std::regex little_rook_pattern("(O|o|0)-(O|o|0)");
    std::regex big_rook_pattern("(O|o|0)-(O|o|0)-(O|o|0)");
    */
    if (!std::regex_match(input, pattern))
    {
        std::cout << "Invalid input" << std::endl;
        return "";
    }
    return input;
}

Parser::UpdateCoords Parser::parseInput(std::string input)
{
    int x = input[0] - 'a';
    int y = input[1] - '1';
    int x2 = input[2] - 'a';
    int y2 = input[3] - '1';
    return UpdateCoords{Coord{x, y}, Coord{x2, y2}};
}
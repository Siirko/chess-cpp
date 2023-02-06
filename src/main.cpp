#include "../includes/ui/cli/cli.hpp"
#include "../includes/ui/gui/gui.hpp"
#include <iostream>
#include <string>

int main(void)
{
    std::string input;
    std::cout << "Choose your interface (cli/gui): ";
    std::cin >> input;
    if (input == "cli")
    {
        CLI cli;
        cli.run();
    }
    else if (input == "gui")
    {
        GUI gui;
        gui.run();
    }
    else
    {
        std::cout << "Invalid input, defaulting to CLI" << std::endl;
        CLI cli;
        cli.run();
    }
}

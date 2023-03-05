#include "../includes/ui/cli/cli.hpp"
#include "../includes/ui/gui/gui.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        CLI cli;
        cli.run();
    }
    else if (argc == 2)
    {
        std::string arg = argv[1];
        if (arg == "--gui")
        {
            GUI gui;
            gui.run();
        }
        else
        {
            std::cout << "Invalid argument" << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }
    return 0;
}

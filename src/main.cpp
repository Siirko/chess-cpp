#include "../includes/ui/cli/cli.hpp"
#ifdef WITH_GUI
#include "../includes/ui/gui/gui.hpp"
#endif
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
#ifdef WITH_GUI
    if (argc == 2)
    {
        std::string arg = argv[1];
        if (arg == "--gui")
        {
            GUI gui;
            gui.run();
        }
        else if (arg == "--cli")
        {
            CLI cli;
            cli.run();
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
        std::cout << "Usage: ./chess [--gui|--cli]" << std::endl;
        return 1;
    }
#else
    CLI cli;
    cli.run();
#endif
    return 0;
}

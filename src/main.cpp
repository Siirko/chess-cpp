#include "../includes/ui/cli/cli.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    CLI cli = CLI();
    cli.run();
    return 0;
}

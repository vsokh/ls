#include "CommandLineArgsParser.h"
#include "DirEntry.h"

#include <iostream>
#include <exception>

int main(int argc, char** argv)
{
    if (argc < 1) {
        return -1;
    }
    try {
        using namespace ls;

        const Options possibleOptions{"l", "a"};
        OptionsParser optionsParser{possibleOptions};

        CommandLineArgsParser argsParser{optionsParser};
        auto [options, entries] = argsParser.parse(argc, argv);

        for (auto opt : options) {
            std::cout << "option: " << opt << '\n';
        }

        for (auto entry : entries) {
            std::cout << "entry: " << entry._name << '\n';
        }
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}


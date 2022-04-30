#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <string_view>

class DirEntry;

namespace ls {

using Option = std::string;
using Options = std::vector<Option>;

class OptionsParser {
public:
    explicit OptionsParser(Options  possibleOptions);
    std::optional<Options> parse(std::string_view opt);

private:
    Options _possibleOptions{};
};

class CommandLineArgsParser {
public:
    explicit CommandLineArgsParser(OptionsParser optionsParser);
    std::tuple<Options, std::vector<DirEntry>> parse(int argc, char** argv);

private:
    OptionsParser _optionsParser;
};

} // namespace ls

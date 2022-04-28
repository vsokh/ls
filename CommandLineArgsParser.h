#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <optional>

// TODO: make a visitor class
struct DirEntry {
    DirEntry(std::string name) : _name{name} {}
    std::string _name{};
};

namespace ls {

using Option = std::string;
using Options = std::vector<Option>;

class OptionsParser {
public:
    OptionsParser(const Options& possibleOptions);
    std::optional<Options> parse(const std::string& opt);

private:
    static bool startsWithDash(const std::string& opt);
    std::string removeDash(const std::string& opt);
    bool contains(const std::string& opt);
    Options split(const std::string& opt);

private:
    Options _possibleOptions{};
};

class CommandLineArgsParser {
public:
    CommandLineArgsParser(const OptionsParser& optionsParser);
    std::tuple<Options, std::vector<DirEntry>> parse(int argc, char** argv);

private:
    OptionsParser _optionsParser;
};

} // namespace ls

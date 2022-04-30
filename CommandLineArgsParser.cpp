#include "CommandLineArgsParser.h"
#include "DirEntry.h"

#include <utility>

namespace {

bool startsWith(std::string_view str1, std::string_view str2) {
    return str1.compare(0, str2.size(), str2, 0, str2.size()) == 0;
}

std::string remove(std::string_view str, std::size_t count) {
    return {str.begin() + count, str.end()};
}

bool contains(const ls::Options& possibleOptions, std::string_view opt) {
    return std::find(possibleOptions.begin(),
                     possibleOptions.end(), opt) != possibleOptions.end();
}

std::vector<std::string> split(std::string str, std::string_view delimiter)
{
    std::vector<std::string> result;
    auto pos = str.find(delimiter);
    while (pos != std::string::npos) {
        auto end = str.begin() + pos;

        result.emplace_back(str.begin(), end);
        str.erase(end + 1);

        pos = str.find(delimiter);
    }
    if (!str.empty()) {
        auto end = str.begin() + pos;
        result.emplace_back(str.begin(), end);
    }
    return result;
}
}

namespace ls {

OptionsParser::OptionsParser(Options possibleOptions)
        : _possibleOptions{std::move(possibleOptions)} {}

std::optional<Options> OptionsParser::parse(std::string_view opt) {
    std::string dash = "-";
    if (!startsWith(opt, dash)) {
        return std::nullopt;
    }
    if (auto noDashOpt = remove(opt, dash.size());
            noDashOpt.size() == 1) {
        if (contains(_possibleOptions, noDashOpt)) {
            return Options{noDashOpt};
        }
    } else {
        Options options;
        auto opts = split(noDashOpt, "");
        for (const auto& tokenOpt : opts)
        {
            if (contains(_possibleOptions, tokenOpt)) {
                options.push_back(tokenOpt);
            }
        }
    }
    return std::nullopt;
}

CommandLineArgsParser::CommandLineArgsParser(OptionsParser optionsParser)
    : _optionsParser{std::move(optionsParser)}
{}

std::tuple<Options, std::vector<DirEntry>>
CommandLineArgsParser::parse(int argc, char** argv)
{
    Options options;
    std::vector<DirEntry> entries;
    for (int argIdx = 1; argIdx < argc; ++argIdx)
    {
        std::string arg{argv[argIdx]};
        if (auto opts = _optionsParser.parse(arg)) {
            options.assign(opts.value().begin(), opts.value().end());
        } else {
            entries.emplace_back(arg);
        }
    }
    return {options, entries};
}

} // namespace ls

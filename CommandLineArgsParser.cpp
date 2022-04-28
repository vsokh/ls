#include "CommandLineArgsParser.h"

namespace ls {

OptionsParser::OptionsParser(const Options& possibleOptions)
    : _possibleOptions{possibleOptions}
{}

std::optional<Options> OptionsParser::parse(const std::string& opt)
{
    if (!startsWithDash(opt)) {
        return std::nullopt;
    }
    if (auto noDashOpt = removeDash(opt);
             noDashOpt.size() == 1) {
        if (contains(noDashOpt)) {
            return Options{noDashOpt};
        }
    } else {
        return split(noDashOpt);
    }
    return std::nullopt;
}

bool OptionsParser::startsWithDash(const std::string& opt)
{
    return opt.compare(0, 1, "-", 0, 1) == 0;
}

std::string OptionsParser::removeDash(const std::string& opt)
{
    return {opt.begin()+1, opt.end()};
}

bool OptionsParser::contains(const std::string& opt)
{
    return std::find(_possibleOptions.begin(),
                     _possibleOptions.end(), opt) != _possibleOptions.end();
}

Options OptionsParser::split(const std::string& opt)
{
    Options options;
    std::for_each(opt.begin(), opt.end(),
                  [this, &options](char ch)
                  {
                      std::string tmpOpt{ch};
                      if (contains(tmpOpt)) {
                          options.emplace_back(std::move(tmpOpt));
                      }
                  });
    return options;
}

CommandLineArgsParser::CommandLineArgsParser(const OptionsParser& optionsParser)
    : _optionsParser{optionsParser}
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
            entries.emplace_back(DirEntry{arg});
        }
    }
    return {options, entries};
}

} // namespace ls

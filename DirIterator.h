#pragma once

#include <exception>
#include <variant>
#include <vector>
#include <string>

#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>
#include <unistd.h>
#include <stdint.h>
#include "DirEntry.h"

class DirEntry;

namespace ls {

class DirIterator
{
public:
    explicit DirIterator(std::string dirname);
    ~DirIterator();

    struct iter
    {
        iter() = default;

        iter(DIR* dirp, std::string dirname);
        bool operator!=(const iter& rhs) const noexcept;
        iter& operator++();
        DirEntry operator*() const noexcept;

    private:
        DirEntry nextEntry();

    private:
        DIR* _dirp{};
        std::string _dirname{};
        DirEntry _lastEntry{};
    };

    iter begin();
    iter end();

private:
    std::string _dirname;
    DIR* _dirp{};
};

} // namespace ls

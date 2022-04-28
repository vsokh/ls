#pragma once

#include <iostream>
#include <exception>
#include <variant>
#include <vector>

#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>
#include <unistd.h>
#include <stdint.h>

namespace ls {

class DirEntry {
public:
    DirEntry() = default;

    explicit DirEntry(struct dirent *entry);

    bool operator!=(const DirEntry &rhs) const noexcept;

    std::string path() const noexcept;

    void status() const;

private:
    struct dirent *_entry{};
};

} // namespace ls


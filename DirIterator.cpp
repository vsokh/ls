#include "DirIterator.h"

#include <utility>
#include "DirEntry.h"

namespace ls {

DirIterator::DirIterator(std::string dirname)
    : _dirname{std::move(dirname)}
    , _dirp{opendir(_dirname.c_str())}
{}

DirIterator::~DirIterator() {
    if (_dirp) {
        closedir(_dirp);
    }
}

DirIterator::iter::iter(DIR* dirp, std::string dirname)
    : _dirp{dirp}
    , _dirname{std::move(dirname)}
    , _lastEntry{nextEntry()} {}

DirIterator::iter DirIterator::begin() { return iter{_dirp, _dirname}; }
DirIterator::iter DirIterator::end()   { return iter{}; }

bool DirIterator::iter::operator!=(const iter& rhs) const noexcept {
    return _lastEntry != rhs._lastEntry;
}

DirIterator::iter& DirIterator::iter::operator++() {
    _lastEntry = nextEntry();
    return *this;
}

DirEntry DirIterator::iter::operator*() const noexcept {
    return _lastEntry;
}

DirEntry DirIterator::iter::nextEntry() {
    if (_dirp) {
        if (auto dp = readdir(_dirp); dp != nullptr) {
            chdir(_dirname.c_str());
            DirEntry entry{dp}; // Get all info - use stat.
            chdir("..");
            return entry;
        }
    }
    return DirEntry{};
}

} // namespace ls

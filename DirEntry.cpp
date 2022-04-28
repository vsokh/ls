#include "DirEntry.h"

namespace ls {

DirEntry::DirEntry(struct dirent* entry)
    : _entry{entry} {}

bool DirEntry::operator!=(const DirEntry& rhs) const noexcept
{
    // TODO: Is this correct?
    return _entry != rhs._entry;
}

std::string DirEntry::path() const noexcept
{
    return _entry != nullptr ? _entry->d_name : "";
}

void DirEntry::status() const
{
    auto file = _entry->d_name;
    struct stat statbuf;
    struct passwd *pwd;
    struct group *grp;
    struct tm *tm;
    char datestring[256];

    if (stat(file, &statbuf) == -1) {
        return;
    }

    // TYPE, PERMISSIONS, NUM OF LINKS
    /* Print out type, permissions, and number of links. */
    printf(" (%3o)", statbuf.st_mode & 0777);
    printf("%4d", statbuf.st_nlink);

    // OWNER
    /* Print out owner's name if it is found using getpwuid(). */
    if ((pwd = getpwuid(statbuf.st_uid)) != nullptr)
        printf(" %-8.8s", pwd->pw_name);
    else
        printf(" %-8d", statbuf.st_uid);

    // GROUP
    /* Print out group name if it is found using getgrgid(). */
    if ((grp = getgrgid(statbuf.st_gid)) != nullptr)
        printf(" %-8.8s", grp->gr_name);
    else
        printf(" %-8d", statbuf.st_gid);

    // SIZE
    /* Print size of file. */
    printf(" %9jd", (intmax_t) statbuf.st_size);


    tm = localtime(&statbuf.st_mtime);

    // TIME
    /* Get localized date string. */
    strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

    printf(" %s %s\n", datestring, file);
}

} // namespace ls

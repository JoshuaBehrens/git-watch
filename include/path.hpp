#ifndef _GIT_WATCH__INCLUDE__PATH_HPP
#define _GIT_WATCH__INCLUDE__PATH_HPP

#include <filesystem>
#include <optional>

namespace git_watch::path
{
    std::optional<std::filesystem::path> user_directory();
    std::optional<std::filesystem::path> config_directory();
    std::optional<std::filesystem::path> data_directory();
}

#endif // _GIT_WATCH__INCLUDE__PATH_HPP

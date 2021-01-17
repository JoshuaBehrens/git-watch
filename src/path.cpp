#include <algorithm>

#include "path.hpp"

std::string getenv_str(const char* query)
{
    auto result = getenv(query);

    return result == nullptr ? "" : result;
}

std::optional<std::filesystem::path> git_watch::path::user_directory()
{
    // @see https://docs.python.org/2.7/library/os.path.html#os.path.expanduser
    std::filesystem::path home(getenv_str("HOME"));

    if (std::filesystem::exists(home)) {
        return home;
    }

    home = getenv_str("USERPROFILE");

    if (std::filesystem::exists(home)) {
        return home;
    }

    home = getenv_str("HOMEDRIVE");
    home.append(getenv_str("HOMEPATH"));

    if (std::filesystem::exists(home)) {
        return home;
    }

    return {};
}

std::optional<std::filesystem::path> git_watch::path::config_directory()
{
    // @see https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
    std::filesystem::path config(getenv_str("XDG_CONFIG_HOME"));

    if (std::filesystem::exists(config)) {
        return config;
    }

    auto home{user_directory()};

    if (!home.has_value()) {
        return {};
    }

    auto result = home.value().append(".config");

    if (std::filesystem::exists(result)) {
        return result;
    }

    return {};
}

std::optional<std::filesystem::path> git_watch::path::data_directory()
{
    // @see https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
    std::filesystem::path data(getenv_str("XDG_DATA_HOME"));

    if (std::filesystem::exists(data)) {
        return data;
    }

    auto home{user_directory()};

    if (!home.has_value()) {
        return {};
    }

    auto result = home.value().append(".local").append("share");

    if (std::filesystem::exists(result)) {
        return result;
    }

    return {};
}

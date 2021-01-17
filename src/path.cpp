#include <algorithm>

#include "path.hpp"

namespace fs = std::filesystem;

using std::optional;
using std::string;

string getenv_str(const char* query)
{
    auto result = getenv(query);

    return result == nullptr ? "" : result;
}

optional<fs::path> git_watch::path::user_directory()
{
    // @see https://docs.python.org/2.7/library/os.path.html#os.path.expanduser
    fs::path home(getenv_str("HOME"));

    if (exists(home)) {
        return home;
    }

    home = getenv_str("USERPROFILE");

    if (exists(home)) {
        return home;
    }

    home = getenv_str("HOMEDRIVE");
    home.append(getenv_str("HOMEPATH"));

    if (exists(home)) {
        return home;
    }

    return {};
}

optional<fs::path> git_watch::path::config_directory()
{
    // @see https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
    fs::path config(getenv_str("XDG_CONFIG_HOME"));

    if (exists(config)) {
        return config;
    }

    auto home{user_directory()};

    if (!home.has_value()) {
        return {};
    }

    auto result = home.value().append(".config");

    if (exists(result)) {
        return result;
    }

    return {};
}

optional<fs::path> git_watch::path::data_directory()
{
    // @see https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
    fs::path data(getenv_str("XDG_DATA_HOME"));

    if (exists(data)) {
        return data;
    }

    auto home{user_directory()};

    if (!home.has_value()) {
        return {};
    }

    auto result = home.value().append(".local").append("share");

    if (exists(result)) {
        return result;
    }

    return {};
}

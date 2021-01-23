#include <iostream>
#include <filesystem>
#include "arguments.hpp"

int main(int argc, char const** argv) {
    namespace fs = std::filesystem;

    git_watch::arguments args;
    args.fill(argv, argc);

    if (args.help() || args.operation().empty()) {
        std::cout << args.usage() << std::endl;

        return args.help() ? 0 : 1;
    }

    fs::path config_dir(args.config_dir());

    if (!exists(config_dir)) {
        create_directories(config_dir);
    }

    std::cout << config_dir.generic_string() << std::endl;

    return 0;
}

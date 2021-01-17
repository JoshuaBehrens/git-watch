#include <iostream>
#include "path.hpp"

int main() {
    auto dataDir(
        git_watch::path::data_directory()
            .value_or(std::filesystem::current_path().append("data"))
            .append("git_watch")
    );

    if (!std::filesystem::exists(dataDir)) {
        std::filesystem::create_directories(dataDir);
    }

    std::cout << dataDir.generic_string() << std::endl;

    return 0;
}

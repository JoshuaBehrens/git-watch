#include <iostream>
#include "path.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::cout << git_watch::path::user_directory().value_or(std::filesystem::current_path()).generic_string() << std::endl;
    std::cout << git_watch::path::data_directory().value_or(std::filesystem::current_path()).generic_string() << std::endl;
    std::cout << git_watch::path::config_directory().value_or(std::filesystem::current_path()).generic_string() << std::endl;

    return 0;
}

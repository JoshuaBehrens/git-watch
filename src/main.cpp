#include <iostream>
#include <boost/program_options.hpp>
#include "path.hpp"

int main(int argc, char** argv) {
    boost::program_options::options_description desc("Allowed arguments and options");
    desc.add_options()
        ("help", "Show help message");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;

        return 0;
    }

    auto dataDir(
        git_watch::path::config_directory()
            .value_or(std::filesystem::current_path().append("config"))
            .append("git_watch")
    );

    if (!std::filesystem::exists(dataDir)) {
        std::filesystem::create_directories(dataDir);
    }

    std::cout << dataDir.generic_string() << std::endl;

    return 0;
}

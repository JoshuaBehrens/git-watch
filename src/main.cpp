#include <iostream>
#include <boost/program_options.hpp>
#include "path.hpp"

int main(int argc, char** argv) {
    namespace fs = std::filesystem;
    namespace bpo = boost::program_options;

    bpo::options_description desc("Allowed arguments and options");
    desc.add_options()
        ("help", "Show help message");

    bpo::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;

        return 0;
    }

    auto dataDir(
        git_watch::path::config_directory()
            .value_or(fs::current_path().append("config"))
            .append("git_watch")
    );

    if (!exists(dataDir)) {
        create_directories(dataDir);
    }

    std::cout << dataDir.generic_string() << std::endl;

    return 0;
}

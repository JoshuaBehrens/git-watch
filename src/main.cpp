#include <iostream>
#include <boost/program_options.hpp>
#include "path.hpp"

int main(int argc, char** argv) {
    namespace fs = std::filesystem;
    namespace bpo = boost::program_options;

    auto configDir(
        git_watch::path::config_directory()
            .value_or(fs::current_path().append("config"))
            .append("git_watch")
            .generic_string()
    );

    bpo::options_description desc("Allowed arguments and options");
    desc.add_options()
        ("help", "Show help message")
        ("config-dir", bpo::value<std::string>(&configDir)->default_value(configDir), "Set the configuration directory");

    auto configDirPath = fs::path(configDir);

    bpo::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;

        return 0;
    }

    if (!exists(configDirPath)) {
        create_directories(configDirPath);
    }

    std::cout << configDirPath.generic_string() << std::endl;

    return 0;
}

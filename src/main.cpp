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
    std::string operation;

    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Show help message")
        ("config-dir,c", bpo::value<std::string>(&configDir)->default_value(configDir), "Set the configuration directory")
        ("operation,o", bpo::value<std::string>(&operation), "Operation of choice");
    bpo::positional_options_description pdesc;
    pdesc.add("operation", 1);
    auto configDirPath = fs::path(configDir);

    bpo::variables_map vm;
    auto parser{bpo::command_line_parser(argc, argv)};

    store(parser.options(desc).run(), vm);
    store(parser.positional(pdesc).run(), vm);
    notify(vm);

    if (vm.count("help") || operation.empty()) {
        std::cout << "Usage " << argv[0] << " " << "operation [options]" << std::endl << desc << std::endl;

        return vm.count("help") ? 0 : 1;
    }

    if (!exists(configDirPath)) {
        create_directories(configDirPath);
    }

    std::cout << configDirPath.generic_string() << std::endl;

    return 0;
}

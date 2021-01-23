#include "arguments.hpp"

#include <filesystem>
#include <sstream>
#include <boost/program_options.hpp>
#include <path.hpp>

using namespace git_watch;

void arguments::fill(char const** arguments, int argument_count)
{
    namespace bpo = boost::program_options;
    namespace fs = std::filesystem;

    auto configDir(
        path::config_directory()
            .value_or(fs::current_path().append("config"))
            .append("git_watch")
            .generic_string()
    );
    std::string operation;

    bpo::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "Show help message")
            ("config-dir,c", bpo::value<std::string>(&_config_dir)->default_value(configDir), "Set the configuration directory")
            ("operation,o", bpo::value<std::string>(&_operation), "Operation of choice");
    bpo::positional_options_description pdesc;
    pdesc.add("operation", 1);
    auto configDirPath = fs::path(configDir);

    bpo::variables_map vm;
    auto parser{bpo::command_line_parser(argument_count, arguments)};

    store(parser.options(desc).run(), vm);
    store(parser.positional(pdesc).run(), vm);
    notify(vm);

    _help = vm.count("help");

    std::ostringstream usage;
    usage << "Usage " << arguments[0] << " " << "operation [options]" << std::endl << desc;
    _usage = usage.str();
}

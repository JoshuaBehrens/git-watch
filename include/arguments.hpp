#ifndef _GIT_WATCH__INCLUDE__ARGUMENTS_HPP
#define _GIT_WATCH__INCLUDE__ARGUMENTS_HPP

#include <string>

namespace git_watch
{
    class arguments
    {
    protected:
        std::string _operation;
        std::string _config_dir;
        std::string _usage;
        bool _help = false;
    public:
        [[nodiscard]]
        inline std::string operation() const
        {
            return _operation;
        }

        [[nodiscard]]
        inline std::string config_dir() const
        {
            return _operation;
        }

        [[nodiscard]]
        inline std::string usage() const
        {
            return _usage;
        }

        [[nodiscard]]
        inline bool help() const
        {
            return _help;
        }

        void fill(char const** arguments, int argument_count);
    };
}

#endif // _GIT_WATCH__INCLUDE__ARGUMENTS_HPP

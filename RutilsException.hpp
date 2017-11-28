//
// Created by Dowwind on 27/11/2017.
//

#ifndef RUTILS_RUTILSEXCEPTION_HPP
#define RUTILS_RUTILSEXCEPTION_HPP

#include <string>
#include <utility>

namespace rutils
{
    class FileNotFound: std::invalid_argument
    {
    private:
        std::string _msg;
    public:
        explicit FileNotFound(const std::string &_Message, std::string const &str)
                : invalid_argument(_Message), _msg(str) {}

        const char *what() const throw() { return _msg.c_str(); }
    };

    class InvalidTypeFile: std::invalid_argument
    {
    private:
        std::string _msg;

    public:
        explicit InvalidTypeFile(const std::string &_Message, std::string const &str)
                : invalid_argument(_Message), _msg(str) {}

        const char *what() const throw() { return _msg.c_str(); }

    };

}

#endif //RUTILS_RUTILSEXCEPTION_HPP

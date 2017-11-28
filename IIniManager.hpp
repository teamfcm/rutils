//
// Created by Dowwind on 27/11/2017.
//

#ifndef RUTILS_IINIMANAGER_HPP
#define RUTILS_IINIMANAGER_HPP

#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include "RutilsException.hpp"

namespace rutils
{
    template <typename T>
    using isIniValue = std::enable_if<typename std::is_same<T, std::string>::value
                                       && typename std::is_arithmetic<T>::value
                                       && typename std::is_same<T, bool>::value>::type;
    class IniManager
    {
        static IniManager *_instance;

    public:
    };

    class IniFile
    {
        std::experimental::filesystem::path _path;
    private:

    public:

        ~IniFile() = default;
    };

    class IniData
    {
    private:
        std::unordered_map<std::string, IniScope> _scopes{};

    public:
        IniData() = default;
        ~IniData() = default;

        IniScope const &getScope(std::string const &scopeName) const
        {
            if (this->exist(scopeName))
                return (_scopes.at(scopeName));
            throw std::out_of_range("the scope : " + scopeName + " does not exist.");
        }

        void createScope(std::string const &scopeName)
        {
            if (exist(scopeName))
                throw std::invalid_argument("The scope : " + scopeName +" already exists.");
            _scopes[scopeName];
        }

        bool exist(std::string const &scopeName) const noexcept { return _scopes.find(scopeName) != _scopes.end(); }
    };

    class IniScope
    {
    private:
        std::unordered_map<std::string, std::string> _values;

    public:
        IniScope() = default;
        ~IniScope() = default;

        template <typename T,
                typename = isIniValue<T>>
        T getValueAs(std::string const &key) = delete;
        std::string getValue(std::string const &key) = delete;

        template <typename T,
                typename = isIniValue<T>>
        void setOrCreateValueAs(std::string const &key, T const &value) = delete;
        void setOrCreateValue(std::string const &key, std::string const &value) = delete;

        void setScopeName() = delete;
    };
}

#endif //RUTILS_IINIMANAGER_HPP

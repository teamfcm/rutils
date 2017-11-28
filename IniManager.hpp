//
// Created by Dowwind on 28/11/2017.
//

#ifndef RUTILS_INIMANAGER_HPP
#define RUTILS_INIMANAGER_HPP

#include <unordered_map>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace rutils
{
    class IniManager;

    class IniScope
    {
    private:
        std::unordered_map<std::string, std::string> _values{};
    public:
        IniScope() = default;
        ~IniScope() = default;

        void add(std::string const &key, std::string const &value)
        {
            if (_values.find(key) != _values.end())
                throw std::runtime_error("[INI] Key {" + key + "} already exists.");
            _values[key] = value;
        }
    };

    class IniData
    {
    private:
        std::unordered_map<std::string, IniScope> _scopes{};
        std::experimental::filesystem::path _path;
        std::ifstream _in;

        std::string findScope(std::string const &line)
        {
            size_t openBrace;
            size_t closeBrace;
            std::string scopeName;

            if ((openBrace = line.find('[')) != std::string::npos) {
                if ((closeBrace = line.find(']')) != std::string::npos) {
                    if (closeBrace < openBrace)
                        throw std::runtime_error("[INI] Syntax error.");
                    scopeName = line.substr(openBrace + 1, closeBrace - openBrace - 1);
                    std::cout << "Scope name : " << scopeName << std::endl;
                    _scopes[scopeName];
                    return scopeName;
                }
                throw std::runtime_error("[INI] Syntax error.");
            }
            return "";
        }

        void findValue(std::string const &line, std::string const &scopeName)
        {
            std::string key;
            std::string value;
            size_t equal;

            if ((equal = line.find('=')) == std::string::npos)
                throw std::runtime_error("[INI] Syntax error.");
            key = line.substr(0, equal - 1);
            value = line.substr(equal + 1);
            std::cout << "Found " << key << " with the value " << value << std::endl;
            _scopes[scopeName].add(key, value);
        }

        void parseIniFile()
        {
            std::string line;
            size_t semicolonIndex;
            std::string scopeName;

            while (std::getline(_in, line))
            {
                if ((semicolonIndex = line.find(';')) != std::string::npos)
                    line = line.substr(0, semicolonIndex);
                if (line.empty())
                    continue;
                if ((scopeName = findScope(line)).empty())
                    findValue(line, scopeName);
            }
        }

    public:
        explicit IniData(std::string const &path)
                : _path(path), _in(path)
        {
            if (!std::experimental::filesystem::exists(_path))
                throw std::experimental::filesystem::filesystem_error(path + " does not exist.");
            if (!std::experimental::filesystem::is_regular_file(_path))
                throw std::experimental::filesystem::filesystem_error(path + " does not refer to a regular file.");
            parseIniFile();
        }
    };


    class IniManager
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<IniData>> _iniFiles;
        IniManager() = default;

    public:
        IniManager(IniManager const &) = delete;
        IniManager &operator=(IniManager const &) = delete;

        static IniManager *instance() {
            static auto instance = static_cast<IniManager *>(nullptr);

            if (instance == nullptr)
                instance = new IniManager();
            return instance;
        }

        std::shared_ptr<IniData> getOrCreateIniData(std::string const &path)
        {
            if (_iniFiles.find(path) == _iniFiles.end())
                _iniFiles[path] = std::make_shared<IniData>(path);
            return _iniFiles.at(path);
        }
    };

    class IniFile
    {
    private:
        IniManager *_manager;
        std::shared_ptr<IniData> _iniData{};

    public:
        explicit IniFile(std::string const &path)
        {
            _manager = IniManager::instance();
            _iniData = _manager->getOrCreateIniData(path);
        }
        ~IniFile() = default;
    };

};

#endif //RUTILS_INIMANAGER_HPP

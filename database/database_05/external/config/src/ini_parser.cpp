#include "config/ini_parser.hpp"

#include <fstream>
#include <unordered_map>
#include <stdexcept>

namespace config
{
    namespace
    {
        std::string trim(const std::string& s)
        {
            const auto first = s.find_first_not_of(" \t");

            if (first == std::string::npos)
                return "";

            const auto last = s.find_last_not_of(" \t");

            return s.substr(first, last - first + 1);
        }

        bool is_ignored_line(const std::string& line)
        {
            return line.empty() || line[0] == '#' || line[0] == ';' || line[0] == '[';
        }

        std::pair<std::string, std::string> parse_kv(const std::string& line)
        {
            const auto pos = line.find('=');

            if (pos == std::string::npos)

                throw std::runtime_error("Invalid line: " + line);

            return
            {
                trim(line.substr(0, pos)),
                trim(line.substr(pos + 1))
            };
        }

        std::string require(
            const std::unordered_map<std::string, std::string>& map,
            const std::string& key)
        {
            auto it = map.find(key);
            if (it == map.end() || it->second.empty())
                throw std::runtime_error("Missing config key: " + key);

            return it->second;
        }
    }

    DatabaseConfig IniParser::load_db_config(const std::string& filepath)
    {
        std::ifstream file(filepath);

        if (!file.is_open())
            throw std::runtime_error("Cannot open: " + filepath);

        std::unordered_map<std::string, std::string> values;

        std::string line;
        while (std::getline(file, line))
        {
            line = trim(line);

            if (is_ignored_line(line))
                continue;

            auto [key, value] = parse_kv(line);

            if (!key.empty())
                values[key] = value;
        }

        DatabaseConfig cfg;

        cfg.host = require(values, "host");
        cfg.dbname = require(values, "dbname");
        cfg.user = require(values, "user");
        cfg.password = require(values, "password");

        try
        {
            cfg.port = std::stoi(require(values, "port"));
        }
        catch (...)
        {
            throw std::runtime_error("Invalid port");
        }

        return cfg;
    }
}
#include "Logger.hpp"

Logger::Logger(const std::string& file_name) : _file(file_name, std::ios::app)
{
}

void Logger::Log(const std::string& message)
{
    if (_file.is_open())
    {
        _file << message << "\n";
    }
}
#include <string>
#include <fstream>

class Logger
{
    private:

        std::ofstream _file;

    public:
    
        explicit Logger(const std::string& file_name);

        void Log(const std::string& message);
};
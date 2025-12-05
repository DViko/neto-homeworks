#include <iostream>
#include <limits>
#include <fstream>
#include <string>

bool ReadValue(std::istream& stream, int& value, bool positive);
void ReverseWriteToFile(const int* buffer, int length, const std::string& path);

int main()
{
    int length {0}, counter {0}, element {0};
    int* buffer { nullptr };

    std::cout << "Insert array length: ";

    if (!ReadValue(std::cin, length, true))
    {
       return EXIT_FAILURE;
    }

    buffer = new int[length]();

    do
    {
        std::cout << "Insert array element: [" << counter << "]";
            
        if(ReadValue(std::cin, element, false))
        {
            buffer[counter] = element;
            counter ++;
        }
    }
    while (counter < length);

    ReverseWriteToFile(buffer, length, "out.txt");
        
    delete[] buffer;
    buffer = nullptr;
        
    return EXIT_SUCCESS;
}


bool ReadValue(std::istream& stream, int& value, bool positive)
{
    
    stream >> value;

    if (!stream || (positive && value <= 0))
    {
        if(positive)
        {
            std::cout << "Error: Length must be a positive number and greater than zero.\n";
        }
        else
        {
            std::cout << "Error: Invalid input, not a number.\n";
        }

        stream.clear();
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}

void ReverseWriteToFile(const int* buffer, int length, const std::string& path)
{
    std::ofstream file (path);

    file << length << "\n";

    for (int i { length - 1 }; i >= 0; i--)
    {
        file << buffer[i] << " ";
    }

    file.close();
}
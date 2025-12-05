#include <iostream>
#include <cstdint>
#include <string>
#include <array>

struct Human {
    std::string name;
    int age;
};

template<typename T>
void printVarType(std::string name, T& type);


int main(int argc, char** argv) {

    short s {0}; int i {0};
    long l {0}; long long ll {0};
    float f {0.0f}; double d {0.0}; long double ld {0.0};
    bool b {false};
    Human h {}; std::array<int, 5> std_arr {}; short c_arr[5] {};

    printVarType("short", s);
    printVarType("int", i);
    printVarType("long", l);
    printVarType("long long", ll);
    printVarType("float", f);
    printVarType("double", d);
    printVarType("long double", ld);
    printVarType("bool", b);
    printVarType("struct", h);
    printVarType("array", std_arr);
    printVarType("c_array", c_arr);

    return EXIT_SUCCESS;
}

template<typename T>
void printVarType(std::string name, T& type) {

    std::cout << name 
              << ": >> 0x" << std::hex << reinterpret_cast<uintptr_t>(&type)
              << " >> " << std::dec << sizeof(type) << "\n";
}
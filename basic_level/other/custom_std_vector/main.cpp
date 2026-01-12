#include "IntVector.hpp"
#include <iostream>

int main()
{
    IntVector vector;

    vector.PushBack(5);
    vector.PushBack(15);

    std::cout << "Vector Elements:\n";
    
    for ( size_t i {}; i < vector.Size(); i ++)
    {
        std::cout << "Element " << i << ": Value: " << vector[i] << '\n'; 
    }

    IntVector another_vector = vector;

    another_vector.PushBack(32);
    another_vector.PushBack(145);

    std::cout << "Another Vector Elements:\n";
    
    for ( size_t i {}; i < another_vector.Size(); i ++)
    {
        std::cout << "Element " << i << ": Value: " << another_vector[i] << '\n'; 
    }

    IntVector moved_vector = std::move(another_vector);

    moved_vector.PushBack(99);
    moved_vector.PushBack(1001);

    std::cout << "Moved Vector Elements:\n";

    for ( size_t i {}; i < moved_vector.Size(); i ++)
    {
        std::cout << "Element " << i << ": Value: " << moved_vector[i] << '\n'; 
    }

    IntVector assigned_vector { moved_vector};

    assigned_vector.PushBack(2024);
    assigned_vector.PushBack(3034);

    std::cout << "Assigned Vector Elements:\n";

    for ( size_t i {}; i < assigned_vector.Size(); i ++)
    {
        std::cout << "Element " << i << ": Value: " << assigned_vector[i] << '\n'; 
    }

    std::cout << "Original Vector Elements after moves:\n";

    for (int i {}; i < 10; i ++)
    {
        vector.PushBack(i * 10);
    }

    for ( size_t i {}; i < vector.Size(); i ++)
    {
        std::cout << "Element " << i << ": Value: " << vector[i] << '\n'; 
    }

    std::cout << "Vector Size: " << vector.Size() << '\n';
    std::cout << "Vector Capacity: " << vector.Capacity() << '\n';

    return EXIT_SUCCESS;
}
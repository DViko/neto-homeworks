#include <iostream>

struct Adress
{
    const char* city,
              * street;

    unsigned short building_number, apartment_number;
    unsigned int zip_code;
};

void PrintAdress(const Adress* adresses, unsigned short length);

int main()
{
    Adress adresses[]
    {
        {"Moscow", "Arbat", 12, 34, 119019},
        {"Saint Petersburg", "Nevsky Prospekt", 56, 78, 190000},
        {"Kazan", "Bauman Street", 90, 12, 420111},
        {"Novosibirsk", "Lenina Street", 34, 56, 630000}
    };
    
    PrintAdress(adresses, sizeof(adresses) / sizeof(adresses[0]));

    return EXIT_SUCCESS;
}

void PrintAdress(const Adress* adresses, unsigned short length)
{
    for (unsigned short i {}; i < length; i ++)
    {
        std::cout << "City: " << adresses[i].city << "\n"
                  << "Street: " << adresses[i].street << "\n"
                  << "Building Number: " << adresses[i].building_number << "\n"
                  << "Apartment Number: " << adresses[i].apartment_number << "\n"
                  << "ZIP Code: " << adresses[i].zip_code << "\n\n";
    }
}
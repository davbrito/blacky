#include "tools.h"

#include <iostream>
#include <iterator>

bool seguir_jugando()
{
    std::cout << "Desean jugar otra ronda? (s/n): ";
    for (auto itr = std::istream_iterator<std::string>(std::cin), end = std::istream_iterator<std::string>();
         itr != end; itr++)
    {
        if (*itr == "s")
            return true;
        if (*itr == "n")
            return false;
        std::cout << "Opcion invalida.\n";
    }
    return false;
}
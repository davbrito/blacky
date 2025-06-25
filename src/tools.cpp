#include "tools.h"

#include <fmt/format.h>
#include <iostream>
#include <iterator>

bool seguir_jugando()
{
    fmt::print("¿Desean jugar otra ronda? (s/n): ");
    for (auto itr = std::istream_iterator<std::string>(std::cin), end = std::istream_iterator<std::string>();
         itr != end; itr++)
    {
        if (*itr == "s")
            return true;
        if (*itr == "n")
            return false;

        fmt::println("Opcion invalida.");
    }
    return false;
}
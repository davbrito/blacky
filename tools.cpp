#include "tools.h"

#include <iterator>
#include <iostream>

bool seguir_jugando()
{
    cout << "Desean jugar otra ronda? (s/n): ";
    for (auto itr = istream_iterator<string>(cin),
              end = istream_iterator<string>();
         itr != end; itr++)
    {
        if (*itr == "s")
            return true;
        if (*itr == "n")
            return false;
        cout << "Opcion invalida.\n";
    }
    return false;
}
#include "Carta.h"
#include "menu.h"

#include <cassert>
#include <map>
#include <string>

const std::map<Carta, std::string> cartas_map{
    {Carta::A, "A"},
    {Carta::C2, "2"},
    {Carta::C3, "3"},
    {Carta::C4, "4"},
    {Carta::C5, "5"},
    {Carta::C6, "6"},
    {Carta::C7, "7"},
    {Carta::C8, "8"},
    {Carta::C9, "9"},
    {Carta::C10, "10"},
    {Carta::J, "J"},
    {Carta::Q, "Q"},
    {Carta::K, "K"}};

namespace std
{
    string to_string(const Carta c) { return cartas_map.at(c); }
} // namespace std

std::ostream &operator<<(std::ostream &os, const Carta c) { return os << std::to_string(c); }

int pedir_valor_As()
{
    auto opc = choice_selector("Usted tiene un nuevo as. Escoja el valor deseado",
                               "Opcion invalida.\n",
                               choice{1, "1\n"},
                               choice{2, "11\n"})();
    return (opc == 1 ? 1 : 11);
}

int valor(Carta carta)
{
    switch (carta)
    {
    case Carta::A:
        return pedir_valor_As();
    case Carta::J:
    case Carta::Q:
    case Carta::K:
        return 10;
    default:
        return static_cast<int>(carta);
    }
}
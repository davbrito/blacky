#include "Carta.h"
#include "menu.h"

#include <cassert>
#include <map>
#include <string>
#include <string_view>

const std::map<Carta, const char *> cartas_map{
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

int pedir_valor_As()
{
    auto opc = choose("Usted tiene un nuevo as. Escoja el valor deseado",
                      "Opcion invalida.", choice{1, "1"}, choice{2, "11"});
    return (opc == 1 ? 1 : 11);
}

const char *format_as(const Carta c) { return get_carta_name(c); }
const char *get_carta_name(const Carta c) { return cartas_map.at(c); }

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
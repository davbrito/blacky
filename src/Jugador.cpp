
#include "Jugador.h"
#include <iostream>
#include <istream>
#include <numeric>
#include <utility>

void Jugador::print_cartas() const
{
    std::cout << "Sus cartas son: ";
    for (const auto &[carta, _] : cartas_)
        std::cout << carta << ", ";
    std::cout << "\n";
}

int Jugador::suma() const
{
    return std::accumulate(begin(cartas_), end(cartas_), 0,
                           [](int sum, const std::pair<Carta, int> &c)
                           { return sum + std::get<int>(c); });
}
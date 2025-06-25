
#include "Jugador.h"

#include <algorithm>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <istream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <utility>

void Jugador::print_cartas() const
{
    fmt::print("{}", "Sus cartas son: ");
    auto cs = cartas_ | std::views::transform([](const std::pair<Carta, int> &carta)
                                              { return get_carta_name(carta.first); });
    fmt::print("{}", fmt::join(cs, ", "));
    fmt::println("\n");
}

int Jugador::suma() const
{
    return std::accumulate(begin(cartas_), end(cartas_), 0,
                           [](int sum, const std::pair<Carta, int> &c)
                           { return sum + std::get<int>(c); });
}
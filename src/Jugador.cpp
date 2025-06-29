
#include "Jugador.h"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <ranges>

void Jugador::ganar() { rondas_ganadas++; }

void Jugador::reset_ganados() noexcept { rondas_ganadas = 0; }

int Jugador::ganados() const noexcept { return rondas_ganadas; }

void Jugador::print_cartas() const { fmt::print("Sus cartas son: {}", fmt::join(m_cartas | std::views::keys | std::views::transform(&get_carta_name), ", ")); }

int Jugador::suma() const { return std::ranges::fold_left(m_cartas | std::views::values, 0, std::plus{}); }

void Jugador::add_carta(Carta c) { m_cartas.emplace(c, valor(c)); }

void Jugador::add_cartas(std::initializer_list<Carta> c)
{
    for (const Carta carta : c)
        add_carta(carta);
}

void Jugador::reset_cartas() { m_cartas.clear(); }
#if !defined(JUGADOR_H)
#define JUGADOR_H

#include "Carta.h"

#include <concepts>
#include <map>
#include <string>
#include <string_view>
#include <utility>

class Jugador
{
    std::multimap<Carta, int> m_cartas{};
    int rondas_ganadas = 0;

public:
    std::string nombre;

    Jugador() = delete;
    Jugador(const std::string_view nomb) : nombre{nomb} {}

    void ganar();
    void reset_ganados() noexcept;
    int ganados() const noexcept;
    int suma() const;
    void print_cartas() const;

    void add_carta(Carta c);
    void add_cartas(std::initializer_list<Carta> c);
    void reset_cartas();
};

#endif // JUGADOR_H

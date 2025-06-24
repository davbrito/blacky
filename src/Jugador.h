#if !defined(JUGADOR_H)
#define JUGADOR_H

#include "Carta.h"

#include <string>
#include <string_view>
#include <vector>
#include <utility>

using namespace std;

class Jugador
{
    vector<pair<Carta, int>> cartas_{};
    int rondas_ganadas = 0;

public:
    string nombre;

    Jugador() = delete;
    Jugador(const string_view nomb)
        : nombre{nomb} {}

    inline void add_carta(Carta c);

    template <typename... CartaT>
    inline enable_if_t<conjunction_v<is_same<CartaT, Carta>...>>
    add_cartas(CartaT&&... c);

    inline void ganar();
    inline void reset_ganados();
    inline int ganados() const;
    int suma() const;
    void print_cartas() const;
};

inline void Jugador::add_carta(Carta c) { cartas_.push_back({c, valor(c)}); }

template <typename... CartaT>
inline enable_if_t<conjunction_v<is_same<CartaT, Carta>...>>
Jugador::add_cartas(CartaT &&... c) { (add_carta(forward<CartaT>(c)), ...); }

inline void Jugador::ganar() { rondas_ganadas++; }

inline void Jugador::reset_ganados() { rondas_ganadas = 0; }

inline int Jugador::ganados() const { return rondas_ganadas; }

#endif // JUGADOR_H

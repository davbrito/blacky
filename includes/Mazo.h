#if !defined(MAZO_H)
#define MAZO_H

#include <algorithm>
#include <concepts>
#include <exception>
#include <map>
#include <random>
#include <vector>

#include "Carta.h"
#include "Jugador.h"

struct no_cards : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class Mazo
{

public:
    Mazo();
    Carta pop_card();

    void repartir(std::ranges::range auto &jugadores)
    {
        for (Jugador &jugador : jugadores)
            jugador.add_cartas({pop_card(), pop_card()});
    }

private:
    std::map<Carta, int> m_cuenta{};
    std::vector<Carta> m_cartas;
    std::mt19937 random_generator{std::random_device{}()};

    inline void barajar()
    {
        std::ranges::shuffle(m_cartas, random_generator);
    }

    inline void push_card(Carta c)
    {
        m_cuenta[c]++;
        m_cartas.push_back(c);
    }

    //    void debug_print() const
    //    {
    //        cout << "mazo: " << endl;
    //        {
    //            int i = 1;
    //            for (auto c : cartas_)
    //                {
    //                    cout << c << ", ";
    //                    if (i % 20 == 0)
    //                        cout << endl;
    //                    i++;
    //                }
    //        }
    //        cout << endl;
    //    }
};

#endif // MAZO_H

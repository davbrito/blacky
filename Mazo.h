#if !defined(MAZO_H)
#define MAZO_H

#include <map>
#include <vector>
#include <random>
#include <exception>
#include <algorithm>

#include "Carta.h"
#include "Jugador.h"

using namespace std;

struct no_cards : runtime_error
{
    using runtime_error::runtime_error;
};

class Mazo
{
    map<Carta, int> cuenta_{};
    vector<Carta> cartas_;

public:
    Mazo();
    Carta pop_card();
    template <typename Range>
    inline void repartir(Range &jugadores);

private:
    inline void barajar();
    inline void push_card(Carta c);

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

inline void Mazo::barajar() { shuffle(begin(cartas_), end(cartas_), mt19937{random_device{}()}); }

template <typename Range>
inline void Mazo::repartir(Range &jugadores)
{
    for (Jugador &jugador : jugadores)
        jugador.add_cartas(pop_card(), pop_card());
}

inline void Mazo::push_card(Carta c)
{
    cuenta_[c]++;
    cartas_.push_back(c);
}

#endif // MAZO_H

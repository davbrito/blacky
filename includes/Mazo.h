#if !defined(MAZO_H)
#define MAZO_H

#include <algorithm>
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
    std::map<Carta, int> cuenta_{};
    std::vector<Carta> cartas_;

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

inline void Mazo::barajar()
{
    std::shuffle(std::begin(cartas_), std::end(cartas_), std::mt19937{std::random_device{}()});
}

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

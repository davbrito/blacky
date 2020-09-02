// *** ADDED BY HEADER FIXUP ***
#include <istream>
// *** END ***
#include "Jugador.h"
#include <iostream>
#include <numeric>
#include <utility>

using namespace std;
void Jugador::print_cartas() const
{
    cout << "Sus cartas son: ";
    for (const auto &[carta, _] : cartas_)
        cout << carta << ", ";
    cout << "\n";
}

int Jugador::suma() const
{
    return accumulate(begin(cartas_), end(cartas_), 0,
                      [](int sum, const pair<Carta, int> &c) { return sum + get<int>(c); });
}
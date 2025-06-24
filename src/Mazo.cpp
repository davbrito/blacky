#include "Mazo.h"

Mazo::Mazo()
{
    for (Carta c : allCards)
        for (int i = 0; i < 4; ++i)
            push_card(c);
    barajar();
}

Carta Mazo::pop_card()
{
    if (cartas_.empty())
        throw no_cards("No hay más cartas en el mazo.");
    auto carta = cartas_.back();
    cartas_.pop_back();
    cuenta_.at(carta)--;
    return carta;
}

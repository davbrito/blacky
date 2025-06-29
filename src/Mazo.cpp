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
    if (m_cartas.empty())
        throw no_cards("No hay más cartas en el mazo.");
    auto carta = m_cartas.back();
    m_cartas.pop_back();
    m_cuenta.at(carta)--;
    return carta;
}

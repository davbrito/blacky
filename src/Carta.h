#if !defined(CARTA_H)
#define CARTA_H

#include <array>
#include <ostream>
#include <string>

enum class Carta
{
    A = 1,
    C2,
    C3,
    C4,
    C5,
    C6,
    C7,
    C8,
    C9,
    C10,
    J,
    Q,
    K
};

constexpr const std::array<const Carta, 13> allCards = {
    Carta::A, Carta::C2, Carta::C3, Carta::C4, Carta::C5,
    Carta::C6, Carta::C7, Carta::C8, Carta::C9,
    Carta::C10, Carta::J, Carta::Q, Carta::K};

std::ostream &operator<<(std::ostream &os, const Carta c);
// string to_string(const Carta c);

int valor(Carta carta);
#endif // CARTA_H

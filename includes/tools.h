#if !defined(TOOLS_H)
#define TOOLS_H

#include <iostream>
#include <istream>
#include <string>

template <typename Tp>
Tp input(const std::string &msj = "", std::istream &in = std::cin)
{
    auto execption_mask = in.exceptions();
    try
    {
        in.exceptions(std::ios::failbit);
        Tp x;
        std::cout << msj;
        in >> x;
        return x;
    }
    catch (std::ios::failure &)
    {
        in.exceptions(execption_mask);
        throw;
    }
}

bool seguir_jugando();

#endif // TOOLS_H

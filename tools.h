#if !defined(TOOLS_H)
#define TOOLS_H

#include <string>
#include <istream>
#include <iostream>

using namespace std;

template <typename Tp>
Tp input(const string &msj = "", istream &in = cin)
{
    auto execption_mask = in.exceptions();
    try
    {
        in.exceptions(ios::failbit);
        Tp x;
        cout << msj;
        in >> x;
        return x;
    }
    catch (ios::failure &)
    {
        in.exceptions(execption_mask);
        throw;
    }
}

bool seguir_jugando();


#endif // TOOLS_H

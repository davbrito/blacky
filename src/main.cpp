// *** ADDED BY HEADER FIXUP ***
#include <istream>
// *** END ***
#include <iostream>
#include "blacky.h"
#include "menu.h"
// #include <fstream>
using namespace std;

extern const map<Carta, string> cartas_map;
int main()
{
    //     system("CLS");
    bool end = false;
    auto m = menu("Ingrese una opcion:",
                  "Opcion invalida. Intente de nuevo.\n",
                  menu_option{'1', "Empezar partida.\n", &jugar},
                  menu_option{'2', "Instrucciones.\n", &instrucciones},
                  menu_option{'3', "Salir\n", [&end] { end = true; }});
    while (!end)
        m();

    cout << "Adios. Gracias por jugar.";
}


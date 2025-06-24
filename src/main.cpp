#include "blacky.h"
#include "menu.h"
#include <iostream>
#include <istream>

extern const std::map<Carta, std::string> cartas_map;
int main()
{
    //     system("CLS");
    bool end = false;
    auto m = menu("Ingrese una opcion:", "Opcion invalida. Intente de nuevo.\n",
                  menu_option{'1', "Empezar partida.\n", &jugar}, menu_option{'2', "Instrucciones.\n", &instrucciones},
                  menu_option{'3', "Salir\n", [&end]
                              { end = true; }});
    while (!end)
        m();

    std::cout << "Adios. Gracias por jugar.";
}

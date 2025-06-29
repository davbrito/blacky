#include "app.h"
#include "blacky.h"
#include "menu.h"

int main()
{
    auto a = app{};

    a.run(menu{
        "Ingrese una opcion:",
        "Opcion invalida. Intente de nuevo.",
        menu_option{'1', "Empezar partida.", [&]()
                    { jugar(); }},
        menu_option{'2', "Instrucciones.", [&]()
                    { instrucciones(); }},
        menu_option{'3', "Salir", [&]()
                    { a.stop(); }}});

    fmt::println("Adios. Gracias por jugar.");
}

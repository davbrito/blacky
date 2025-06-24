#include "blacky.h"
#include "menu.h"
#include "tools.h"

#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

void instrucciones()
{
    constexpr auto instrucciones =
        "Instrucciones.\n\n"
        "Valor de las cartas:\n"
        "El As tiene un valor de 1 u 11  (tendra la opcion de elegir)\n"
        "Las cartas J, Q y K tienen un valor de 10 c/u.   El resto de\n"
        "las cartas del 2 al 10 tendran su valor natural. El objetivo\n"
        "del juego es llegar a 21 o lo mas cerca posible,  para ello:\n"
        "1) Se le repartiran 2 cartas y se le indicara la sumatoria de las mismas.\n"
        "2) En tal caso de que sus 2 cartas principales sean un As y una carta cuyo\n"
        "valor sea 10, usted tendra Blackjack y ganara automaticamente\n"
        "3) Se le preguntara si desea pedir otra carta, plantarse o dejar que el computador elija.\n"
        "Opcion que debe elegir segun sea su mano\n"
        "4) Si elige pedir se le dara otra carta la cual se sumara a las que ya tenia\n"
        "5) Si al pedir una carta se pasa de 21 perdera la ronda\n"
        "6) Si elige plantarse no se le repartiran mas cartas y se quedara con la sumatoria que posea\n"
        "7) Se le dara turno al siguiente jugador\n"
        "8) Luego de que todos los jugadores hayan jugado su turno, ganara aquel que\n"
        "tenga 21 o este mas cerca de dicho numero\n";
    std::cout << instrucciones;
    std::system("PAUSE");
}

std::ofstream abrir_archivo(const char *nom_arch)
{
    if (!std::ifstream(nom_arch))
        return std::ofstream(nom_arch);
    return std::ofstream(nom_arch, std::ios::ate);
}

int get_random(int low_included, int hi_excluded)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dis(low_included, hi_excluded - 1);
    return dis(gen);
}

int get_random(int hi_excluded)
{
    return get_random(0, hi_excluded);
}

std::string pedir_nombre(int num)
{
    return input<std::string>("Ingrese el nombre del jugador " + std::to_string(num) + ": ");
}

void turno(Jugador &j, Mazo &m)
{
    std::cout << "\nAhora es el turno de " << j.nombre << ".\n";
    j.print_cartas();

    if (j.suma() == 21)
    {
        std::cout << "Usted tiene un Blackjack. ;)\n";
        return;
    }

    std::cout << "La suma de sus cartas es " << j.suma() << ".\n";

    auto cs = choice_selector("Que desea hacer?\n", "Opcion invalida.\n", choice{1, "Pedir, "},
                              choice{2, "Plantarse, "}, choice{3, "Decision del computador \n"});
    while (1)
    {
        int opc = cs();
        if (opc == 3)
            opc = get_random(1, 3);

        if (opc == 1)
        {
            auto c = m.pop_card();
            std::cout << "Le salio un: " << c << std::endl;
            j.add_carta(c);
        }
        else if (opc == 2)
        {
            std::cout << j.nombre << " se ha plantado.\n";
            break;
        }

        j.print_cartas();
        printf("La suma de sus cartas es %i.\n", j.suma());

        if (j.suma() > 21)
        {
            printf("Se ha pasado de 21\n");
            break;
        }
    }
}

std::vector<Jugador> crear_jugadores(size_t n)
{
    std::vector<Jugador> v;
    for (size_t i = 1; i <= n; i++)
        v.emplace_back(pedir_nombre(i));
    return v;
}

void estadisticas_finales(const std::vector<Jugador> &jugadores)
{
    std::ofstream file = abrir_archivo("puntuaciones_blackjack.txt");
    for (std::ostream &out : std::vector<std::reference_wrapper<std::ostream>>{file, std::cout})
    {
        out << "\nEstos son los resultados del juego.\n";
        for (const auto &jugador : jugadores)
            out << jugador.nombre << ": " << jugador.ganados() << " rondas ganadas.\n";
    }
}

void ganador_ronda(std::vector<Jugador> &jugadores)
{
    auto ganador = find_if(jugadores.begin(), jugadores.end(), [](Jugador const &j)
                           { return j.suma() <= 21; });

    if (ganador == jugadores.end())
    {
        std::cout << "\nNo hay ganador en esta ronda.\n";
        return;
    }

    for (auto i = ganador, end = jugadores.end(); i != end; i++)
        if (i->suma() <= 21 && i->suma() > ganador->suma())
            ganador = i;

    std::cout << "\nEl ganador de la ronda es " << ganador->nombre << " con " << ganador->suma() << " puntos\n";
    ganador->ganar();
}

void jugar()
{
    std::vector<Jugador> jugadores = crear_jugadores(input<int>("Ingrese la cantidad de jugadores: "));
    do
    {
        Mazo mazo;
        mazo.repartir(jugadores);
        for (auto &jugador : jugadores)
        {
            // system("CLS");
            turno(jugador, mazo);
            if (jugador.suma() == 21)
                break;
            // system("PAUSE");
        }
        ganador_ronda(jugadores);
    } while (seguir_jugando());
    // system("CLS");
    estadisticas_finales(jugadores);
    // system("PAUSE");
}

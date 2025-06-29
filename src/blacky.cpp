#include "blacky.h"
#include "menu.h"
#include "tools.h"

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/tee.hpp>

#include <fmt/ostream.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <string>
#include <vector>

constexpr const auto INSTRUCCIONES =
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

void instrucciones()
{
    fmt::println("{}", INSTRUCCIONES);
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

namespace choice_type
{
    constexpr const int PEDIR = 1;
    constexpr const int PLANTARSE = 2;
    constexpr const int DECISION_COMPUTADOR = 3;
};

constexpr const int BLACKJACK = 21;

constexpr const auto ask_choice = choice_selector("Que desea hacer?", "Opcion invalida.",
                                                  choice{choice_type::PEDIR, "Pedir, "},
                                                  choice{choice_type::PLANTARSE, "Plantarse, "},
                                                  choice{choice_type::DECISION_COMPUTADOR, "Decision del computador "});
void turno(Jugador &j, Mazo &m)
{
    fmt::println("\nAhora es el turno de {}.", j.nombre);
    j.print_cartas();

    if (j.suma() == BLACKJACK)
    {
        fmt::println("Usted tiene un Blackjack. ;)");
        return;
    }

    fmt::println("La suma de sus cartas es {}.", j.suma());

    while (1)
    {
        int opc = ask_choice();
        if (opc == choice_type::DECISION_COMPUTADOR)
            opc = get_random(1, 3);

        if (opc == choice_type::PEDIR)
        {
            auto c = m.pop_card();
            fmt::println("Le salio un: {}", get_carta_name(c));
            j.add_carta(c);
        }
        else if (opc == choice_type::PLANTARSE)
        {
            fmt::println("{} se ha plantado.", j.nombre);
            break;
        }

        j.print_cartas();
        fmt::println("La suma de sus cartas es {}.", j.suma());

        if (j.suma() > BLACKJACK)
        {
            fmt::println("Se ha pasado de 21");
            break;
        }
    }
}

std::vector<Jugador> crear_jugadores(int n)
{
    auto names = std::views::iota(1, n + 1) | std::views::transform(pedir_nombre);
    return {std::begin(names), std::end(names)};
}

void estadisticas_finales(const std::vector<Jugador> &jugadores)
{
    std::ofstream file = abrir_archivo("puntuaciones_blackjack.txt");
    auto sink = boost::iostreams::tee(std::cout, file);
    auto output = boost::iostreams::stream<boost::iostreams::tee_device<std::ostream, std::ofstream>>(sink);

    fmt::println(output, "\nEstos son los resultados del juego.");
    for (const auto &jugador : jugadores)
        fmt::println(output, "{}: {} rondas ganadas.", jugador.nombre, jugador.ganados());
}

void print_players_status(const std::vector<Jugador> &jugadores)
{
    fmt::println("\nEstado de los jugadores:");
    for (const auto &jugador : jugadores)
    {
        fmt::println("\nJugador {}:", jugador.nombre);
        jugador.print_cartas();
        fmt::println("{} tiene {} puntos y ha ganado {} rondas.", jugador.nombre, jugador.suma(), jugador.ganados());
    }
}

void ganador_ronda(std::vector<Jugador> &jugadores)
{
    auto candidatos = jugadores | std::views::filter([](const Jugador &j)
                                                     { return j.suma() <= BLACKJACK; });
    auto ganador = std::ranges::max_element(candidatos, {}, &Jugador::suma);

    if (ganador == candidatos.end())
    {
        fmt::println("\nNo hay ganador en esta ronda.");
        return;
    }

    fmt::println("\nEl ganador de la ronda es {} con {} puntos", ganador->nombre, ganador->suma());
    ganador->ganar();
}

void jugar()
{
    auto jugadores = crear_jugadores(input<int>("Ingrese la cantidad de jugadores: "));

    while (true)
    {
        Mazo mazo;
        mazo.repartir(jugadores);
        for (auto &jugador : jugadores)
        {
            turno(jugador, mazo);
            if (jugador.suma() == BLACKJACK)
                break;
        }
        ganador_ronda(jugadores);
        print_players_status(jugadores);

        if (!seguir_jugando())
            break;
    };

    estadisticas_finales(jugadores);
}

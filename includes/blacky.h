#if !defined(BLACKY_H)
#define BLACKY_H

#include <fstream>
#include <iostream>
#include <istream>
#include <random>
#include <string>

#include "Carta.h"
#include "Jugador.h"
#include "Mazo.h"

constexpr int JUGADORES = 4;

/* UTILS */
std::ofstream abrir_archivo(const char *nom_arch);
int get_random(int low_included, int hi_excluded);
int get_random(int hi_excluded);

void turno(Jugador &j, Mazo &m);

void ganador_ronda(std::vector<Jugador> &);
void estadisticas_finales(const std::vector<Jugador> &);

void jugar();
void instrucciones();

#endif // BLACKY_H

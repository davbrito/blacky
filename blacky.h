#if !defined(BLACKY_H)
#define BLACKY_H

#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include <random>

#include "Mazo.h"
#include "Carta.h"
#include "Jugador.h"

using namespace std;

constexpr int JUGADORES = 4;

/* UTILS */
ofstream abrir_archivo(const char *nom_arch);
int get_random(int low_included, int hi_excluded);
int get_random(int hi_excluded);

void turno(Jugador &j, Mazo &m);

void ganador_ronda(vector<Jugador> &);
void estadisticas_finales(const vector<Jugador> &);

void jugar();
void instrucciones();



#endif // BLACKY_H

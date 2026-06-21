#include <algorithm>

#include "estructuras.h"
#include "brute-force.h"

using namespace std;

long long mejorSatisfaccion;

/*
 * Explora recursivamente todas las combinaciones posibles de opciones para cada anime.
 * En cada nivel de la recursión se decide cuantos capitulos ver de un anime
 * (incluyendo la opcion de no verlo).
 */

void backtracking(const vector<Anime>& animes, int animeActual, int tiempoUsado, 
    int energiaUsada, long long satisfaccionActual, int M, int E){
    
    // Backtracking, corta la ramas si se excede
    if (tiempoUsado > M || energiaUsada > E)
        return;

    // Caso base
    if (animeActual >= static_cast<int>(animes.size())){
        mejorSatisfaccion = max(mejorSatisfaccion, satisfaccionActual);
        return;
    }

    // Busqueda exhaustiva
    for (const Opcion& opcion : animes[animeActual].opciones){
        backtracking(animes, animeActual + 1, tiempoUsado + opcion.tiempo,
            energiaUsada + opcion.energia, satisfaccionActual + opcion.satisfaccion,
            M, E);
    }
}

long long fuerzaBruta(const vector<Anime>& animes, int M, int E){
    mejorSatisfaccion = 0;
    backtracking(animes, 0, 0, 0, 0, M, E);

    return mejorSatisfaccion;
}

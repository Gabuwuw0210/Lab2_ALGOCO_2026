#include "estructuras.h"
#include <vector>
#include <algorithm>

using namespace std;

/*
 * En codigo se parece mucho al otro greedy pero cambia su forma de actuar.
 * Heuristica: Cada opcion se evalua segun la satisfaccion extra que aporta
 * respecto a la opcion anterior y el costo adicional necesario para obtenerla.
 * Se selecciona iterativamente la alternativa con mejor rendimiento.
 * Score = Δv / Δt+Δc
 * Ejemplo: si tengo un cap v1=40, t1=30 y e1=10, (40-0)/(30-0+10-0)= 1 muy rentable
 * el cap 2 tiene v2=15, t2=30, e2=10, (55-40)/(60-30+20-10)= 0.375 no muy rentable
 * Entonces pasar de ver 0 a 1cap es rentable, de 1 a 2 no tanto.
 */

long long greedy2(const vector<Anime>& animes, int M, int E){
    int n = animes.size();

    vector<bool> usado(n, false);

    int tiempo = 0;
    int energia = 0;
    long long satisfaccion = 0;

    while (true){
        double bestScore = -1.0;
        int bestAnime = -1;
        int bestOption = -1;

        // Busca la mejor opcion
        for (int i = 0; i < n; i++){
            if (usado[i]) continue;

            const auto& opciones = animes[i].opciones;

            // Desde j=1 porque la opción 0 es no ver nada
            for (int j = 1; j < (int)opciones.size(); j++){
                const Opcion& op = opciones[j];

                // Descarta opciones
                if (tiempo + op.tiempo > M || energia + op.energia > E)
                    continue;

                const Opcion& prev = opciones[j - 1];

                int dt = op.tiempo - prev.tiempo;
                int de = op.energia - prev.energia;
                long long dv = op.satisfaccion - prev.satisfaccion;

                double cost = dt + de;
                if (cost <= 0) continue;

                // Relacion beneficio/costo (marginal) del greedy
                double score = (double)dv / cost;

                //Actualiza bestScore
                if (score > bestScore){
                    bestScore = score;
                    bestAnime = i;
                    bestOption = j;
                }
            }
        }

        // Agrega la mejor opcion
        const Opcion& op =
            animes[bestAnime].opciones[bestOption];

        tiempo += op.tiempo;
        energia += op.energia;
        satisfaccion += op.satisfaccion;

        usado[bestAnime] = true;
    }

    return satisfaccion;
}

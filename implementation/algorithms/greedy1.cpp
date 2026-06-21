#include "estructuras.h"
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Heuristica: En cada iteracion selecciona la opcion mas factible con la
 * mejor relacion satisfaccion/recursos(energia y timepo).
 * Score = v/(t/M + E/c)
 */

long long greedy1(const vector<Anime>& animes, int M, int E){
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

            for (int j = 0; j < (int)animes[i].opciones.size(); j++){
                const Opcion& op = animes[i].opciones[j];

                // Descarta opciones
                if (tiempo + op.tiempo > M || energia + op.energia > E)
                    continue;

                // Calcula un costo normalizado segun el tiempo/energia que haya
                double cost = (double)op.tiempo / M + (double)op.energia / E;

                if (cost == 0) continue;

                // Relacion beneficio/costo del greedy
                double score = (double)op.satisfaccion / cost;

                //Actualiza bestScore
                if (score > bestScore){
                    bestScore = score;
                    bestAnime = i;
                    bestOption = j;
                }
            }
        }

        // Agrega la mejor opcion
        const Opcion& op = animes[bestAnime].opciones[bestOption];

        tiempo += op.tiempo;
        energia += op.energia;
        satisfaccion += op.satisfaccion;

        usado[bestAnime] = true;
    }

    return satisfaccion;
}

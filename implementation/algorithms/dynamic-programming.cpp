#include <algorithm>

#include "estructuras.h"
#include "dynamic-programming.h"

using namespace std;

/*
 * DP con 2 restricciones, cada anime se modela como un grupo de opciones MUTUAMENTE
 * EXCLUYENTES, donde debe escogerse exactamente una (incluyendo la opcion de
 * no ver ni un capitulo).
 */

long long programacionDinamica(const vector<Anime>& animes, int M, int E){
    vector<vector<long long>> dp(M + 1, vector<long long>(E + 1, -1));

    // Aqui se guarda el mayor valor
    dp[0][0] = 0;

    for (const Anime& anime : animes){
        vector<vector<long long>> new_dp(M + 1, vector<long long>(E + 1, -1));

         // Recorre todos los estados
        for (int m = 0; m <= M; m++){
            for (int e = 0; e <= E; e++){
                if (dp[m][e] == -1) continue;

                // Prueba cada opcion del anime actual
                for (const Opcion& op : anime.opciones){
                    int nm = m + op.tiempo;
                    int ne = e + op.energia;

                    // Descarta opciones
                    if (nm > M || ne > E) continue;

                    // Actualiza la mejor satisfaccion
                    new_dp[nm][ne] = max( new_dp[nm][ne], dp[m][e] + op.satisfaccion);
                }
            }
        }

        dp = move(new_dp);
    }

    long long ans = 0;

    // Busca la mejor satisfaccion entre los estados validos
    for (int m = 0; m <= M; m++)
        for (int e = 0; e <= E; e++)
            ans = max(ans, dp[m][e]);

    return ans;
}

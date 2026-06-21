#pragma once

#include <string>
#include <vector>

struct Opcion {
    int tiempo;
    int energia;
    long long satisfaccion;
};

struct Anime {
    std::string nombre;
    std::vector<Opcion> opciones;
};

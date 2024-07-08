//
// Created by gab11 on 17/06/2024.
//

#ifndef USUARIO_H
#define USUARIO_H
#include "iostream"
#include "Peliculas.h"
#include "vector"

using namespace std;

struct Usuario {
    vector<Peliculas> ver_mas_tarde;
    vector<Peliculas> likes;

    void agregar_mas_tarde(Peliculas n) {
        ver_mas_tarde.push_back(n);
    }
    void agregar_favortio(Peliculas n) {
        likes.push_back(n);
    }
};


#endif //USUARIO_H

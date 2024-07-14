#ifndef PELICULAS_H
#define PELICULAS_H

#include <iostream>

using namespace std;

struct Peliculas {
    string imdb_id;
    string title;
    string plot_synopsis;
    string tags;
    string split;
    string synopsis_source;
    Peliculas() = default;
    Peliculas(string, string, string , string, string, string);

    virtual void mostrar();
    virtual ~Peliculas() {}
};

#endif // PELICULAS_H

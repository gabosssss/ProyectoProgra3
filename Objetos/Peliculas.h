
#ifndef PELICULAS_H
#define PELICULAS_H

#include "iostream"
#include "vector"

using namespace std;



class Peliculas {
private:
    string imdb_id;
    string title;
    string plot_synopsis;
    vector<string> tags;
};



#endif //PELICULAS_H

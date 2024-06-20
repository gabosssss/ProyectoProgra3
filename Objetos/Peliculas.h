
#ifndef PELICULAS_H
#define PELICULAS_H

#include "iostream"
#include "vector"

using namespace std;



class Peliculas {
private:
    string imdb_id;
    string plot_synopsis;
    vector<string> tags;
public:
    Peliculas(string codigo, string plot, vector<string> tags):imdb_id(codigo),plot_synopsis(plot),tags(tags){}
    ~Peliculas(){}

};



#endif //PELICULAS_H

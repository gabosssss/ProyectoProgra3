#include "Peliculas.h"
#include "../Funciones.h"

Peliculas::Peliculas(string imdb_id, string title, string plot, string tags, string split, string synopsis_source){
    this->imdb_id = imdb_id;
    this->title = title;
    this->plot_synopsis = plot;
    this->tags = tags;
    this->split = split;
    this->synopsis_source = synopsis_source;
}

void Peliculas::mostrar() {
    cout << "============================" << endl;
    cout << "Title: " << title << endl;
    cout << "Imdb_id: " << imdb_id << endl;
    cout << "Tags: " << tags << endl;
    cout << "Split: " << split << endl;
    cout << "Synopsis_source: " << synopsis_source << endl << endl; 
}

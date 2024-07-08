//
// Created by gab11 on 17/06/2024.
//

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
    cout << "Title: " << title << endl;
    cout << "IMDB ID: " << imdb_id << endl;
}


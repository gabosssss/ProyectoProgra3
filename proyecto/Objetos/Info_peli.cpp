#include "Info_peli.h"

//Patrón : DECORATOR

InfoBase::InfoBase(Peliculas* pelicula){

    this->imdb_id = pelicula->imdb_id;
    this->title = pelicula->title;
    this->plot_synopsis = pelicula->plot_synopsis;
    this->tags = pelicula->tags;
    this->split = pelicula->split;
    this->synopsis_source = pelicula->synopsis_source;
    
}

InfoDecorador::InfoDecorador(Peliculas* info){
    this->info = info;
}

InfoCompleta::InfoCompleta(Peliculas* pelicula): InfoDecorador(pelicula){
}


void InfoBase::mostrar(){
    cout << "==============================" << endl;
    cout << "INFO ABOUT: " << title << endl;
    cout << "ID: " << imdb_id << endl;
    cout << "Tags: " << tags << endl;
}

void InfoDecorador::mostrar(){
    info->mostrar();
}

void InfoCompleta::mostrar(){
    InfoDecorador::mostrar();
    cout << "Split: " << info->split << endl;
    cout << "Synopsis source: " << info->synopsis_source << endl;
    cout << "Plot synopsis: " << endl; cout << info->plot_synopsis << endl;
}
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include "Objetos/Peliculas.h"
#include "Objetos/Info_peli.h"
#include "Objetos/Usuario.h"
#include "Funciones.h"
#include "Database.h"


using namespace std;

int main() {
    
    Database* d = Database::getInstance(); // La base de datos con todo

    //Testing

    vector<string> v = d->getImdbId();
    vector<string> v2 = d->getPlotSynopsis();

    if (v.empty()) {
        cout << "No se cargaron datos" << endl;
    } else {
        cout << "Datos cargados correctamente" << endl;
    }

    for (size_t i = 0; i < v.size() && i < 3; ++i) {
        cout << v[i] << endl;
    }

    cout << v2[9];
    cout << endl << endl;
    vector<string> v4 = d->getTags();
    cout << v4[4];
    cout << endl;
    get_peliculas_tag_simple(get_by_tag(d));
    cout << endl << endl;
    get_peliculas_tag_complejo(get_by_tag(d));


    return 0;
}


// Correr
// g++ main.cpp Funciones.cpp Database.cpp Objetos/Info_peli.cpp Objetos/Peliculas.cpp -I./ -I./Objetos -o main
// ./main.exe

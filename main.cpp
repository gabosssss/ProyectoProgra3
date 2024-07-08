#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "Objetos/Peliculas.cpp"
#include "Objetos/Usuario.h"
#include "Funciones.h"
#include "Objetos/Database.h"


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

    return 0;
}

/* Código anterior 1:

    ifstream data;
    data.open("../mpst_full_data.csv");
    string line="";
    getline(data,line);
    getline(data,line);

    cout<<line<<endl<<endl;

    vector<string> hola=split(line,',');
    for (int i=0;i<hola.size();i++) {
        cout<<hola[i]<<endl;
    }
    // Cols: imdb_id,title,plot_synopsis,tags,split,synopsis_source
    data.close();
*/
/* Código anterior 2:

    ifstream data;
    ifstream data2;
    data.open("../mpst_full_data_fixed.csv");
    string line;
    vector<vector<string>> peliculas;
    getline(data,line);
    while (getline(data,line)) {
        vector<string> pelis=split(line,';');
        peliculas.push_back(pelis);
    }

    data.close();

    for (size_t i = 0; i < peliculas.size(); i++) {
        for (size_t j = 0; j < peliculas[i].size(); j++) {
            cout << peliculas[i][j] <<endl;
        }
        cout << endl;
    }
*/

// Cosa
// g++ main.cpp Funciones.cpp Database.cpp -o main
// ./main.exe

#include "Funciones.h"
#include "Objetos/Peliculas.h"

vector<string> split(string texto, char separador) {
    vector<string> resultado;
    string palabra="";
    for (char ch : texto) {
        if (ch != separador) {
            palabra+=ch;
        }
        else {
            resultado.push_back(palabra);
            palabra="";
        }
    }
    return resultado;
}

vector<vector<string>> fill_database() {
    vector<vector<string>> lines;
    ifstream data("../mpst_full_data_fixed.csv");
    if (!data.is_open()) {
        cerr << "Error: No se pudo abrir el archivo" << endl;
        return lines;
    }
    string line = "";
    getline(data, line);
    while (getline(data, line)) {
        lines.push_back(split_avanzado(line,';'));
    }
    data.close();
    return lines;
}

vector<string> get_col(vector<vector<string>> database, int pos) {
    vector<string> ret;
    for (auto& i : database) {
        if (pos < i.size()) {
            ret.push_back(i[pos]);
        }
    }
    return ret;
}

vector<Peliculas> get_by_tag(Database* b){
    string busqueda;
    vector<Peliculas> peliculas;
    vector<string> d = b->getTags();
    cout << "Enter tag to search: "; cin >> busqueda;
    for(int i = 0; i < d.size();i++){
        if(d[i].find(busqueda) != string::npos){
            peliculas.push_back(Peliculas(b->imdb_id[i], b->title[i], b->plot_synopsis[i], b->tags[i], b->split[i], b->synopsis_source[i]));
        }
    }
    return peliculas;
}

void get_peliculas_tag_simple(vector<Peliculas> peliculas){
    for (int i = 0; i < 5; i++) {
        InfoBase infoBase(&peliculas[i]);
        infoBase.mostrar();
    }
}

void get_peliculas_tag_complejo(vector<Peliculas> peliculas){
    for (int i = 0; i < 5; i++) {
        InfoBase infoBase(&peliculas[i]);
        InfoCompleta infoCompleta(&infoBase);
        infoCompleta.mostrar();
    }
}

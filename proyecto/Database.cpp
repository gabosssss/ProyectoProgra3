#include "Database.h"
#include "Funciones.h"

//PATRÓN SINGLETON

using namespace std;

Database* Database::instance = nullptr;
vector<string> Database::imdb_id;
vector<string> Database::title;
vector<string> Database::plot_synopsis;
vector<string> Database::tags;
vector<string> Database::split;
vector<string> Database::synopsis_source;

Database* Database::getInstance() {
    if (instance == nullptr) {
        instance = new Database();
        initialize();
    }
    return instance;
}

void Database::initialize() {
    vector<vector<string>> database = fill_database();
    imdb_id = get_col(database, 0);
    title = get_col(database, 1);
    plot_synopsis = get_col(database, 2);
    tags = get_col(database, 3);
    split = get_col(database, 4);
    synopsis_source = get_col(database, 5);
}

void Database::agregarPelicula(string imdb_id, string title, string plot, string tags, string split, string synopsis_source) {
    this->imdb_id.push_back(imdb_id);
    this->title.push_back(title);
    this->plot_synopsis.push_back(plot);
    this->tags.push_back(tags);
    this->split.push_back(split);
    this->synopsis_source.push_back(synopsis_source);
    cout << "Película " << title << " agregada a la base de datos.\n";
}

void Database::eliminarPelicula(string imdb_id) {
    auto it = find(this->imdb_id.begin(), this->imdb_id.end(), imdb_id);
    if (it != this->imdb_id.end()) {
        int index = distance(this->imdb_id.begin(), it);
        this->imdb_id.erase(this->imdb_id.begin() + index);
        this->title.erase(this->title.begin() + index);
        this->plot_synopsis.erase(this->plot_synopsis.begin() + index);
        this->tags.erase(this->tags.begin() + index);
        this->split.erase(this->split.begin() + index);
        this->synopsis_source.erase(this->synopsis_source.begin() + index);
        cout << "Película con ID " << imdb_id << " eliminada de la base de datos.\n";
    } else {
        cout << "Película con ID " << imdb_id << " no encontrada en la base de datos.\n";
    }
}
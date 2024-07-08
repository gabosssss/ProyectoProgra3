#include "Database.h"
#include "../Funciones.h"

using namespace std;

Database* Database::instance = nullptr;
vector<string> Database::imdb_id;
vector<string> Database::title;
vector<string> Database::plot_synopsis;
vector<string> Database::tags;
vector<string> Database::split;
vector<string> Database::synopsis_source;


Database* Database::instance = nullptr;

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
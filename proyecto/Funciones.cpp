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


vector<string> split_avanzado(string texto, char separador) {
    vector<string> resultado;
    char delimitador = '"';
    string palabra="";
    bool dentroDeComillas = false;
    for (char ch : texto) {
        if (ch == delimitador) {
            dentroDeComillas = !dentroDeComillas;
        } else if (ch == separador && !dentroDeComillas) {
            resultado.push_back(palabra);
            palabra = "";
        } else {
            palabra += ch;
        }
    }
    if (!palabra.empty()) {
        resultado.push_back(palabra);
    }

    return resultado;
}

vector<vector<string>> fill_database() {
    vector<vector<string>> lines;
    ifstream data("../mpst_full_data_fixed.csv");
    if (!data.is_open()) {
        cerr << "Error: Could not open archive." << endl;
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

vector<Peliculas> get_by_column(Database* b, int col){
    string busqueda;
    vector<Peliculas> peliculas;
    vector<string> d;
    if(col == 1){
        d = b->getTitle();
    }
    else if(col == 2){
        d = b->getTags();
    }
    else if(col == 3){
        d = b->getSplit();
    }
    else{
        d = b->getPlotSynopsis();
    }
    cout << "Enter tag to search: "; cin >> busqueda;
    transform(busqueda.begin(), busqueda.end(), busqueda.begin(), ::tolower);
    for(int i = 0; i < d.size();i++){
        if(d[i].find(busqueda) != string::npos){
            peliculas.push_back(Peliculas(b->imdb_id[i], b->title[i], b->plot_synopsis[i], b->tags[i], b->split[i], b->synopsis_source[i]));
        }
    }
    return peliculas;
}

void mostrarPaginado(vector<Peliculas>& peliculas, UsuarioReal* usuario){
    int total = peliculas.size();
    int pagina = 0;
    const int tamanoPagina = 5;
    
    while (pagina * tamanoPagina < total) {
        for (int i = pagina * tamanoPagina; i < (pagina + 1) * tamanoPagina && i < total; ++i) {
            cout << i + 1 << ". ";
            InfoBase infoBase(&peliculas[i]);
            infoBase.mostrar();
            
        }
        
        cout << "\nOptions:\n";
        cout << "1. View details of movies\n";
        cout << "2. View next 5 movies\n";
        cout << "3. Exit\n";
        cout << "Enter an option: ";
        int opcion;
        cin >> opcion;
        
        if (opcion == 1) {
            cout << "Enter number of movie: ";
            int num;
            cin >> num;
            if (num > 0 && num <= total) {
                Peliculas& pelicula = peliculas[num - 1];
                InfoBase infoBase(&pelicula);
                InfoCompleta infoCompleta(&infoBase);
                infoCompleta.mostrar();
                
                cout << "\nOptions:\n";
                cout << "1. Like\n";
                cout << "2. Save for later\n";
                cout << "3. Exit\n";
                cout << "Enter an option: ";
                cin >> opcion;
                
                switch (opcion) {
                    case 1:
                        usuario->darLike(pelicula.imdb_id);
                        usuario->guardarLikesYVerMasTarde("../likes_y_ver_mas_tarde.csv");
                        cout << "You liked this movie.\n";
                        break;
                    case 2:
                        usuario->marcarVerMasTarde(pelicula.imdb_id);
                        usuario->guardarLikesYVerMasTarde("../likes_y_ver_mas_tarde.csv");
                        cout << "Movie saved for later.\n";
                        break;
                    case 3:
                        return;
                    default:
                        cout << "Invalid option.\n";
                }
            } else {
                cout << "Invalid movie number.\n";
            }
        } else if (opcion == 2) {
            if ((pagina + 1) * tamanoPagina < total) {
                pagina++;
            } else {
                cout << "There are no more movies to show.\n";
            }
        } else if (opcion == 3) {
            return;
        } else {
            cout << "Invalid option.\n";
        }
    }
}


void registrarUsuario(UsuarioManager& manager) {
    string nombre, contrasena, tipo;
    cout << "Enter username: "; cin >> nombre;
    cout << "Enter password: "; cin >> contrasena;
    UsuarioReal nuevoUsuario(nombre, contrasena, "regular");
    manager.agregarUsuario(nuevoUsuario);
    cout << "User registered successfully.\n";
}

UsuarioReal* login(UsuarioManager& manager) {
    string nombre, contrasena;
    cout << "Enter username: ";
    cin >> nombre;
    cout << "Enter password: ";
    cin >> contrasena;

    UsuarioReal* usuario = manager.buscarUsuario(nombre,contrasena);
    if (usuario) {
        cout << "Login successful.\n";
        return usuario;
    } else {
        cout << "Login failed. Invalid username or password.\n";
        return nullptr;
    }
}
Peliculas get_pelicula_by_id(Database* b, string imdb_id){
    vector<string>ids = b->imdb_id;
    for(int i = 0; i < ids.size();i++){
        if(ids[i] == imdb_id){
            return Peliculas(b->imdb_id[i],b->title[i], b->plot_synopsis[i], b->tags[i], b->split[i], b->synopsis_source[i]);
        }
    }
}

void mostrarPeliculasMarcadas(vector<string> imdb_ids, Database* b) {
    for (auto imdb_id : imdb_ids) {
        Peliculas pelicula = get_pelicula_by_id(b, imdb_id);
        
        if (pelicula.imdb_id== imdb_id) {
            cout << "Title: " << pelicula.title << endl;
            cout << "Tags: " << pelicula.tags << endl;
            cout << "Split: " << pelicula.split<< endl;
            cout << "Synopsis Source: " << pelicula.synopsis_source << endl;
            cout << "-----------------------\n";
        }
    }
}

void mostrarPeliculasMarcadas(UsuarioReal* usuario, Database* b) {
    cout << "Movies liked:\n";
    for (const string& imdb_id : usuario->getPeliculasLike()) {
        Peliculas pelicula = get_pelicula_by_id(b, imdb_id);
        if (!pelicula.imdb_id.empty()) {
            cout << "Title: " << pelicula.title << endl;
            cout << "Tags: " << pelicula.tags << endl;
            cout << "Split: " << pelicula.split << endl;
            cout << "Synopsis Source: " << pelicula.synopsis_source << endl;
            cout << "-----------------------\n";
        }
    }

    cout << "\nMovies to watch later:\n";
    for (const string& imdb_id : usuario->getPeliculasVerMasTarde()) {
        Peliculas pelicula = get_pelicula_by_id(b, imdb_id);
        if (!pelicula.imdb_id.empty()) {
            cout << "Title: " << pelicula.title << endl;
            cout << "Tags: " << pelicula.tags << endl;
            cout << "Split: " << pelicula.split << endl;
            cout << "Synopsis Source: " << pelicula.synopsis_source << endl;
            cout << "-----------------------\n";
        }
    }
}

void eliminarUsuario(UsuarioManager& manager) {
    string username;
    cout << "Enter username to delete: ";
    cin >> username;

    vector<UsuarioReal> usuarios = manager.getUsuarios();
    auto it = find_if(usuarios.begin(), usuarios.end(), [&](UsuarioReal& u) {
        return u.getNombre() == username;
    });

    if (it != usuarios.end()) {
        if (it->getTipo() != "admin") {
            manager.eliminarUsuario(username); // Eliminar el usuario del vector
            manager.guardarUsuarios("../usuarios_actualizados.csv"); // Guardar los cambios en el archivo CSV
            cout << "User " << username << " eliminated.\n";
        } else {
            cout << "Cannot erase another administrator.\n";
        }
    } else {
        cout << "User not found.\n";
    }
}

void interfaz(Database* b, UsuarioManager& manager) {
    system("cls");
    cout << "VIEW MOVIES" << endl << endl;
    cout << "1. Register user\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Enter an option: ";
    
    int opcion;
    cin >> opcion;

    while (opcion < 1 || opcion > 3) {
        cout << "Enter a valid option: ";
        cin >> opcion;
    }

    if (opcion == 1) {
        registrarUsuario(manager);
        manager.guardarUsuarios("../usuarios_actualizados.csv");
        interfaz(b, manager);
        return;
    }

    UsuarioReal* usuario = nullptr;

    if (opcion == 2) {
        usuario = login(manager);
        if (usuario) {
            usuario->cargarLikesYVerMasTarde("../likes_y_ver_mas_tarde.csv");
        }
    }

    if (opcion == 3 || usuario == nullptr) {
        cout << "Exiting...\n";
        return;
    }

    system("cls");
    cout << "Options:\n";
    cout << "1. Search by title\n";
    cout << "2. Search by tags\n";
    cout << "3. Search by split\n";
    cout << "4. Search by plot synopsis\n";
    cout << "5. View liked or saved movies\n";

    bool isAdmin = (usuario->getTipo() == "admin");

    if (isAdmin) {
        cout << "6. Delete user\n";
        cout << "7. Suspend user\n";
        cout << "8. Exit\n";
    } else {
        cout << "6. Exit\n";
    }

    cout << "Enter an option (1-";

    if (isAdmin) {
        cout << "8";
    } else {
        cout << "6";
    }

    cout << "): ";

    int a;
    cin >> a;

    while ((isAdmin && (a < 1 || a > 8)) || (!isAdmin && (a < 1 || a > 6))) {
        cout << "Enter a valid option (1-";
        
        if (isAdmin) {
            cout << "8";
        } else {
            cout << "6";
        }

        cout << "): ";
        cin >> a;
    }

    while (a != (isAdmin ? 8 : 6)) {
        if (isAdmin) {
            switch (a) {
                case 1: {
                    vector<Peliculas> peliculas = get_by_column(b, 1);
                    mostrarPaginado(peliculas, usuario);
                    break;
                }
                case 2: {
                    vector<Peliculas> peliculas = get_by_column(b, 2);
                    mostrarPaginado(peliculas, usuario);
                    break;
                }
                case 3: {
                    vector<Peliculas> peliculas = get_by_column(b, 3);
                    mostrarPaginado(peliculas, usuario);
                    break;
                }
                case 4: {
                    vector<Peliculas> peliculas = get_by_column(b, 4);
                    mostrarPaginado(peliculas, usuario);
                    break;
                }
                case 5: {
                    cout << "Movies liked:\n";
                    string username = usuario->getNombre();
                    vector<Peliculas> likes;
                    vector<Peliculas> ver_mas_tarde;
                    ifstream archivo("../likes_y_ver_mas_tarde.csv");
                    if (!archivo.is_open()) {
                        cerr << "Error while opening likes_y_ver_mas_tarde.csv" << endl;
                        return;
                    }

                    string linea;
                    while (getline(archivo, linea)) {
                        istringstream ss(linea);
                        string usr, imdb_id, estado;
                        
                        if (getline(ss, usr, ',') && std::getline(ss, imdb_id, ',') && std::getline(ss, estado, ',')) {
                            if (usr == username) {
                                if (estado == "like") {
                                    int pos = b->buscarPelicula_id(imdb_id);
                                    likes.push_back(Peliculas(b->imdb_id[pos],b->title[pos],b->plot_synopsis[pos],b->tags[pos],b->split[pos],b->synopsis_source[pos]));
                                } else if (estado == "ver_mas_tarde") {
                                    int pos = b->buscarPelicula_id(imdb_id);
                                    ver_mas_tarde.push_back(Peliculas(b->imdb_id[pos],b->title[pos],b->plot_synopsis[pos],b->tags[pos],b->split[pos],b->synopsis_source[pos]));
                                }
                            }
                        }
                    }

                    archivo.close();
                    
                    for(auto i : likes){
                        i.mostrar();
                    }

                    cout << "Movies saved:\n";
                    for(auto i : ver_mas_tarde){
                        i.mostrar();
                    }
                    break;
                }

                case 6: {
                    /*
                    cout << "Enter username to delete: ";
                    string username;
                    cin >> username;
                    vector<UsuarioReal> usuarios = manager.getUsuarios();
                    auto it = find_if(usuarios.begin(), usuarios.end(), [&](UsuarioReal u) {
                        return u.getNombre() == username;
                    });

                    if (it != usuarios.end()) {
                        if (it->getTipo() != "admin") {
                            usuarios.erase(it);
                            manager.guardarUsuarios("../usuarios_actualizados.csv");
                            cout << "User " << username << " eliminated.\n";
                        } else {
                            cout << "Cannot erase another administrator.\n";
                        }
                    } else {
                        cout << "User not found.\n";
                    }
                    
                    cout << "Enter username to delete: ";
                    string username;
                    cin >> username;
                    manager.eliminarUsuario(username); // Eliminar usuario usando la función de UsuarioManager
                    manager.guardarUsuarios("../usuarios_actualizados.csv"); // Guardar cambios en el archivo CSV
                    cout << "User " << username << " eliminated.\n";
                    */
                    eliminarUsuario(manager);
                    break;
                }
                case 7: {
                    cout << "Enter username to suspend: ";
                    string username;
                    cin >> username;
                    vector<UsuarioReal> usuarios = manager.getUsuarios();
                    auto it = find_if(usuarios.begin(), usuarios.end(), [&](UsuarioReal u) {
                        return u.getNombre() == username;
                    });

                    if (it != usuarios.end()) {
                        if (it->getTipo() != "admin") {
                            it->suspender();
                            manager.guardarUsuarios("../usuarios_actualizados.csv");
                            ofstream suspendidos("../usuarios_suspendidos.csv", ios::app);
                            suspendidos << it->getNombre() << "," << it->getContrasena() << "," << it->getTipo() << endl;
                            suspendidos.close();
                            cout << "User " << username << " suspended.\n";
                        } else {
                            cout << "Cannot suspend an administrator.\n";
                        }
                    } else {
                        cout << "User not found.\n";
                    }
                    break;
                }
                case 8: {
                    cout << "Exiting...\n";
                    break;
                }
                default:
                    break;
            }
        } else {
            switch (a) {
                case 1: {
                    vector<Peliculas> peliculas = get_by_column(b, 1);
                    mostrarPaginado(peliculas, usuario);
                    break;
                }
                case 2: {
                    vector<Peliculas> peliculas = get_by_column(b, 2);
                    mostrarPaginado(peliculas, usuario);
                    break;
                }
                case 3: {
                    vector<Peliculas> peliculas = get_by_column(b, 3);
                    mostrarPaginado(peliculas, usuario);
                    break;
                }
                case 4: {
                    vector<Peliculas> peliculas = get_by_column(b, 4);
                    mostrarPaginado(peliculas, usuario);
                    break;
                }
                case 5: {
                    cout << "Movies liked:\n";
                    string username = usuario->getNombre();
                    vector<Peliculas> likes;
                    vector<Peliculas> ver_mas_tarde;
                    ifstream archivo("../likes_y_ver_mas_tarde.csv");
                    if (!archivo.is_open()) {
                        cerr << "Error while opening likes_y_ver_mas_tarde.csv" << endl;
                        return;
                    }

                    string linea;
                    while (getline(archivo, linea)) {
                        istringstream ss(linea);
                        string usr, imdb_id, estado;
                        
                        if (getline(ss, usr, ',') && std::getline(ss, imdb_id, ',') && std::getline(ss, estado, ',')) {
                            if (usr == username) {
                                if (estado == "like") {
                                    int pos = b->buscarPelicula_id(imdb_id);
                                    likes.push_back(Peliculas(b->imdb_id[pos],b->title[pos],b->plot_synopsis[pos],b->tags[pos],b->split[pos],b->synopsis_source[pos]));
                                } else if (estado == "ver_mas_tarde") {
                                    int pos = b->buscarPelicula_id(imdb_id);
                                    ver_mas_tarde.push_back(Peliculas(b->imdb_id[pos],b->title[pos],b->plot_synopsis[pos],b->tags[pos],b->split[pos],b->synopsis_source[pos]));
                                }
                            }
                        }
                    }

                    archivo.close();
                    
                    for(auto i : likes){
                        i.mostrar();
                    }

                    cout << "Movies saved:\n";
                    for(auto i : ver_mas_tarde){
                        i.mostrar();
                    }
                    break;
                }

                case 6: {
                    cout << "Exiting...\n";
                    break;
                }
                default:
                    break;
            }
        }

        cout << "Enter an option (1-";
        
        if (isAdmin) {
            cout << "8";
        } else {
            cout << "6";
        }

        cout << "): ";
        cin >> a;
    }

    cout << "Exiting...\n";
}


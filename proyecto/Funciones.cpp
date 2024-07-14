#include "Funciones.h"
#include "Objetos/Peliculas.h"
#include "Objetos/Historial.h"

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

void get_peliculas_simple(vector<Peliculas> peliculas){
    for (int i = 0; i < 5; i++) {
        InfoBase infoBase(&peliculas[i]);
        infoBase.mostrar();
    }
}

void get_peliculas_complejo(vector<Peliculas> peliculas){
    for (int i = 0; i < 5; i++) {
        InfoBase infoBase(&peliculas[i]);
        InfoCompleta infoCompleta(&infoBase);
        infoCompleta.mostrar();
    }
}

void registrarUsuario(UsuarioManager& manager) {
    string nombre, contrasena, tipo;
    cout << "Ingrese nombre de usuario: "; cin >> nombre;
    cout << "Ingrese contrasena: "; cin >> contrasena;
    UsuarioReal nuevoUsuario(nombre, contrasena, "regular");
    manager.agregarUsuario(nuevoUsuario);
    cout << "Usuario registrado con exito.\n";
}

UsuarioReal* login(UsuarioManager& manager) {
    /*
    string nombre, contrasena;
    cout << "Ingrese nombre de usuario: "; cin >> nombre;
    cout << "Ingrese contrasena: "; cin >> contrasena;
    for (const auto& usuario : manager.getUsuarios()) {
        if (usuario.getNombre() == nombre && usuario.getContrasena() == contrasena) {
            cout << "Login exitoso.\n";
            return new UsuarioReal(usuario);
        }
    }
    cout << "Nombre de usuario o contrasena incorrectos.\n";
    return nullptr;
    */
    string nombre, contrasena;
    cout << "Ingrese nombre de usuario: "; cin >> nombre;
    cout << "Ingrese contrasena: "; cin >> contrasena;

    if (manager.estaSuspendido(nombre)) {
        cout << "This user is suspended and can not login.\n";
        return nullptr;
    }

    for (auto usuario : manager.getUsuarios()) {
        if (usuario.getNombre() == nombre && usuario.getContrasena() == contrasena) {
            cout << "Login successfull.\n";
            return new UsuarioReal(usuario);
        }
    }
    cout << "Wrong username or password.\n";
    return nullptr;
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
    cout << "5. Rewatch\n";

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

    while (a != (isAdmin ? 7 : 5)) {
        if (isAdmin) {
            switch (a) {
                case 1: {
                    vector<Peliculas> peliculas = get_by_column(b, 1);
                    get_peliculas_simple(peliculas);
                    break;
                }
                case 2: {
                    vector<Peliculas> peliculas = get_by_column(b, 2);
                    get_peliculas_simple(peliculas);
                    break;
                }
                case 3: {
                    vector<Peliculas> peliculas = get_by_column(b, 3);
                    get_peliculas_simple(peliculas);
                    break;
                }
                case 4: {
                    vector<Peliculas> peliculas = get_by_column(b, 4);
                    get_peliculas_simple(peliculas);
                    break;
                }
                case 5: {
                    if(!usuario.historial.empty()) {
                        if (!Usuario.historial.size()>3) {
                            for(int i=0;i<Usuario.historial.size();i++) {
                                cout<<Usuario.historial.estadoAnterior;
                            }
                        }
                    }
                    break;

                }
                case 6: {
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
                            cout << "Can not erase another administrator.\n";
                        }
                    } else {
                        cout << "User not found.\n";
                    }
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
                            cout << "Usuario " << username << " suspendido.\n";
                        } else {
                            cout << "Can not suspend an administrator.\n";
                        }
                    } else {
                        cout << "User not found.\n";
                    }
                    break;
                }
                default:
                    break;
            }
        } else {
            switch (a) {
                case 1: {
                    vector<Peliculas> peliculas = get_by_column(b, 1);
                    get_peliculas_simple(peliculas);
                    break;
                }
                case 2: {
                    vector<Peliculas> peliculas = get_by_column(b, 2);
                    get_peliculas_simple(peliculas);
                    break;
                }
                case 3: {
                    vector<Peliculas> peliculas = get_by_column(b, 3);
                    get_peliculas_simple(peliculas);
                    break;
                }
                case 4: {
                    vector<Peliculas> peliculas = get_by_column(b, 4);
                    get_peliculas_simple(peliculas);
                    break;
                }
                default:
                    break;
            }
        }

        cout << "Enter an option (1-";
        if (isAdmin) {
            cout << "7";
        } else {
            cout << "5";
        }
        cout << "): ";
        cin >> a;
    }

    cout << "Exiting...\n";
}
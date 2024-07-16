#include "Usuarios.h"
#include <fstream>
#include <sstream>

string UsuarioReal::getNombre(){
    return nombre;
}

string UsuarioReal::getTipo(){
    return tipo;
}

string UsuarioReal::getContrasena(){
    return contrasena;
}

UsuarioReal::UsuarioReal(string nombre,string contrasena,string tipo)
    : nombre(nombre), contrasena(contrasena), tipo(tipo), suspendido(false){
    }

void UsuarioReal::acceder(){
    if (suspendido) {
        cout << nombre << " is suspended and can not access the system. \n";
    } else {
        cout << nombre << " accessed as " << tipo << ".\n";
    }
}

bool UsuarioReal::isSuspendido(){
    return suspendido;
}

void UsuarioReal::suspender(){
    suspendido = true;
}

UsuarioReal::~UsuarioReal() {}

void UsuarioReal::darLike(string peliculaId){
    likedPeliculas.push_back(peliculaId);
}

void UsuarioReal::marcarVerMasTarde(string peliculaId){
    verMasTardePeliculas.push_back(peliculaId);
}

vector<string>& UsuarioReal::getPeliculasLike(){
    return likedPeliculas;
}

vector<string>& UsuarioReal::getPeliculasVerMasTarde(){
    return verMasTardePeliculas;
}

void UsuarioReal::cargarLikesYVerMasTarde(string archivo){
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error while opening " << archivo << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, imdb_id, estado;
        ss >> username >> imdb_id >> estado;
        if (username == nombre){
            if (estado == "like") {
            likedPeliculas.push_back(imdb_id);
            } else if (estado == "ver_mas_tarde") {
                verMasTardePeliculas.push_back(imdb_id);
            }
        }
    }

    file.close();
}

void UsuarioReal::guardarLikesYVerMasTarde(string archivo){
    ofstream file(archivo, ios::app);
    for (auto imdb_id : likedPeliculas){
        file << nombre << "," << imdb_id << ",like" << endl;
    }
    for (auto imdb_id : verMasTardePeliculas){
        file << nombre << "," << imdb_id << ",ver_mas_tarde" << endl;
    }
    file.close();
}


UsuarioProxy::UsuarioProxy(string nombre, string contrasena, string tipo)
    : nombre(nombre), contrasena(contrasena), tipo(tipo), usuarioReal(make_shared<UsuarioReal>(nombre, contrasena, tipo)) {}

bool UsuarioProxy::tieneAcceso(){
    return tipo == "admin";
}

void UsuarioProxy::acceder(){
    if (tieneAcceso()) {
        usuarioReal->acceder();
    } else {
        cout << nombre << " not allowed to access the system.\n";
    }
}

string UsuarioProxy::getNombre(){
    return nombre;
}

string UsuarioProxy::getTipo(){
    return tipo;
}

string UsuarioProxy::getContrasena(){
    return contrasena;
}

bool UsuarioProxy::isSuspendido(){
    return usuarioReal->isSuspendido();
}

void UsuarioProxy::suspender() {
    usuarioReal->suspender();
}

Admin::Admin(string nombre, string contrasena)
    : UsuarioReal(nombre, contrasena, "admin"){}

void Admin::suspenderUsuario(UsuarioReal& usuario){
    if (usuario.getTipo() != "admin") {
        usuario.suspender();
        cout << "Administrator " << getNombre() << " has suspended user " << usuario.getNombre() << ".\n";
    } else{
        cout << "Can not suspend another administrator.\n";
    }
}

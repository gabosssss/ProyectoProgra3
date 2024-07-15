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
    : nombre(nombre), contrasena(contrasena), tipo(tipo), suspendido(false) {
        elHistorial = new Historial(); 
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

UsuarioReal::~UsuarioReal() {
    delete elHistorial;
}

void UsuarioReal::darLike(string peliculaId){
    elHistorial->agregarPelicula(peliculaId);
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

void UsuarioReal::cargarLikesYVerMasTarde(string archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << archivo << endl;
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

void UsuarioProxy::acceder() {
    if (tieneAcceso()) {
        usuarioReal->acceder();
    } else {
        cout << nombre << " no tiene permiso para acceder al sistema.\n";
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
    : UsuarioReal(nombre, contrasena, "admin") {}

void Admin::suspenderUsuario(UsuarioReal& usuario){
    if (usuario.getTipo() != "admin") {
        usuario.suspender();
        cout << "El administrador " << getNombre() << " ha suspendido a " << usuario.getNombre() << ".\n";
    } else{
        cout << "No se puede suspender a otro administrador.\n";
    }
}

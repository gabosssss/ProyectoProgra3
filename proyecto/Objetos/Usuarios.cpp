#include "Usuarios.h"

string UsuarioReal::getNombre(){
    return nombre;
}

string UsuarioReal::getTipo() {
    return tipo;
}

string UsuarioReal::getContrasena(){
    return contrasena;
}

UsuarioReal::UsuarioReal(string nombre,string contrasena,string tipo)
    : nombre(nombre), contrasena(contrasena), tipo(tipo), suspendido(false) {}

void UsuarioReal::acceder() {
    if (suspendido) {
        cout << nombre << " is suspended and can not access the system. \n";
    } else {
        cout << nombre << " accessed as " << tipo << ".\n";
    }
}

bool UsuarioReal::isSuspendido(){
    return suspendido;
}

void UsuarioReal::suspender() {
    suspendido = true;
}

void UsuarioReal::darLike(string peliculaId) {
    likedPeliculas.push_back(peliculaId);
    cout << "Película " << peliculaId << " marcada como 'liked' por " << nombre << ".\n";
}

void UsuarioReal::marcarVerMasTarde(string peliculaId) {
    verMasTardePeliculas.push_back(peliculaId);
    cout << "Película " << peliculaId << " marcada como 'ver mas tarde' por " << nombre << ".\n";
}

void UsuarioReal::mostrarLikedPeliculas() {
    cout << "Películas 'liked' por " << nombre << ":\n";
    for (const auto& id : likedPeliculas) {
        cout << "- " << id << "\n";
    }
}

void UsuarioReal::mostrarVerMasTardePeliculas(){
    cout << "Peliculas marcadas como 'ver mas tarde' por " << nombre << ":\n";
    for (const auto& id : verMasTardePeliculas) {
        cout << "- " << id << "\n";
    }
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

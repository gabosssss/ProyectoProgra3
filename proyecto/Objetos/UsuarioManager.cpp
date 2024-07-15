#include "UsuarioManager.h"
#include <iostream>

UsuarioManager::UsuarioManager(){}

void UsuarioManager::agregarUsuario(UsuarioReal usuario){
    usuarios.push_back(usuario);
}

vector<UsuarioReal> UsuarioManager::getUsuarios(){
    return usuarios;
}

void UsuarioManager::cargarUsuarios(string archivo){
    ifstream file(archivo);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string nombre, contrasena, tipo;
        getline(ss, nombre, ',');
        getline(ss, contrasena, ',');
        getline(ss, tipo, ',');
        usuarios.push_back(UsuarioReal(nombre, contrasena, tipo));
    }
    file.close();
}

void UsuarioManager::guardarUsuarios(string archivo){
    ofstream archivoSalida(archivo);
    if (archivoSalida.is_open()){
        for (auto usuario : usuarios) {
            archivoSalida << usuario.getNombre() << "," << usuario.getContrasena() << "," << usuario.getTipo() << "\n";
        }
        archivoSalida.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo " << archivo << " para escritura." << endl;
    }
    archivoSalida.close();
    
}

void UsuarioManager::eliminarUsuario(string nombreUsuario){
    auto it = find_if(usuarios.begin(), usuarios.end(), [&](UsuarioReal u) {
        return u.getNombre() == nombreUsuario;
    });
    if (it != usuarios.end()){
        usuarios.erase(it);
    } else{
        cout << "Usuario no encontrado.\n";
    }
}


UsuarioReal* UsuarioManager::buscarUsuario(string nombre){
    for (auto& usuario : usuarios) {
        if (usuario.getNombre() == nombre) {
            return &usuario;
        }
    }
    return nullptr;
}

void UsuarioManager::cargarUsuariosSuspendidos(string archivo){
    ifstream file(archivo);
    string line;
    while (getline(file, line)){
        stringstream ss(line);
        string nombre;
        getline(ss, nombre, ',');
        usuariosSuspendidos.push_back(nombre);
    }
    file.close();
}

bool UsuarioManager::estaSuspendido(string nombreUsuario){
    return find(usuariosSuspendidos.begin(), usuariosSuspendidos.end(), nombreUsuario) != usuariosSuspendidos.end();
}

void UsuarioManager::guardarLikesYVerMasTarde(string archivo){
    for (auto usuario : usuarios) {
        usuario.guardarLikesYVerMasTarde(archivo);
    }
}
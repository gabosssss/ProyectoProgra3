#ifndef USUARIOMANAGER_H
#define USUARIOMANAGER_H

#include "Usuarios.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

class UsuarioManager {
private:
    vector<UsuarioReal> usuarios;
    vector<string> usuariosSuspendidos;

public:
    UsuarioManager();
    void cargarUsuarios(string archivo);
    void guardarUsuarios(string archivo);
    void agregarUsuario(UsuarioReal usuario);
    void eliminarUsuario(string nombreUsuario);
    vector<UsuarioReal> getUsuarios();
    UsuarioReal* buscarUsuario(string nombre, string contrasena);
    UsuarioReal* buscarUsuario(string nombre);
    void cargarUsuariosSuspendidos(string archivo);
    bool estaSuspendido(string nombreUsuario);
    void guardarLikesYVerMasTarde(string archivo);
};

#endif // USUARIOMANAGER_H

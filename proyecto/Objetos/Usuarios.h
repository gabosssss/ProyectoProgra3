#ifndef USUARIOS_H
#define USUARIOS_H

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

//USANDO PROXY

struct Usuario{
    virtual void acceder() = 0;
    virtual string getNombre() = 0;
    virtual string getTipo() = 0;
    virtual string getContrasena() = 0;
    virtual bool isSuspendido() = 0;
    virtual void suspender() = 0;
    virtual ~Usuario() = default;
};

class UsuarioReal : public Usuario {
private:
    string nombre;
    string contrasena;
    string tipo;
    bool suspendido;
    vector<string> likedPeliculas;
    vector<string> verMasTardePeliculas;

public:
    UsuarioReal() = default;
    UsuarioReal(string nombre, string contrasena, string tipo);
    void acceder() override;
    string getNombre() override;
    string getTipo() override;
    string getContrasena() override;
    bool isSuspendido();
    void suspender();
    ~UsuarioReal(); 

    // Métodos para gestionar "like" y "ver más tarde"
    void darLike(string imdb_id);
    void marcarVerMasTarde(string imdb_id);
    vector<string>& getPeliculasLike();
    vector<string>& getPeliculasVerMasTarde();
    void cargarLikesYVerMasTarde(string archivo);
    void guardarLikesYVerMasTarde(string archivo);

};

class UsuarioProxy : public Usuario {
private:
    shared_ptr<UsuarioReal> usuarioReal;
    string nombre;
    string contrasena;
    string tipo;
    bool tieneAcceso();

public:
    UsuarioProxy(string nombre, string contrasena, string tipo);
    void acceder() override;
    string getNombre() override;
    string getTipo() override;
    string getContrasena() override;
    bool isSuspendido() override;
    void suspender() override;
};

class Admin : public UsuarioReal {
    public:
    Admin(string nombre, string contrasena);
    void suspenderUsuario(UsuarioReal& usuario);
};

#endif // USUARIOS_H
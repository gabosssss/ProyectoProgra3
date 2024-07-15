#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include "Peliculas.h"
#include "Info_peli.h"
#include "Usuarios.h"
#include "UsuarioManager.h"
#include "Funciones.h"
#include "Database.h"

using namespace std;

int main() {
    
    UsuarioManager manager;
    Database* database = Database::getInstance();

    // Cargar usuarios desde un archivo CSV
    manager.cargarUsuarios("../usuarios_actualizados.csv");
    manager.cargarUsuariosSuspendidos("../usuarios_suspendidos.csv");

    ifstream archivo("../likes_y_ver_mas_tarde.csv");
    if (archivo.is_open()) {
        string linea;
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            vector<string> datos = split(linea, ',');
            if (datos.size() == 3) {
                string username = datos[0];
                string imdb_id = datos[1];
                string estado = datos[2];

                UsuarioReal* usuario = manager.buscarUsuario(username);
                if (usuario) {
                    if (estado == "like") {
                        usuario->darLike(imdb_id);
                    } else if (estado == "ver_mas_tarde") {
                        usuario->marcarVerMasTarde(imdb_id);
                    }
                } else {
                    cerr << "Usuario no encontrado: " << username << endl;
                }
            }
        }

        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo 'likes_y_ver_mas_tarde.csv'" << endl;
    }

    // Mostrar la interfaz
    interfaz(database, manager);
    return 0;
}


// Correr
// cd proyecto
// g++ -o programa main.cpp Objetos/Historial.cpp Objetos/Info_peli.cpp Objetos/Memento.cpp Objetos/Peliculas.cpp Objetos/UsuarioManager.cpp Objetos/Usuarios.cpp Database.cpp Funciones.cpp -I./Objetos
// ./programa
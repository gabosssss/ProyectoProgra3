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

    // Mostrar la interfaz
    interfaz(database, manager);
    return 0;
}


// Correr
// g++ main.cpp Funciones.cpp Database.cpp Objetos/UsuarioManager.cpp Objetos/Usuarios.cpp Objetos/Info_peli.cpp Objetos/Peliculas.cpp -I./ -I./Objetos -o main
// ./main.exe
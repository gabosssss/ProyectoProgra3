#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <vector>
#include "Objetos/Peliculas.h"
#include "Database.h"
#include "Objetos/Info_peli.h"
#include "Objetos/UsuarioManager.h"
#include "Objetos/Usuarios.h"
#include <fstream>
#include <algorithm>
#include <cctype>
using namespace std;

vector<string> split(string texto, char separador);
vector<string> split_avanzado(string texto, char separador);
vector<vector<string>> fill_database();
vector<string> get_col(vector<vector<string>> database, int pos);
vector<Peliculas> get_by_column(Database*, int);
void get_peliculas_tag_simple(vector<Peliculas>);
void get_peliculas_tag_complejo(vector<Peliculas>);
void registrarUsuario(UsuarioManager&);
UsuarioReal* login(UsuarioManager&);
void interfaz(Database*, UsuarioManager&);

#endif // FUNCIONES_H

//Fuente usada: https://www.geeksforgeeks.org/csv-file-management-using-c/
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <vector>

using namespace std;

vector<string> split(string texto, char separador);
vector<string> split_avanzado(string texto, char separador);
vector<vector<string>> fill_database();
vector<string> get_col(vector<vector<string>> database, int pos);

#endif // FUNCIONES_H

//Fuente usada: https://www.geeksforgeeks.org/csv-file-management-using-c/
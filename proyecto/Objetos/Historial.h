
#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <iostream>
#include <stack>
#include "Peliculas.cpp"
#include "Usuarios.cpp"
#include "Memento.h"


class Historial {
private:
    stack<Memento> historial;
public:
    Historial();
    void agregarPelicula (const string& estado);
    stack<Memento> obtenerHistorial() const;
    string estadoAnterior();
    ~Historial();
};



#endif //HISTORIAL_H

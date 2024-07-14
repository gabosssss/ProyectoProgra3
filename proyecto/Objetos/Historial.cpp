
#include "Historial.h"
#include <iostream>

using namespace std;

Historial::Historial() {}

Historial::~Historial() {}

void Historial::agregarPelicula(const string &estado) {
    historial.push(Memento(estado));
}

string Historial::estadoAnterior() {
    if (historial.size()>1) {
        historial.pop();
        return historial.top().ObtEstado();
    }
    return "Historial vacio";
}

stack<Memento> Historial::obtenerHistorial() const {
    return this->historial;
}


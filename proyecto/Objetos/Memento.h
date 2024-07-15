#ifndef MEMENTO_H
#define MEMENTO_H

#include <iostream>

using namespace std;


class Memento {
private:
    string estado;
public:
    Memento(string e):estado(e){}
    string ObtEstado() const;
    ~Memento(){}
};

#endif //MEMENTO_H

//
// Created by gab11 on 14/07/2024.
//

#ifndef MEMENTO_H
#define MEMENTO_H

#include <iostream>

using namespace std;


class Memento {
private:
    string estado;
public:
    Memento(const string& e):estado(e){}
    string ObtEstado() const;
    ~Memento(){}
};



#endif //MEMENTO_H

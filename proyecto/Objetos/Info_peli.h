#ifndef INFO_PELI_H
#define INFO_PELI_H

#include "Peliculas.h"

//Estas clases básicamente es para ver en la consola

class InfoBase : public Peliculas{
    public:
        InfoBase(Peliculas* pelicula);
        void mostrar();
};

class InfoDecorador : public Peliculas{
    public:
        Peliculas* info;
        InfoDecorador() = default;
        InfoDecorador(Peliculas*);
        void mostrar();
};

class InfoCompleta : public InfoDecorador{
    public:
    InfoCompleta(Peliculas* pelicula);
    void mostrar();
};

#endif // INFO_PELI_H
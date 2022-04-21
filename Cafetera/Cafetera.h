#ifndef CAFETERA_H
#define CAFETERA_H

#include <iostream>
using namespace std;

class Cafetera
{
    private:
        int capacidadMaxima;
        int capacidadActual;
    
    public:
        Cafetera();
        Cafetera(int cM);
        Cafetera(int cM, int cA);

        void vaciarCafetera();
        void llenarCafetera();
        void servirTaza(int capacidadTaza);
        void agregarCafe(int mlCafe);
};

Cafetera::Cafetera()
{
    capacidadMaxima = 1000;
    capacidadActual = 0;
}

Cafetera::Cafetera(int cM)
{
    capacidadMaxima = cM;
}

Cafetera::Cafetera(int cM, int cA)
{
    capacidadMaxima = cM;
    capacidadActual = cA;
}

void Cafetera::vaciarCafetera()
{
    capacidadActual = 0;
}

void Cafetera::llenarCafetera()
{
    capacidadActual = capacidadMaxima;
}

void Cafetera::servirTaza(int capacidadTaza)
{
    if(capacidadActual >= capacidadTaza)
    {
        capacidadActual = capacidadActual - capacidadTaza;
    }

    else
    {
        capacidadActual = 0;
    }
}

void Cafetera::agregarCafe(int mlCafe)
{

    if(capacidadActual + mlCafe >= capacidadMaxima)
    {
        capacidadActual = capacidadMaxima;
    }

    else
    {
        capacidadActual = capacidadActual + mlCafe;
    }
}

#endif//CAFETERA_H
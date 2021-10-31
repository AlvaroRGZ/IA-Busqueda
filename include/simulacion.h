#include "mundo_acotado.h"
#include <ctime>


#pragma once

class Simulation {

    private:

    int max_iter;
    int curr_iter;
    Vehicle* vehicle;
    World *grid;

    public:

    Simulation();
    Simulation(int);
    Simulation(World*, Vehicle*, int);
    ~Simulation();

    int GetMaxIter(void); // devuelve el número máximo de iteraciones
    int GetCurrIter(void); // devuelve el número actual de iteraciones

    void SetMaxIter(int);
    void SetCurrIter(int);

    void BusquedaAEstrella();
    void Loop(void);
    void Sort(void);
    void PrintData(void);
};
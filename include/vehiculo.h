class World;

#include <iostream>
#include "stdio.h"
#include "funciones.h"
#include <vector>
#pragma once

class Vehicle {

    protected:

  

    int row_pos;
    int column_pos;
    int direction;
    int destination_row;
    int destination_col;
    std::vector<bool> sensor;

    virtual void Turn45(bool) = 0;
    virtual void Turn45(char) = 0;

    //virtual void Move_4(funcion_heuristica& f) = 0; // hace que avance su posición una casilla en función de su dirección
    //virtual void Move_8(funcion_heuristica& f) = 0; 
    //Aplica el algoritmo A* para llegar al destino.
    virtual void Move(void) = 0; 

    public:

    Vehicle();
    Vehicle(int, int, int, int, int);
    ~Vehicle();

    int GetRow(void); // devuelve la fila en la que se encuentra el taxi
    int GetColumn(void); // devuelve la columna en la que se encuentra el taxi
    int GetDirection(void); // devuelve la dirección que tiene
    int GetDestinationRow(void); // devuelve la fila en la que se encuentrab la direccion de destino del vehiculo
    int GetDestinationColumn(void); // devuelve la columna en la que esta la direccion de destino

    void SetRow(int);
    void SetColumn(int);
    void SetDirection(int);

    virtual void Update(World&); // hace el giro y el movimiento en funcion de la casilla

    virtual void PrintDirection(void) = 0;
};
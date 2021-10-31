#pragma once

//#include "mundo.h"
#include "vector.h"
#include "funciones.h"

//class World;

#include <iostream>
#include "stdio.h"
//#include "funciones.h"
#include <vector>
#include <stack>
#include <bits/stdc++.h>

typedef Vector<Vector<Cell>> Mundo_t;

class Vehicle {

    public: //antes private

    funcion_heuristica* f_heuristica_;

    int row_pos;
    int column_pos;
    int direction;
    int destination_row;
    int destination_col;
    int expansion;

    int WorldSizeX, WorldSizeY;
    std::stack<Posicion_t> Solucion_;

    //Atributos necesarios para la posicion

    Posicion_t Origen, Destino;

    std::vector<bool> sensor;

    virtual void Turn45(bool) = 0;
    virtual void Turn45(char) = 0;

    //virtual void Move_4(funcion_heuristica& f) = 0; // hace que avance su posición una casilla en función de su dirección
    //virtual void Move_8(funcion_heuristica& f) = 0; 
    //Aplica el algoritmo A* para llegar al destino.
    virtual void Move(Mundo_t& MainGrid) = 0; 

    public:

    Vehicle();
    Vehicle(int, int, int, int, int, int, int,  funcion_heuristica*);
    ~Vehicle();

    int GetRow(void); // devuelve la fila en la que se encuentra el taxi
    int GetColumn(void); // devuelve la columna en la que se encuentra el taxi
    int GetDirection(void); // devuelve la dirección que tiene
    int GetDestinationRow(void); // devuelve la fila en la que se encuentrab la direccion de destino del vehiculo
    int GetDestinationColumn(void); // devuelve la columna en la que esta la direccion de destino
    int GetExpansion(void);

    int GetWorldX(void){ return WorldSizeX; }
    int GetWorldY(void){ return WorldSizeY; }

    Posicion_t GetOrigen (void){ return Origen; }
    Posicion_t GetDestino(void){ return Destino;}

    funcion_heuristica* Get_f_Heuristica(void);

    //Metodos necesarios para A*
    bool isValid(int row, int col);
    bool isUnBlocked(Mundo_t& Grid, int row, int col);
    bool isDestination(int row, int col, Posicion_t dest);
    //void tracePath(Cell& cellDetails[WorldSizeX][WorldSizeY], Posicion_t dest); //Arreglar eso

    double calculateHValue(int row, int col, Posicion_t dest);

    void SetRow(int);
    void SetColumn(int);
    void SetDirection(int);
    void AddExpansion(void);

    virtual void Update(Mundo_t& Grid); // hace el giro y el movimiento en funcion de la casilla

    virtual void PrintDirection(void) = 0;
};

#pragma once

//#include "taxi4.h"
#include "vehiculo.h"
#include "vector.h"
#include "celda.h"
//#include "funciones.h"

#include <fstream>
#include <iostream>
#include <random>
#include "stdio.h"
#include <sstream>
#include <unistd.h>

typedef Vector<Vector<Cell>> Mundo_t;

class World {

protected:

//funcion_heuristica* f_heuristica_;
int row;
int column;
int size;
Mundo_t world;



public:

World(); // Constructor por defecto
World(int, int); // Constructor por tamaño
explicit World(int, int, int, int);
explicit World(int, int, int, int, int);
virtual ~World(); // Destructor

inline int GetRow() {
    return row;
} // devuelve el número total de filas

inline int GetColumn() {
    return column;
} // devuelve el número total de columnas

inline int GetSize() {
    return size;
}// devuelve el tamaño de la matriz

inline Cell GetCell(int i, int j){
    try{
        return world[i][j];   
    }
    catch(std::exception& e){
        throw e;
    }   
}

inline Mundo_t& GetWorld(void){
    return world;
} // pasa el mundo por referencia

//funcion_heuristica* Get_f_Heuristica(void){
//  return f_heuristica_;
//}

char GetWorldState(int, int); // devuelve el "estado" de una celda (blanco o negro)
bool GetWorldValue(int, int); // devuelve el estado booleano de una celda

void SetRow(int);
void SetColumn(int);
void SetSize(int);

int GetWorldX(int, int);
int GetWorldY(int, int);

void SetWorldState(char, int, int); // establecer el "estado" de una celda
void SetWorldValue(bool, int, int); // establecer el valor booleano de una celda
void ToggleWorldValue(int, int);
void SetWorld(Mundo_t&);

virtual void ReSize(Vehicle*) = 0;

void PrintWorld(void); // imprime la matriz sola
void PrintHorizontalWall(void); // imprime un muro horizontal
void PrintGrid (Vehicle*);
void PrintSolucion(Vehicle* vehicle);

bool VehicleOut(Vehicle*);
void TryPosition(Vehicle*);


//Pruebas
bool is_in_set(Cell c, const Vector<Cell>& s);
void reconstruir_camino(Vector<Cell> &v, Cell actual, Cell I);
void CambiarHeuristica(bool opt);

void caminoMinimo(unsigned int xInicio, unsigned int yInicio,
                  unsigned int xFinal, unsigned int yFinal);

Vector<Cell> Astar(unsigned int xInicio, unsigned int yInicio,
                   unsigned int xFinal,  unsigned int yFinal);

};
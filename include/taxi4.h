#pragma once

#include "vehiculo.h"

class Taxi4: public Vehicle{

using Vehicle::Vehicle;

virtual void Turn45(char colour);

virtual void Turn45(bool colour);

double calculateHValue(World& Grid, int row, int col, Posicion_t dest);


//Implementa el algoritmo A* 
virtual void Move(World& MainGrid);

virtual void PrintDirection(void);

};

// FALTA POR DECLARAR ESTA FUNCION PERO DA EL ERROR EN LA MATRIZ
/*
void Vehicle::tracePath(Cell& cellDetails[WorldSizeX][WorldSizeY], Posicion_t Destino){
    std::cout << "\nThe Path is ";
    int row = Destino.first;
    int col = Destino.second;
 
    std::stack<Posicion_t> Path;
 
    while (!(cellDetails[row][col].GetPadreX() == row
             && cellDetails[row][col].GetPadreY() == col)) {
        Path.push(std::make_pair(row, col));
        int temp_row = cellDetails[row][col].GetPadreX();
        int temp_col = cellDetails[row][col].GetPadreX();
        row = temp_row;
        col = temp_col;
    }
 
    Path.push(std::make_pair(row, col));
    while (!Path.empty()) {
        std::pair<int, int> p = Path.top();
        Path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
    }
 
    return;
}
*/








/**
 
 
 virtual void Move(void) {
    if(direction == 1)
        row_pos += -1;
    else if(direction == 2) {
        column_pos += 1;
    }
    else if (direction == 3)
        row_pos += 1;
    else if(direction == 4) {
        column_pos += -1;
    }
    else std::cout << "ERROR, direction = " << direction << std::endl;
}
};
 
 */


// REALIZA EL MOVIMIENTO SIN INFORMACION
/*virtual void Move(void) { // se mueve en el entorno (coordenadas)
    
    if(direction == 1)
        row_pos += -1;
    else if(direction == 2) {
        row_pos += -1;
        column_pos += 1;
    }
    else if (direction == 3)
        column_pos += 1;
    else if(direction == 4) {
        row_pos += 1;
        column_pos += 1;
    }
    else if(direction == 5)
        row_pos += 1;
    else if(direction == 6) {
        row_pos += 1;
        column_pos += -1;
    }
    else if(direction == 7)
        column_pos += -1;
    else if(direction == 8) {
        row_pos += -1;
        column_pos += -1;
    }
    else std::cout << "ERROR, direccion = " << direction << std::endl;

}
*/
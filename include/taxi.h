#include "vehiculo.h"

#pragma once

class Taxi: public Vehicle
{

using Vehicle::Vehicle;

virtual void Turn45(char colour) {
    if(colour == ' '){ // si la casilla es blanca
        if((direction <= 8) && (direction > 1)) // giro a la izquierda
            direction--;
        else if(direction == 1)
            direction = 8;
        else std::cout << "ERROR, direccion = " << direction << std::endl;
    }
    else if(colour == 'X') { // si la casilla es negra
        if((direction >= 1) && (direction < 8)) // giro a la derecha
            direction++;
        else if (direction == 8)
            direction = 1;
        else std::cout << "ERROR, direccion = " << direction << std::endl;
    }
}

virtual void Turn45(bool colour){
    if(colour == false){ // si la casilla es blanca 
        if((direction <= 8) && (direction > 1)) // giro a la izquierda
            direction--;
        else if(direction == 1)
            direction = 8;
        else std::cout << "ERROR, direccion = " << direction << std::endl;
    }
    else {
        if((direction >= 1) && (direction < 8)) // giro a la derecha
            direction++;
        else if (direction == 8)
            direction = 1;
        else std::cout << "ERROR, direccion = " << direction << std::endl;
    }
}

virtual void Move(void) { // se mueve en el entorno (coordenadas)
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

virtual void PrintDirection(void){ // imprime las flechas para representar las direcciones que se toman
    int direction = GetDirection();
    switch(direction){
        case 1: std::cout << "\u2191"; // Unicode Character 'UPWARDS ARROW'
        break;

        case 2: std::cout << "\u2197"; // Unicode Character 'NORTH EAST ARROW
        break;

        case 3: std::cout << "\u2192"; // Unicode Character 'RIGHTWARDS ARROW'
        break;

        case 4: std::cout << "\u2198"; // Unicode Character 'SOUTH EAST ARROW'
        break;

        case 5: std::cout << "\u2193"; // Unicode Character 'DOWNWARDS ARROW'
        break;

        case 6: std::cout << "\u2199"; // Unicode Character 'SOUTH WEST ARROW'
        break;

        case 7: std::cout << "\u2190"; // Unicode Character 'LEFTWARDS ARROW'
        break;

        case 8: std::cout << "\u2196"; // Unicode Character 'NORTH WEST ARROW'
        break;
    }
}

};
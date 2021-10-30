#pragma once

#include "vehiculo.h"

class Taxi8: public Vehicle {

  //using Vehicle::Vehicle;
  public:
  Taxi8(int i, int j, int direction_, int row_destination,
                 int col_destination, int Wx, int Wy, funcion_heuristica* fh): 
                 Vehicle(i,j,direction_,row_destination,col_destination,Wx,Wy,fh){}

  virtual void Turn45(char colour);

  virtual void Turn45(bool colour);

  //Implementa el algoritmo A* 
  virtual void Move(Mundo_t& MainGrid);

  virtual void PrintDirection(void);
  
};
#include <cmath>
#include "celda.h"

class funcion_heuristica{

  virtual int funcionheuristica(int x_act, int y_act, int x_fin, int y_fin) = 0;

};

class F_Rectilinea: public funcion_heuristica{

  //Rectilinea();
  int funcionheuristica(int x_act, int y_act, int x_fin, int y_fin){
    return fabs((x_fin-x_act) + (y_fin-y_act));
  }

};

class F_Euclidiana: public funcion_heuristica{

  int funcionheuristica(int x_act, int y_act, int x_fin, int y_fin){
    return static_cast<int>(sqrt(pow((x_fin-x_act),2) + pow((y_fin-y_act), 2)));
    //trunca al menor
  }
};
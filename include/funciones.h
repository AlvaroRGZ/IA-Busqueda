#include <cmath>
#include "celda.h"

class funcion_heuristica{

  int Rectilinea(int x_act, int y_act, int x_fin, int y_fin){
    return fabs((x_fin-x_act) + (y_fin-y_act));
  }

  float Euclidiana(int x_act, int y_act, int x_fin, int y_fin){
    return static_cast<int>(sqrt(pow((x_fin-x_act),2) + pow((y_fin-y_act), 2)));
    //trunca al menor
  }

};
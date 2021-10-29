#include <cmath>
#include "celda.h"

class funcion_heuristica{
  public:
  virtual int operator()(int x_act, int y_act, int x_fin, int y_fin) = 0;
  //virtual ~funcion_heuristica(void) = 0;

};

class F_Manhattan: public funcion_heuristica{

  //Rectilinea();
  public:
  int operator()(int x_act, int y_act, int x_fin, int y_fin){
    return fabs((x_fin-x_act) + (y_fin-y_act));
  }
  //~F_Manhattan(void){}

};

class F_Euclidiana: public funcion_heuristica{
  public:
  int operator()(int x_act, int y_act, int x_fin, int y_fin){
    return static_cast<int>(sqrt(pow((x_fin-x_act),2) + pow((y_fin-y_act), 2)));
    //trunca al menor
  }
  //~F_Euclidiana(void){}
};
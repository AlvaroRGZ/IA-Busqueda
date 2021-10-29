#pragma once

#include <utility>
/*
struct Cell {

    bool value; // Libre    --> false
                // No libre --> true
                
    char state = ' '; // X   --> significa que el taxi ha pasado previamente por ese sitio
                      // " " --> significa que está libre
                      // O   --> significa que hay un obstáculo
    
};*/

// PARA LA CLASE Cell.h:

typedef std::pair <int,int> Posicion_t;
typedef std::pair<double, std::pair<int, int> > pPair;

class Cell {

    private:

    bool is_closed_; // Está en closed_list?

    bool is_frontier_; // Está en open_list?

    bool value = false; //libre(false) u ocupado (true)

    char state = ' '; // X pasó por ahí, " " libre, O obstaculo.

    int x; //coordenada x

    int y; //cordenada y

    Posicion_t Posicion;

    //Coordenadas del padre
    int padre_x_;

    int padre_y_;

    double f_; // Coste estimado desde nodo inicial a nodo objetivo (g(n) + h(n))
    double h_; // Coste estimado desde este nodo al nodo objetivo
    double g_; // Coste desde el nodo inicial a este nodo

    public:

    Cell(int row = 0, int col = 0) {
      x = row;
      y = col;
      Posicion = std::make_pair(row,col);
    }

    ~Cell() {};

    bool GetValue() const{
      return value;
    }

    char GetState() const{
      return state;
    }

    int GetX() const{
      return x;
    }

    int GetY() const{
      return y;
    }

    void SetValue(bool new_value) {
      value = new_value;
    }

    void SetState(char new_state) {
      state = new_state;
    }

    void SetX(int x_) {
      x = x_;
      Posicion.first = x_;
    }

    void SetY(int y_) {
      y = y_;
      Posicion.second = y_;
    }

    void SetPos(int x_, int y_) {
      y = y_;
      x = x_;
      Posicion = std::make_pair(x_,y_);
    }

    bool IsBlocked(void){
      return value;
    }

    //Getter |setters de las f heuristicas

    void SetF(double f) {
      f_ = f;
    }
    double GetF(void) const{
      return f_;
    }

    void SetG(double g) {
      g_ = g;
    }
    
    double GetG(void) const{
      return g_;
    }
        
    void SetH(double h) {
      h_ = h;
    }

    double GetH(void) const{
      return h_;
    }


    int GetPadreX(void) const{
      return padre_x_;
    }

    int GetPadreY(void) const{
      return padre_y_;
    }

    void SetPadreX(int p){
      padre_x_ = p;
    }

    void SetPadreY(int p){
      padre_y_ = p;
    }

};


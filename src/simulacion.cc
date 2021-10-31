#include "../include/simulacion.h"

long t0, t1;

// Constructores
Simulation::Simulation() {
    max_iter = 10;
    curr_iter = 0;
}

Simulation::Simulation(int iter){
    max_iter = iter;
    curr_iter = 0;
}

Simulation::Simulation(World* world, Vehicle* taxi, int iterations){
    max_iter = iterations;
    curr_iter = 0;
    vehicle = taxi;
    grid = world;
}

// Destructor
Simulation::~Simulation() {
}

int Simulation::GetMaxIter(void) {
    return max_iter;
}

int Simulation::GetCurrIter(void) {
    return curr_iter;
}

void Simulation::SetMaxIter(int iteration) {
    max_iter = iteration;
}
   
void Simulation::SetCurrIter(int iteration) {
    curr_iter = iteration;
}

void Simulation::Loop(void) {

  try {
    
    grid->PrintGrid(vehicle);
      t0 = clock();
    vehicle->Update(grid->GetWorld());
      t1 = clock();
      double time = (double(t1 - t0) / CLOCKS_PER_SEC);
      std::cout << "\nTiempo de ejecución: " << time << std::endl;
    grid->ToggleWorldValue(vehicle->GetRow(), vehicle->GetColumn());
    grid->SetWorldState('X', vehicle->GetRow(),vehicle->GetColumn());
      std::cout << "\nTamaño del resultado: " << vehicle->Solucion_.size() << std::endl;
    grid->PrintSolucion(vehicle);

  }catch (std::exception& e) {
    throw e;
  }
}

void Simulation::PrintData(void) {
  std::cout << "Vehiculo: X = " << vehicle->GetRow() << " Y = " << vehicle->GetColumn() << " Direccion: " ;
  vehicle->PrintDirection();
  std::cout << std::endl;
}
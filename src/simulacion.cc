#include "../include/simulacion.h"

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
    vehicle->Update(grid->GetWorld());
    grid->ToggleWorldValue(vehicle->GetRow(), vehicle->GetColumn());
    grid->SetWorldState('X', vehicle->GetRow(),vehicle->GetColumn());
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
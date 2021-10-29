#include "../include/vehiculo.h"
#include "../include/mundo.h"

// Constructores
Vehicle::Vehicle(){
    row_pos = 0;
    column_pos = 0;
    direction = 1;
    destination_row = 4;
    destination_col = 7;
}

Vehicle::Vehicle(int i, int j, int direction_, int row_destination, int col_destination, int Wx, int Wy){
    
    Origen = std::make_pair(i,j);
    Destino = std::make_pair(row_destination,col_destination);
    
    WorldSizeX = Wx;
    WorldSizeY = Wy;

    row_pos = i;
    column_pos = j;
    direction = direction_;
    destination_row = row_destination;
    destination_col = col_destination;
}

// Destructor
Vehicle::~Vehicle(){
}

// Getters y Setters
int Vehicle::GetRow(void) {
    return row_pos;
}

int Vehicle::GetColumn(void) {
    return column_pos;
}

int Vehicle::GetDestinationRow(void) {
    return destination_row;
}

int Vehicle::GetDestinationColumn(void) {
    return destination_col;
}

int Vehicle::GetDirection(void) {
    return direction;
}

void Vehicle::SetRow(int row) {
    row_pos = row;
}

void Vehicle::SetColumn(int column) {
    column_pos = column;
}

void Vehicle::SetDirection(int next_direction) {
    direction = next_direction;
}

void Vehicle::Update(World& coord) {
    try{
        //Turn45(coord.GetWorldValue(GetRow(), GetColumn()));
        coord.ToggleWorldValue(GetRow(), GetColumn());
        coord.SetWorldState('X', GetRow(), GetColumn());
        Move(coord); 
    }
    catch (std::exception& e){
        throw e;
    }
}

bool Vehicle::isValid(int row, int col){
    return (row >= 0) && (row < WorldSizeX) && (col >= 0) && (col < WorldSizeY);
}

bool Vehicle::isUnBlocked(Vector<Vector<Cell>>& Grid, int row, int col){

  return !Grid[row][col].GetValue();

}

bool Vehicle::isDestination(int row, int col, Posicion_t dest){
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}
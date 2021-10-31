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

Vehicle::Vehicle(int i, int j, int direction_, int row_destination,
                 int col_destination, int Wx, int Wy, funcion_heuristica* fh){
    

    f_heuristica_ = fh;
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

int Vehicle::GetExpansion(void) {
    return expansion;
}

void Vehicle::AddExpansion(void) {
    expansion += 1;
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

void Vehicle::Update(Mundo_t& coord) {
    try{
        //Turn45(coord.GetWorldValue(GetRow(), GetColumn()));
        //coord.ToggleWorldValue(GetRow(), GetColumn());
        //coord.SetWorldState('X', GetRow(), GetColumn());

        //Estas funciones ahora estan implementadas en el 
        //metodo invocador de update (simulacion.cc/loop)

        //Realmente el algoritmo se ejecuta totalmente de 
        //una vez y no se ccambian los estados de las posiciones 
        //del mundo a X, la solucion que veo es luego utilizar el 
        //Camino construido para pintarlo
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

double Vehicle::calculateHValue(int row, int col, Posicion_t dest){
    return Get_f_Heuristica()->operator()(row,col, dest.first, dest.second);
}

funcion_heuristica* Vehicle::Get_f_Heuristica(void){
  return f_heuristica_;
}
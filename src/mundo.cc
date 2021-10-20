#include "../include/mundo.h"

//Constructores

World::World(){
    row = 10;
    column = 10;
    size = 100;
    world = Vector<Vector<Cell>> (-10,10);
    for(int i = 0; i < 10; i++) {
        world[i].resize(10);
    }
}
std::vector<int> a;
World::World(int row_size, int column_size){
    row = row_size;
    column = column_size;
    size = row * column;
    world.resize(row_size);
        for(int i = 0; i < column_size; i++){
        world[i].resize(column_size);
    }
}

World::World(int row_min, int row_max, int col_min, int col_max){
    row = row_max - row_min;
    column = col_max - col_min;
    size = row * column;
    world.resize(row);
    world.SetLowerLimit(row_min);
    for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++){
        world[i].resize(column);
        world[i].SetLowerLimit(col_min);
    }
}

World::World(int row_min, int row_max, int col_min, int col_max, int obstacle_type){ // inicializa un mundo con obstáculos aleatorios
    row = row_max - row_min;
    column = col_max - col_min;
    size = row * column;
    world.resize(row);
    world.SetLowerLimit(row_min);
    int x, y;
    for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++){
        world[i].resize(column);
        world[i].SetLowerLimit(col_min);
    }

    int obstacle_percentage;
    int obstacle_quantity;

    switch(obstacle_type) {
        case 0: 
                
                std::cout << "Introduzca el porcentaje de obstáculos (valor comprendido entre 0 y 100): " << std:: endl;
                std::cin >> obstacle_percentage;
                while ((obstacle_percentage < 0) || (obstacle_percentage > 100)) {
                    std::cout << "ERROR: valor fuera del rango entre 0 y 100." << std::endl;
                    std::cout << "Introduzca el numero de obstáculos (valor comprendido entre 0 y 100): " << std:: endl;
                    std::cin >> obstacle_percentage;
                }
                obstacle_quantity = size * obstacle_percentage / 100;

                srand(time(NULL)); 
                for(int i = 0; i < obstacle_quantity; i++) {

                    int random_row = rand()%(world.GetUpperLimit() - world.GetLowerLimit()) + world.GetLowerLimit();
                    int random_col = rand()%(world[random_row].GetUpperLimit() - world[random_row].GetLowerLimit()) + world[random_row].GetLowerLimit();

                    SetWorldState('0', random_row, random_col);
                    SetWorldValue(true, random_row, random_col);
                }
        break;

        case 1:
                std::cout << "Introduzca el porcentaje de obstáculos manuales(valor comprendido entre 0 y 100): " << std:: endl;
                std::cin >> obstacle_percentage;
                while ((obstacle_percentage < 0) || (obstacle_percentage > 100)) {
                    std::cout << "ERROR: valor fuera del rango entre 0 y 100." << std::endl;
                    std::cout << "Introduzca el numero de obstáculos (valor comprendido entre 0 y 100): " << std:: endl;
                    std::cin >> obstacle_percentage;
                }
                obstacle_quantity = size * obstacle_percentage / 100;

                for(int i = 0; i < obstacle_quantity; i++) {
                    do {
                        std::cout << "Introduzca la coordenada X del obstáculo: " << i+1 << " : ";
                        std::cin >> x;
                    while ((x < 0) || (x > row_max * 2 - 1)) {
                        std::cout << "ERROR: la coordenada X no está dentro del mundo definido." << std::endl;
                        std::cout << "Introduzca una coordenada entre " << 0 << " y " << row_max * 2 - 1 << std:: endl;
                        std::cin >> x;
                    }
                    std::cout << "Introduzca la coordenada Y del obstaculo " << i+1 << " : ";
                    std::cin >> y;
                    while ((y < 0) || ( y > col_max * 2 - 1)) {
                        std::cout << "ERROR: la coordenada Y no está dentro del mundo definido." << std::endl;
                        std::cout << "Introduzca una coordenada entre " << 0 << " y " << col_max * 2 - 1 << std:: endl;
                        std::cin >> y;
                    }
                
                    } while (GetWorldValue(x, y) == true); //mientras la casilla ya esté ocupada
                x += row_min;
                y += col_min;
                SetWorldState('0', x, y);
                SetWorldValue(true, x, y);
        }
        break;

    case 2:

    try {

        //pwd = IA-Busqueda  ruta relativa a cwd
        std::string filename = "./data/coordenadas.txt";
        std::ifstream input_file; // lee el contenido del archivo
        input_file.open(filename.c_str(), std::ifstream::in);

        std::string read, num1, num2;
        unsigned move = 0;

        if (!input_file.is_open()) throw 1;
        
        while(getline(input_file, read)) {
            if (read[0] != '/' && read[1] != '/') {

            for(; move < read.size(); move++) {
                if(read[move] != ',') {
                    num1.push_back(read[move]);
                }
                else {
                    move++;
                    break;
                }
            }
            for(; move < read.size(); move++) {
                num2.push_back(read[move]);
            } 

            x = stoi(num1);
            y = stoi(num2);
            num1.clear();
            num2.clear();
            move = 0;

            if((x < 0) || (x > row_max * 2 - 1) || (y < 0) || ( y > col_max * 2 - 1)) throw 2;

            x += row_min;
            y += col_min;
            SetWorldState('0', x, y);
            SetWorldValue(true, x, y);
            }
        }          
        input_file.close();

    }catch(int& error) { // errores con la apertura del archivo
        switch (error)
        {
        case 1:
            std::cout<<"ERROR al intentar abrir el archivo (coordenadas.txt)."<<std::endl;
            break;
        
        case 2:
            std::cout<<"ERROR: los datos no están introducidos correctamente."<<std::endl;
            break;
        }
    }

    break;
    }
}



//Destructor

World::~World(){
}


// Getters y Setters

char World::GetWorldState(int i, int j) {
    return world[i][j].state;
}

bool World::GetWorldValue(int i, int j) {
    try{
       return world[i][j].value; 
    }
    
    catch(...){
        throw std::exception();
    }
}

void World::SetRow(int row_) {
    row = row_;
}

void World::SetColumn(int column_) {
    column = column_;
}

void World::SetSize(int size_) {
    size = size_;
}

void World::SetWorldState(char state_, int i, int j) {
    world[i][j].state = state_;
}

void World::SetWorldValue(bool value_, int i, int j) {
    world[i][j].value = value_;
}

void World::ToggleWorldValue(int i, int j){
    
   if(world[i][j].value == false){
        world[i][j].value = true;
   }
   else {
        world[i][j].value = false;
   }  
}


void World::SetWorld(Vector<Vector<Cell>>& new_world){

    world.resize(new_world.GetSize());
    world.SetLowerLimit(new_world.GetLowerLimit());

    for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++){
        world[i].resize(new_world[i].GetSize());
        world[i].SetLowerLimit(new_world[i].GetLowerLimit());
        for(int j = world[i].GetLowerLimit(); j < world[i].GetUpperLimit(); j++){
            world[i][j] = new_world[i][j];
        }
    }
}

void World::PrintWorld(void) {
    PrintHorizontalWall();
    for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++) {
        std::cout << "|";
        for(int j = world[i].GetLowerLimit(); j < world[i].GetUpperLimit(); j++) {
            if (GetWorldState(i,j) == '0') {
                std::cout << "\033[;36m0\033[0m";
            }else if (GetWorldState(i,j) == 'X') {
                std::cout << "\033[;33mX\033[0m";
            }else {
                std::cout <<  GetWorldState(i,j) ;
            }
        }
        std::cout << "|" << std::endl;
    }
    PrintHorizontalWall();
}

void World::PrintHorizontalWall(void) {   
    for(int i = world[0].GetLowerLimit(); i < world[0].GetUpperLimit() + 2; i++){
        std::cout << "-";
    }
    std::cout << std::endl;
}

/*void World::Update(std::vector<Vehicle>& vehicle) {
    for(int i = 0; i < vehicle.size(); i++) {
        if ((GetWorldValue(vehicle[i].GetRow(), vehicle[i].GetColumn())) == false){ // casilla blanca
            SetWorldValue(true, vehicle[i].GetRow(), vehicle[i].GetColumn());
        }
        else {
            SetWorldValue(false, vehicle[i].GetRow(), vehicle[i].GetColumn()); //casilla negra
        } 
    }
}
*/

void World::PrintGrid(Vehicle* vehicle){
    PrintHorizontalWall();
        for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++) {
            std::cout << "|";
            for(int j = world[i].GetLowerLimit(); j < world[i].GetUpperLimit(); j++) {
                if((i == vehicle->GetRow()) && (j == vehicle->GetColumn()))
                    vehicle->PrintDirection();
                else if ((i == vehicle->GetDestinationRow()) && (j == vehicle->GetDestinationColumn())){
                    std::cout << "\033[;31m\u2691\033[0m";
                }
                else if (GetWorldState(i,j) == '0') {
                    std::cout << "\033[;36m0\033[0m";
                }else if (GetWorldState(i,j) == 'X') {
                    std::cout << "\033[;33mX\033[0m";
                }else {
                    std::cout <<  GetWorldState(i,j) ;
                }
            }
            std::cout << "|" << std::endl;
        }
    PrintHorizontalWall();
}

bool World::VehicleOut(Vehicle* vehicle) {
    bool condition = false;
    if((vehicle->GetRow() >= world.GetUpperLimit()) || (vehicle->GetColumn() >= world.GetUpperLimit()) || (vehicle->GetRow() < world.GetLowerLimit()) || (vehicle->GetColumn() < world.GetLowerLimit()))
        condition = true;
    return condition;
}

void World::TryPosition(Vehicle* vehicle){
    try{
        Cell temp;
        temp = GetCell(vehicle->GetRow(), vehicle->GetColumn());
    }
    catch(std::exception()){
        std::cout << "el taxi se ha salido del mundo!!!" << std::endl;
        throw(std::exception());
    }
}
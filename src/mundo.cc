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
    //world.SetUpperLimit(col)
    int x, y;
    for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++){
        world[i].resize(column);
        //std::cout<<world.GetLowerLimit() <<std::endl;

        for (int iter = 0; iter < world.GetUpperLimit(); iter++){
          //std::cout<<world[i].GetLowerLimit() <<std::endl;
          world[i][iter].SetPos(i, iter);
        }

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
                std::cout << "Introduzca el porcentaje de obstáculos (valor comprendido entre 0 y 100): " << std:: endl;
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
  //delete f_heuristica_;
}


// Getters y Setters

char World::GetWorldState(int i, int j) {
    return world[i][j].GetState();
}

bool World::GetWorldValue(int i, int j) {
    try{
       return world[i][j].GetValue(); 
    }
    
    catch(...){
        throw std::exception();
    }
}

int World::GetWorldX(int i, int j) {
    return world[i][j].GetX();
}

int World::GetWorldY(int i, int j) {
    return world[i][j].GetY();
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
    world[i][j].SetState(state_);
}

void World::SetWorldValue(bool value_, int i, int j) {
    world[i][j].SetValue(value_);
}
void World::ToggleWorldValue(int i, int j){
    
   if(world[i][j].GetValue() == false){
        world[i][j].SetValue(true);
   }
   else {
        world[i][j].SetValue(false);
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
                std::cout << "\033[;32mX\033[0m";
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
        std::cout << "⬛";
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
            std::cout << "⬛";
            for(int j = world[i].GetLowerLimit(); j < world[i].GetUpperLimit(); j++) {
                if((i == vehicle->GetRow()) && (j == vehicle->GetColumn()))
                    //vehicle->PrintDirection();
                    std::cout << "\U0001f696"; //🚖
                else if ((i == vehicle->GetDestinationRow()) && (j == vehicle->GetDestinationColumn())){
                    //std::cout << "\033[;31m\u2691\033[0m";
                    std::cout << "\U0001f3c1"; //🏁
                }
                else if (GetWorldState(i,j) == '0') {
                    std::cout << "\033[;36m\U0001f7e5\033[0m"; //🟥
                }else if (GetWorldState(i,j) == 'X') {
                    std::cout << "\033[;32mX\033[0m";
                }else {
                    std::cout << "\033[;36m\U0001f7e9\033[0m";//GetWorldState(i,j) ; //🟩
                }
            }
            std::cout << "⬛" << std::endl;
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



////////////////////////////////////////////////////////////////////////////////

//bool World::is_in_set(Cell c, const Vector<Cell>& s){}
  /*
    for(unsigned int i = 0; i < s.GetSize(); i++)
        if((s[i].GetX()== c.GetX()) && s[i].GetY()==c.GetY())
            return true;

    return false;
}*/

//void World::reconstruir_camino(Vector<Cell> &v, Cell actual, Cell I){}

  /*
    Cell a = actual;
    v.push_back(a);
    //Introduce los nodos recorriendo los padres hasta llegar al inicio
    while(a.GetX() != I.GetX() || a.GetY() != I.GetY()){           //Mientras no llegue a la celda inicial
        //a = world[static_cast<unsigned int>(a.GetPadreX())][static_cast<unsigned int>(a.GetPadreY())];
        //static en principio no hace falta
        a = world[a.GetPadreX()][a.GetPadreY()];
        v.push_back(a);
    }
}*/



//Vector<Cell> World::Astar(unsigned int xInicio, unsigned int yInicio,
//                          unsigned int xFinal, unsigned int yFinal){}
    
/*
    int contador = 0;                                                  // aparece en el codigo, es para quitar el error
    Vector<Cell> result;                                               // Almacena el camino optimo
    Vector<Cell> setAbierto;
    Vector<Cell> setCerrado;

    Cell& Inicial = world[xInicio][yInicio];
    Cell& Final = world[xFinal][yFinal];

    Inicial.SetG(0);                                                   //Cambiamos valores heuristicos de la primera Celda
    Inicial.SetF(f_heuristica_->operator()(Inicial, Final));

    setAbierto.push_back(Inicial);                                      //Setup completada
    contador++;

    while(!setAbierto.Empty()){
        unsigned int winner = 0;
        //Seleccionar el nodo con mejor valor F
        for(unsigned int i = 0; i < setAbierto.GetSize(); i++){            //Se busca la Celda con menor f_valor
            if(setAbierto[i].GetF() < setAbierto[winner].GetF())
                winner = i;
        }

        //Celda copia a la que tenemos en la rejilla y en el set.
        Cell actual = world[setAbierto[winner].GetX()][setAbierto[winner].GetY()];

        if((actual.GetX() == xFinal) && (yFinal == actual.GetY())){     //Es la misma celda -> Hemos llegado al final con camino óptimo
            reconstruir_camino(result, actual, Inicial);
            //Construimos el camino lo devolvemos
            return result;
        }

        setAbierto.Erase(setAbierto.Begin() + winner);                  //Cambiamos actual de set
        setCerrado.push_back(actual);                                   //Metemos nodo ganador en la lista cerrada

        for(int i = 0; i < actual.sizeVecinos(); i++){                  //Miramos los vecinos de la Celda actual
            int x = actual.getVecino(i).first;
            int y = actual.getVecino(i).second;
            Cell vecino = world[x][y];                              //Valor copia de la Celda vecina

            if(is_in_set(vecino, setCerrado))
                continue;

            int tent_g = actual.getg_() + 1;

            if(!is_in_set(vecino, setAbierto)){
                setAbierto.push_back(vecino);
                contador++;
            }
            else if(tent_g >= vecino.getg_())
                continue;

            //Este camino es el mejor! Guárdalo
            world[vecino.getX()][vecino.getY()].setPadre(actual);
            world[vecino.getX()][vecino.getY()].setg_(tent_g);
            world[vecino.getX()][vecino.getY()].setf_(tent_g + (*heuristica_)(vecino, Final));
        }
    }

    return result;
}
*/

//void World::caminoMinimo(unsigned int xInicio, unsigned int yInicio,
//                         unsigned int xFinal, unsigned int yFinal){}
/*
    long t0,t1;
    //resetCamino();

    t0 = clock();
    Vector<Cell> result = Astar(xInicio, yInicio, xFinal, yFinal);
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);

    std::cout << "Tamaño resultado: " << result.GetSize() << std::endl
         << "Tiempo de ejecucion: " << time;

    for(unsigned int i = 0; i < result.GetSize(); i++){
        if(world[result[i].getX()][result[i].getY()].getValor() == 2) pasajeros++;
        for(int j = 0; j < result[i].sizeVecinos(); j++){
            if(world[result[i].getVecino(j).first][result[i].getVecino(j).second].getValor() == 3){
                pasajeros++;

            }
            if(pasajeros >= CAP_MAX_COCHE) break;
        }
        if(pasajeros >= CAP_MAX_COCHE) break;
    }

    for(unsigned int i = 0; i < result.size(); i++){
        world[result[i].getX()][result[i].getY()].setValor(3);
    }

    cout << "\n\n" << endl;

    //PrintWorld(); // o print camino
}

*/

/*

void World::CambiarHeuristica(bool opt){
    delete f_heuristica_;
    if(opt){
        //Manhattan
        f_heuristica_ = new F_Manhattan();
    }
    else{
        //Euclidea
        f_heuristica_ = new F_Euclidiana();
    }
}
*/
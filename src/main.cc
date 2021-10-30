#include "../include/simulacion.h"
#include "../include/vector.h"
#include "../include/taxi4.h"

int main( void /* int argc, char* argv[]*/ ) {
  
    int row_min, row_max, col_min, col_max, iterations, direction, vehicle_row;
    int vehicle_col, opt, vehicle_chosen, destination_row, destination_col, obstacle_chosen = -1;
    //bool automatic_obstacles;

    Introduccion: // etiqueta para "goto"
    std::cout << "**** Pulse 0 para desplegar la información del programa. ****\n";
    std::cout << "**** Pulse 1 para comenzar con la ejecución. ****\n";
    std::cout << "Introduzca 0 o 1: ";
    std::cin >> opt;
    while ((opt != 0) && (opt != 1)) {
        std::cout << "ERROR: por favor, introduzca 0 o 1: " << std::endl;
        std::cin >> opt;
    }

if (opt == 0) {
    std::cout <<"**** Bienvenido, este programa es está encargado de generar una simulación. ****\n";
    std::cout <<"  Usted será el encargado de seleccionar el modo de generación de recursos aleatorio o manual, ";
    std::cout << "de esta forma se generará un entorno donde un taxi autónomo debe ser capaz de llegar al lugar objetivo ";
    std::cout << "de la manera más eficiente posible.\n";
    goto Introduccion; // vuelve a la etiqueta Introduccion (arriba)
}
else if (opt == 1) {
    std::cout << "Introduzca el ANCHO deseado: ";
    std::cin >> row_max;
    while (row_max < 0) {
        std::cout << "ERROR: valor menor que 0." << std::endl;
        std::cout << "Introduzca el ANCHO deseado: " << std:: endl;
        std::cin >> row_max;
    }

    row_min = 0;
  

    std::cout << "Introduzca el ALTO: ";
    std::cin >> col_max;
    while (col_max < 0) {
        std::cout << "ERROR: valor menor que 0" << std::endl;
        std::cout << "Introduzca el ALTO deseado: " << std:: endl;
        std::cin >> col_max;
    }

    col_min = 0;
    //col_max = -col_min;

    std::cout << "0. ¿Generar automáticamente los obstáculos?\n";
    std::cout << "1. ¿Introducirlos de forma manual?\n";
    std::cout << "2. ¿Leer un fichero con los obstáculos correspondientes?\n";
    std::cout << "--> Introduzca la opción deseada (0, 1 o 2): ";
    std::cin >> obstacle_chosen;
    while ((obstacle_chosen != 0) && (obstacle_chosen != 1) && (obstacle_chosen != 2)) {
        std::cout << "¡Eso no era un 0, 1 o 2! ERROR. " << std::endl << "Introduzca 0 , 1 o 2: ";
        std::cin >> obstacle_chosen;
    }

    std::cout << "Introduzca el número de iteraciones (debe ser > que 0): " << std:: endl;
    std::cin >> iterations;
    while (iterations <= 0) {
        std::cout << "ERROR: valor menor que 0" << std::endl;
        std::cout << "Introduzca el número de iteraciones (debe ser > que 0): " << std:: endl;
        std::cin >> iterations;
    }
}

World* pWorld;
pWorld = new MundoAcotado(row_min, row_max, col_min, col_max, obstacle_chosen);

std::cout << std::endl;
std::cout << pWorld->GetWorldX(5,5) << std::endl;
std::cout << pWorld->GetWorldY(5,5) << std::endl;

Vehicle* pvehicle;

std::cout << "¿El taxi es de 4 o 8 direcciones?: "; // el de 8 permite moverse en diagonal
std::cin >> vehicle_chosen;
while ((vehicle_chosen != 4) && (vehicle_chosen != 8)) {
    std::cout << "Por favor, elige entre 4 y 8 (uno de los dos valores): " << std::endl;
    std::cin >> vehicle_chosen;
}

std::cout << "Introduzca la coordenada X del taxi: ";
std::cin >> vehicle_col;
while ((vehicle_col < 0) || (vehicle_col > col_max * 2 - 1)) {
    std::cout << "ERROR: la coordenada X no está dentro del mundo definido." << std::endl;
    std::cout << "Introduzca una coordenada existente entre " << 0 << " y " << col_max * 2 - 1 << std:: endl;
    std::cin >> vehicle_col;
}

vehicle_col += col_min;

std::cout << "Introduzca la coordenada Y del taxi: ";
std::cin >> vehicle_row;
while ((vehicle_row < 0) || (vehicle_row > row_max * 2 - 1)) {
    std::cout << "ERROR: la coordenada Y no está dentro del mundo definido." << std::endl;
    std::cout << "Introduzca una coordenada existente entre " << 0 << " y " << row_max * 2 - 1 << std:: endl;
    std::cin >> vehicle_row;
}

vehicle_row += row_min;

if (vehicle_chosen == 8) {
    std::cout << "Introduzca la dirección inicial del taxi (1, 2, 3, 4, 5, 6, 7, 8): " << std:: endl;
    std::cin >> direction;
    while ((direction < 1) || (direction > 8)) {
        std::cout << "ERROR: valor de dirección incorrecto." << std::endl;
        std::cout << "Introduzca la dirección inicial del taxi (1, 2, 3, 4, 5, 6, 7, 8): " << std:: endl;
        std::cin >> direction;
    }
} else {
    std::cout << "Introduzca la dirección inicial del taxi (entre estas: 1, 2, 3, 4) " << std:: endl;
    std::cin >> direction;
    while ((direction < 1) || (direction > 4)) {
        std::cout << "ERROR: valor de dirección incorrecto." << std::endl;
        std::cout << "Introduzca la dirección inicial del taxi (1, 2, 3, 4): " << std:: endl;
        std::cin >> direction;
    }
}

do {
    std::cout << "Introduzca la coordenada X de destino: ";
    std::cin >> destination_col;
    while ((destination_col < 0) || (destination_col > col_max * 2 - 1)) {
        std::cout << "ERROR: la coordenada X no está dentro del mundo previamente definido." << std::endl;
        std::cout << "Introduzca una coordenada existente entre " << 0 << " y " << col_max * 2 - 1 << std:: endl;
    std::cin >> destination_col;
    }

    destination_col += col_min;

    std::cout << "Introduzca la coordenada Y de destino: ";
    std::cin >> destination_row;
    while ((destination_row < 0) || (destination_row > row_max * 2 - 1)){
        std::cout << "ERROR: la coordenada Y no está dentro del mundo previamente definido." << std::endl;
        std::cout << "Introduzca una coordenada existente entre " << 0 << " y " << row_max * 2 - 1 << std:: endl;
        std::cin >> destination_row;
    }
    
    destination_row += row_min;
    
} while ((pWorld->GetWorldState(destination_row, destination_col)) == '0');
        // mientras la dirección de origen esté ocupada por un obstáculo se repite el proceso de instertar dirección de origen


if ((vehicle_chosen == 8) || (vehicle_chosen == 4)) {
    pvehicle = new Taxi4(vehicle_row, vehicle_col, direction, destination_row, destination_row, row_max, col_max);
}

Simulation entorno(pWorld, pvehicle, iterations);
entorno.Loop();

return 0;
}

// Leyenda:
//  blanca = false = " "
//  negra  = true  = "X"

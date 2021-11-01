#include "../include/taxi8.h"

void Taxi8::Turn45(char colour) {
    if(colour == ' '){ // si la casilla es blanca
        if((direction <= 8) && (direction > 1)) // giro a la izquierda
            direction--;
        else if(direction == 1)
            direction = 8;
        else std::cout << "ERROR, direccion = " << direction << std::endl;
    }
    else if(colour == 'X') { // si la casilla es negra
        if((direction >= 1) && (direction < 8)) // giro a la derecha
            direction++;
        else if (direction == 8)
            direction = 1;
        else std::cout << "ERROR, direccion = " << direction << std::endl;
    }
}

void Taxi8::Turn45(bool colour){
    if(colour == false){ // si la casilla es blanca 
        if((direction <= 8) && (direction > 1)) // giro a la izquierda
            direction--;
        else if(direction == 1)
            direction = 8;
        else std::cout << "ERROR, direccion = " << direction << std::endl;
    }
    else {
        if((direction >= 1) && (direction < 8)) // giro a la derecha
            direction++;
        else if (direction == 8)
            direction = 1;
        else std::cout << "ERROR, direccion = " << direction << std::endl;
    }
}

void Taxi8::PrintDirection(void){ // imprime las flechas para representar las direcciones que se toman
    int direction = GetDirection();
    switch(direction){
        case 1: std::cout << "\u2191"; // Unicode Character 'UPWARDS ARROW'
        break;

        case 2: std::cout << "\u2197"; // Unicode Character 'NORTH EAST ARROW
        break;

        case 3: std::cout << "\u2192"; // Unicode Character 'RIGHTWARDS ARROW'
        break;

        case 4: std::cout << "\u2198"; // Unicode Character 'SOUTH EAST ARROW'
        break;

        case 5: std::cout << "\u2193"; // Unicode Character 'DOWNWARDS ARROW'
        break;

        case 6: std::cout << "\u2199"; // Unicode Character 'SOUTH WEST ARROW'
        break;

        case 7: std::cout << "\u2190"; // Unicode Character 'LEFTWARDS ARROW'
        break;

        case 8: std::cout << "\u2196"; // Unicode Character 'NORTH WEST ARROW'
        break;
    }
}

void Taxi8::Move(Mundo_t& Grid) {

  //Vector<Vector<Cell>> Grid = MainGrid.GetWorld(); 
 // If the source is out of range
    if (isValid(Origen.first, Origen.second) == false) {
        std::cout << "Source is invalid\n";
        return;
    }
 
    // If the destination is out of range
    if (isValid(Destino.first, Destino.second) == false) {
        std::cout << "Destination is invalid\n";
        return;
    }
 /*
    // Either the source or the destination is blocked
    if (isUnBlocked(Grid, Origen.first, Origen.second) == false
        || isUnBlocked(Grid, Destino.first, Destino.second)
               == false) {
        std::cout << "Source or the destination is blocked\n";
        return;
    }*/
 
    // If the destination cell is the same as source cell
    if (isDestination(Origen.first, Origen.second, Destino)
        == true) {
        printf("We are already at the destination\n");//
        return;
    }
    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    bool closedList[WorldSizeX][WorldSizeY];
    memset(closedList, false, sizeof(closedList));
 
    // Declare a 2D array of structure to hold the details
    // of that cell
    Cell cellDetails[WorldSizeX][WorldSizeY];
 
    int i, j;
    for (i = 0; i < WorldSizeX; i++) {
        for (j = 0; j < WorldSizeY; j++) {
            cellDetails[i][j].SetF(FLT_MAX);
            cellDetails[i][j].SetG(FLT_MAX);
            cellDetails[i][j].SetH(FLT_MAX);
            cellDetails[i][j].SetPadreX(-1);
            cellDetails[i][j].SetPadreY(-1);
        }
    }
 
    // Initialising the parameters of the starting node
    i = Origen.first, j = Origen.second;
    cellDetails[i][j].SetF(0.0);
    cellDetails[i][j].SetG(0.0);
    cellDetails[i][j].SetH(0.0);
    cellDetails[i][j].SetPadreX(i);
    cellDetails[i][j].SetPadreY(j);
    std::set<pPair> openList;
 
    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(std::make_pair(0.0, std::make_pair(i, j)));
 
    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;
 
    while (!openList.empty()) {
        pPair p = *openList.begin();
 
        // Remove this vertex from the open list
        openList.erase(openList.begin());
 
        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;
 
        //----------- 1st Successor (North) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j, Destino) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].SetPadreX(i);
                cellDetails[i - 1][j].SetPadreY(j);
                printf("The destination cell is found\n");
                foundDest = true;
                //tracePath(cellDetails, Destino);
                //----------------------------------------------------------------------

                std::cout << "\nThe Path is ";
                int row = Destino.first;
                int col = Destino.second;
            
                std::stack<Posicion_t> Path;
            
                while (!(cellDetails[row][col].GetPadreX() == row
                        && cellDetails[row][col].GetPadreY() == col)) {
                    Path.push(std::make_pair(row, col));
                    int temp_row = cellDetails[row][col].GetPadreX();
                    int temp_col = cellDetails[row][col].GetPadreY();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                Solucion_ = Path;
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }
                std::cout << std::endl;

                //----------------------------------------------------------------------
                
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j] == false
                     && isUnBlocked(Grid, i - 1, j)
                            == true) {
                gNew = cellDetails[i][j].GetG() + 1.0;
                hNew = calculateHValue(i - 1, j, Destino);
                fNew = gNew + hNew;
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j].GetF() == FLT_MAX
                    || cellDetails[i - 1][j].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i - 1, j)));
                    AddExpansion();
                    // Update the details of this cell
                    cellDetails[i - 1][j].SetF(fNew);
                    cellDetails[i - 1][j].SetG(gNew);
                    cellDetails[i - 1][j].SetH(hNew);
                    cellDetails[i - 1][j].SetPadreX(i);
                    cellDetails[i - 1][j].SetPadreY(j);
                }
            }
        }
 
        //----------- 2nd Successor (South) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j) == true) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j, Destino) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].SetPadreX(i);
                cellDetails[i + 1][j].SetPadreY(j);
                printf("The destination cell is found\n");
                //foundDest = true;
                //tracePath(cellDetails, Destino);
                //----------------------------------------------------------------------

                int row = Destino.first;
                int col = Destino.second;
                std::stack<Posicion_t> Path;
                while (!(cellDetails[row][col].GetPadreX() == row
                        && cellDetails[row][col].GetPadreY() == col)) {
                    Path.push(std::make_pair(row, col));
                    int temp_row = cellDetails[row][col].GetPadreX();
                    int temp_col = cellDetails[row][col].GetPadreY();
                    row = temp_row;
                    col = temp_col;
                }

                Path.push(std::make_pair(row, col));
                Solucion_ = Path;
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }
                std::cout << std::endl;

                //----------------------------------------------------------------------
                
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j] == false
                     && isUnBlocked(Grid, i + 1, j)
                            == true) {
                gNew = cellDetails[i][j].GetG() + 1.0;
                hNew = calculateHValue(i + 1, j, Destino);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j].GetF() == FLT_MAX
                    || cellDetails[i + 1][j].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i + 1, j)));
                    AddExpansion();
                    // Update the details of this cell
                    cellDetails[i + 1][j].SetF(fNew);
                    cellDetails[i + 1][j].SetG(gNew);
                    cellDetails[i + 1][j].SetH(hNew);
                    cellDetails[i + 1][j].SetPadreX(i);
                    cellDetails[i + 1][j].SetPadreY(j);
                }
            }
        }
 
        //----------- 3rd Successor (East) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i, j + 1) == true) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j + 1, Destino) == true) {
                // Set the Parent of the destination cell
                cellDetails[i][j + 1].SetPadreX(i);
                cellDetails[i][j + 1].SetPadreY(j);
                printf("The destination cell is found\n");
                foundDest = true;
                //tracePath(cellDetails, Destino);
                 //----------------------------------------------------------------------

                std::cout << "\nThe Path is ";
                int row = Destino.first;
                int col = Destino.second;
            
                std::stack<Posicion_t> Path;
            
                while (!(cellDetails[row][col].GetPadreX() == row
                        && cellDetails[row][col].GetPadreY() == col)) {
                    Path.push(std::make_pair(row, col));
                    int temp_row = cellDetails[row][col].GetPadreX();
                    int temp_col = cellDetails[row][col].GetPadreY();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                Solucion_ = Path;
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }
                std::cout << std::endl;
                //----------------------------------------------------------------------
                
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j + 1] == false
                     && isUnBlocked(Grid, i, j + 1)
                            == true) {
                gNew = cellDetails[i][j].GetG()+ 1.0;
                hNew = calculateHValue(i, j + 1, Destino);
                fNew = gNew + hNew;
 
                if (cellDetails[i][j + 1].GetF() == FLT_MAX
                    || cellDetails[i][j + 1].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j + 1)));
                    AddExpansion();
                    // Update the details of this cell
                    cellDetails[i][j + 1].SetF(fNew);
                    cellDetails[i][j + 1].SetG(gNew);
                    cellDetails[i][j + 1].SetH(hNew);
                    cellDetails[i][j + 1].SetPadreX(i);
                    cellDetails[i][j + 1].SetPadreY(j);
                }
            }
        }
 
        //----------- 4th Successor (West) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i, j - 1) == true) {

            if (isDestination(i, j - 1, Destino) == true) {

                cellDetails[i][j - 1].SetPadreX(i);
                cellDetails[i][j - 1].SetPadreY(j);
                printf("The destination cell is found\n");
                foundDest = true;

                //tracePath(cellDetails, Destino);
                //----------------------------------------------------------------------

                std::cout << "\nThe Path is ";
                int row = Destino.first;
                int col = Destino.second;
            
                std::stack<Posicion_t> Path;
            
                while (!(cellDetails[row][col].GetPadreX() == row
                        && cellDetails[row][col].GetPadreY() == col)) {
                    Path.push(std::make_pair(row, col));
                    int temp_row = cellDetails[row][col].GetPadreX();
                    int temp_col = cellDetails[row][col].GetPadreY();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                Solucion_ = Path;
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }
                std::cout << std::endl;

                //----------------------------------------------------------------------
                
                return;
            }
 
            else if (closedList[i][j - 1] == false
                     && isUnBlocked(Grid, i, j - 1)
                            == true) {
                gNew = cellDetails[i][j].GetG()+ 1.0;
                hNew = calculateHValue( i, j - 1, Destino);
                fNew = gNew + hNew;

                if (cellDetails[i][j - 1].GetF() == FLT_MAX
                    || cellDetails[i][j - 1].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j - 1)));
                    AddExpansion();
                    // Update the details of this cell
                    cellDetails[i][j - 1].SetF(fNew);
                    cellDetails[i][j - 1].SetG(gNew);
                    cellDetails[i][j - 1].SetH(hNew);
                    cellDetails[i][j - 1].SetPadreX(i);
                    cellDetails[i][j - 1].SetPadreY(j);
                }
            }
        }
        //----------- 5th Successor (North - West) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j - 1) == true) {

            if (isDestination(i - 1, j - 1, Destino) == true) {

                cellDetails[i - 1][j - 1].SetPadreX(i);
                cellDetails[i - 1][j - 1].SetPadreY(j);
                printf("The destination cell is found\n");
                foundDest = true;

                //tracePath(cellDetails, Destino);
                //----------------------------------------------------------------------

                std::cout << "\nThe Path is ";
                int row = Destino.first;
                int col = Destino.second;
            
                std::stack<Posicion_t> Path;
            
                while (!(cellDetails[row][col].GetPadreX() == row
                        && cellDetails[row][col].GetPadreY() == col)) {
                    Path.push(std::make_pair(row, col));
                    int temp_row = cellDetails[row][col].GetPadreX();
                    int temp_col = cellDetails[row][col].GetPadreY();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                Solucion_ = Path;
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }
                std::cout << std::endl;

                //----------------------------------------------------------------------
                
                return;
            }
 
            else if (closedList[i - 1][j - 1] == false
                     && isUnBlocked(Grid, i - 1, j - 1)
                            == true) {
                gNew = cellDetails[i][j].GetG()+ 1.0;
                hNew = calculateHValue( i - 1, j - 1, Destino);
                fNew = gNew + hNew;

                if (cellDetails[i - 1][j - 1].GetF() == FLT_MAX
                    || cellDetails[i - 1][j - 1].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i - 1, j - 1)));
                    AddExpansion();
                    // Update the details of this cell
                    cellDetails[i - 1][j - 1].SetF(fNew);
                    cellDetails[i - 1][j - 1].SetG(gNew);
                    cellDetails[i - 1][j - 1].SetH(hNew);
                    cellDetails[i - 1][j - 1].SetPadreX(i);
                    cellDetails[i - 1][j - 1].SetPadreY(j);
                }
            }
        }
        //----------- 6th Successor (West) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j + 1) == true) {

            if (isDestination(i + 1, j + 1, Destino) == true) {

                cellDetails[i + 1][j + 1].SetPadreX(i);
                cellDetails[i + 1][j + 1].SetPadreY(j);
                printf("The destination cell is found\n");
                foundDest = true;

                //tracePath(cellDetails, Destino);
                //----------------------------------------------------------------------

                std::cout << "\nThe Path is ";
                int row = Destino.first;
                int col = Destino.second;
            
                std::stack<Posicion_t> Path;
            
                while (!(cellDetails[row][col].GetPadreX() == row
                        && cellDetails[row][col].GetPadreY() == col)) {
                    Path.push(std::make_pair(row, col));
                    int temp_row = cellDetails[row][col].GetPadreX();
                    int temp_col = cellDetails[row][col].GetPadreY();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                Solucion_ = Path;
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }
                std::cout << std::endl;

                //----------------------------------------------------------------------
                
                return;
            }
 
            else if (closedList[i + 1][j + 1] == false
                     && isUnBlocked(Grid, i + 1, j + 1)
                            == true) {
                gNew = cellDetails[i][j].GetG()+ 1.0;
                hNew = calculateHValue( i + 1, j + 1, Destino);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j + 1].GetF() == FLT_MAX
                    || cellDetails[i + 1][j + 1].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i + 1, j + 1)));
                    AddExpansion();
                    // Update the details of this cell
                    cellDetails[i + 1][j + 1].SetF(fNew);
                    cellDetails[i + 1][j + 1].SetG(gNew);
                    cellDetails[i + 1][j + 1].SetH(hNew);
                    cellDetails[i + 1][j + 1].SetPadreX(i);
                    cellDetails[i + 1][j + 1].SetPadreY(j);
                }
            }
        }
        //----------- 7th Successor (West) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j - 1) == true) {

            if (isDestination(i + 1, j - 1, Destino) == true) {

                cellDetails[i + 1][j - 1].SetPadreX(i);
                cellDetails[i + 1][j - 1].SetPadreY(j);
                printf("The destination cell is found\n");
                foundDest = true;

                //tracePath(cellDetails, Destino);
                //----------------------------------------------------------------------

                std::cout << "\nThe Path is ";
                int row = Destino.first;
                int col = Destino.second;
            
                std::stack<Posicion_t> Path;
            
                while (!(cellDetails[row][col].GetPadreX() == row
                        && cellDetails[row][col].GetPadreY() == col)) {
                    Path.push(std::make_pair(row, col));
                    int temp_row = cellDetails[row][col].GetPadreX();
                    int temp_col = cellDetails[row][col].GetPadreY();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                Solucion_ = Path;
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }
                std::cout << std::endl;

                //----------------------------------------------------------------------
                
                return;
            }
 
            else if (closedList[i + 1][j - 1] == false
                     && isUnBlocked(Grid, i + 1, j - 1)
                            == true) {
                gNew = cellDetails[i][j].GetG()+ 1.0;
                hNew = calculateHValue( i + 1, j - 1, Destino);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j - 1].GetF() == FLT_MAX
                    || cellDetails[i + 1][j - 1].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i + 1, j - 1)));
                    AddExpansion();
                    // Update the details of this cell
                    cellDetails[i + 1][j - 1].SetF(fNew);
                    cellDetails[i + 1][j - 1].SetG(gNew);
                    cellDetails[i + 1][j - 1].SetH(hNew);
                    cellDetails[i + 1][j - 1].SetPadreX(i);
                    cellDetails[i + 1][j - 1].SetPadreY(j);
                }
            }
        }

        //----------- 8th Successor (West) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j + 1) == true) {

            if (isDestination(i - 1, j + 1, Destino) == true) {

                cellDetails[i - 1][j + 1].SetPadreX(i);
                cellDetails[i - 1][j + 1].SetPadreY(j);
                printf("The destination cell is found\n");
                foundDest = true;

                //tracePath(cellDetails, Destino);
                //----------------------------------------------------------------------

                std::cout << "\nThe Path is ";
                int row = Destino.first;
                int col = Destino.second;
            
                std::stack<Posicion_t> Path;
            
                while (!(cellDetails[row][col].GetPadreX() == row
                        && cellDetails[row][col].GetPadreY() == col)) {
                    Path.push(std::make_pair(row, col));
                    int temp_row = cellDetails[row][col].GetPadreX();
                    int temp_col = cellDetails[row][col].GetPadreY();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                Solucion_ = Path;
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }
                std::cout << std::endl;

                //----------------------------------------------------------------------
                
                return;
            }
 
            else if (closedList[i - 1][j + 1] == false
                     && isUnBlocked(Grid, i - 1, j + 1)
                            == true) {
                gNew = cellDetails[i][j].GetG()+ 1.0;
                hNew = calculateHValue( i - 1, j + 1, Destino);
                fNew = gNew + hNew;

                if (cellDetails[i - 1][j + 1].GetF() == FLT_MAX
                    || cellDetails[i - 1][j + 1].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i - 1, j + 1)));
                    AddExpansion();
                    // Update the details of this cell
                    cellDetails[i - 1][j + 1].SetF(fNew);
                    cellDetails[i - 1][j + 1].SetG(gNew);
                    cellDetails[i - 1][j + 1].SetH(hNew);
                    cellDetails[i - 1][j + 1].SetPadreX(i);
                    cellDetails[i - 1][j + 1].SetPadreY(j);
                }
            }
        }


    }//While
    if (foundDest == false)
        std::cout << "No se pudo encontrar el camino" << std::endl;
}
#pragma once

#include "vehiculo.h"

class Taxi4: public Vehicle
{

using Vehicle::Vehicle;

virtual void Turn45(char colour);

virtual void Turn45(bool colour);

double calculateHValue(World& Grid, int row, int col, Posicion_t dest);


//Implementa el algoritmo A* 
virtual void Move(World& MainGrid) {

  Vector<Vector<Cell>> Grid = MainGrid.GetWorld(); 

 // If the source is out of range
    if (isValid(Origen.first, Origen.second) == false) {
        printf("Source is invalid\n");
        return;
    }
 
    // If the destination is out of range
    if (isValid(Destino.first, Destino.second) == false) {
        printf("Destination is invalid\n");
        return;
    }
 
    // Either the source or the destination is blocked
    if (isUnBlocked(Grid, Origen.first, Origen.second) == false
        || isUnBlocked(Grid, Destino.first, Destino.second)
               == false) {
        printf("Source or the destination is blocked\n");
        return;
    }
 
    // If the destination cell is the same as source cell
    if (isDestination(Origen.first, Origen.second, Destino)
        == true) {
        printf("We are already at the destination\n");
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
 
    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair of
     pair.*/
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
 
        /*
         Generating all the 8 successor of this cell
 
             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E
 
         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)*/
 
        // To store the 'g', 'h' and 'f' of the 8 successors
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
                    int temp_col = cellDetails[row][col].GetPadreX();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }

                //----------------------------------------------------------------------
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j] == false
                     && isUnBlocked(Grid, i - 1, j)
                            == true) {
                gNew = cellDetails[i][j].GetG() + 1.0;
                hNew = calculateHValue(MainGrid, i - 1, j, Destino);
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
                cellDetails[i + 1][j].SetPadreX(j);
                printf("The destination cell is found\n");
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
                    int temp_col = cellDetails[row][col].GetPadreX();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }

                //----------------------------------------------------------------------
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j] == false
                     && isUnBlocked(Grid, i + 1, j)
                            == true) {
                gNew = cellDetails[i][j].GetG() + 1.0;
                hNew = calculateHValue(MainGrid, i + 1, j, Destino);
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
                    int temp_col = cellDetails[row][col].GetPadreX();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }

                //----------------------------------------------------------------------
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j + 1] == false
                     && isUnBlocked(Grid, i, j + 1)
                            == true) {
                gNew = cellDetails[i][j].GetG()+ 1.0;
                hNew = calculateHValue(MainGrid, i, j + 1, Destino);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j + 1].GetF() == FLT_MAX
                    || cellDetails[i][j + 1].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j + 1)));
 
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
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j - 1, Destino) == true) {
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].SetPadreX(i);
                cellDetails[i][j - 1].SetPadreY(j);
                printf("The destination cell is found\n");
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
                    int temp_col = cellDetails[row][col].GetPadreX();
                    row = temp_row;
                    col = temp_col;
                }
            
                Path.push(std::make_pair(row, col));
                while (!Path.empty()) {
                std::pair<int, int> p = Path.top();
                Path.pop();
                //printf("-> (%d,%d) ", p.first, p.second);
                std::cout << "-> (" << p.first << "," << p.second << ") ";
                }

                //----------------------------------------------------------------------
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j - 1] == false
                     && isUnBlocked(Grid, i, j - 1)
                            == true) {
                gNew = cellDetails[i][j].GetG()+ 1.0;
                hNew = calculateHValue(MainGrid, i, j - 1, Destino);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j - 1].GetF() == FLT_MAX
                    || cellDetails[i][j - 1].GetF() > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j - 1)));
 
                    // Update the details of this cell
                    cellDetails[i][j - 1].SetF(fNew);
                    cellDetails[i][j - 1].SetG(gNew);
                    cellDetails[i][j - 1].SetH(hNew);
                    cellDetails[i][j - 1].SetPadreX(i);
                    cellDetails[i][j - 1].SetPadreY(j);
                }
            }
        }



    }//While
}
/*
void Vehicle::tracePath(Cell& cellDetails[WorldSizeX][WorldSizeY], Posicion_t Destino){
    std::cout << "\nThe Path is ";
    int row = Destino.first;
    int col = Destino.second;
 
    std::stack<Posicion_t> Path;
 
    while (!(cellDetails[row][col].GetPadreX() == row
             && cellDetails[row][col].GetPadreY() == col)) {
        Path.push(std::make_pair(row, col));
        int temp_row = cellDetails[row][col].GetPadreX();
        int temp_col = cellDetails[row][col].GetPadreX();
        row = temp_row;
        col = temp_col;
    }
 
    Path.push(std::make_pair(row, col));
    while (!Path.empty()) {
        std::pair<int, int> p = Path.top();
        Path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
    }
 
    return;
}
*/








/**
 
 
 virtual void Move(void) {
    if(direction == 1)
        row_pos += -1;
    else if(direction == 2) {
        column_pos += 1;
    }
    else if (direction == 3)
        row_pos += 1;
    else if(direction == 4) {
        column_pos += -1;
    }
    else std::cout << "ERROR, direction = " << direction << std::endl;
}
};
 
 */


virtual void PrintDirection(void);

};


// REALIZA EL MOVIMIENTO SIN INFORMACION
/*virtual void Move(void) { // se mueve en el entorno (coordenadas)
    
    if(direction == 1)
        row_pos += -1;
    else if(direction == 2) {
        row_pos += -1;
        column_pos += 1;
    }
    else if (direction == 3)
        column_pos += 1;
    else if(direction == 4) {
        row_pos += 1;
        column_pos += 1;
    }
    else if(direction == 5)
        row_pos += 1;
    else if(direction == 6) {
        row_pos += 1;
        column_pos += -1;
    }
    else if(direction == 7)
        column_pos += -1;
    else if(direction == 8) {
        row_pos += -1;
        column_pos += -1;
    }
    else std::cout << "ERROR, direccion = " << direction << std::endl;

}
*/
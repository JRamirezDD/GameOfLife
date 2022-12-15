#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Game Of Life Rules:
    // Any alive cell with less than two alive neighbours dies.
    // Any alive cell with two or three alive neighbours lives.
    // Any alive cell with more than three alive neighbours dies.
    // Any alive dead cell with 3 alive neighbors lives.



// Problem Decomposition
    // Required Data Structures:   
        // List Element
            // 2 Accepted Data Types:
                // 1. Linked-List (aka. Column)
                // 2. Cell        (aka. Row)
        // Linked Lists
        

    // IMPLEMENTATION
        // A Cell (Struct C)
            // Attributes: 
                // Alive Neighbor Count (Int)
                // Alive Status (Bool)
            // Methods
                // Create Cell with default attributes
                // Set Alive Neighbor Count
                // Set Alive Status
                // Update Alive Status
                    // Check Rules Conditions
                    // Update Accordingly   

        // A Row (Struct B)
            // Attributes:
                // 'x' Cells
                    // Linked List of 'x' data type: Cell
            // Methods:
                // Create Row with 'n' cells
                // Get Cell at pos 'x'

        // A Grid (Struct A) of 'x' width and 'y' height is created
            // Attributes:
                // 'y' Rows, each containing 'x' Cells. 
                    // Linked List of 'y' data type: Linked List
                    // Linked List of 'x' data type: Cell
            // Methods:
                // Create Grid with 'n' rows
                // Get Row at pos 'y'
                    // * (1 iteration each)
                // Update Alive Neighbor Count (Of Each Cell)
                // Update Alive Status

        // Special Cases:
            // Cells found on the edges



// Structures and Methods



typedef struct S_Cell Cell;

typedef struct S_Row Row;

typedef struct S_Grid Grid;





struct S_Cell
{
    int alive_status;   // Used as Boolean
    int alive_neighbors;
    Cell* next;
};
Cell* createCell() ;                                        // Write
Cell* getCell(Grid* grid, int y, int x) ;                   // Read
int getAlive_Status(Cell* cell) ;                           // Read
void setAlive_Status(Cell* cell, int alive_status) ;        // Write
int getNeighbor_Count(Cell* cell) ;                         // Read
void setAlive_Neighbors(Cell* cell, int neighbor_count) ;   // Write
int countNeighbors(Grid* grid, int pos_y, int pos_x) ;      // Read
int updateAlive_Status(Cell* cell) ;                        // Read & Write



struct S_Row
{
    int size;   // Number of Cells per Row, or width
    Cell* head;
    Row* next;
};
Row* createRow() ;                                          // Write
Cell* getColumn(Row* row, int pos) ;                        // Read



struct S_Grid
{
    int height;  // Number of Rows per Grid, or height
    int width;   // Number of Cells per Row, or width
    Row* head;
};
Grid* createGrid(int height, int width) ;                   // Write
void randomizeGrid(Grid* grid, int n) ;                     // Read & Write
void updateAll_Alive_Status(Grid* Grid) ;                   // Read & Write
void updateAll_Neighbors(Grid* grid) ;                      // Read & Write
void printGrid(Grid* grid) ;                                // Read
void simulateGrid(Grid* grid, int generations, int delay) ; // Read & Write
Row* getRow(Grid* grid, int pos) ;                          // Read





/*
Visualization of the Data Structures:

3x3 Grid
                 Column 0    Column 1    Column 2
Grid -> Row 0 -> Cell 0,0 -> Cell 0,1 -> Cell 0,2
     -> Row 1 -> Cell 1,0 -> Cell 1,1 -> Cell 1,2
     -> Row 2 -> Cell 2,0 -> Cell 2,1 -> Cell 2,2

*/


// Pre-Programmed Demonstrations:
void runTest() ;
void runDefault() ;
void runUserInputted() ;


int main(void)
{
    
    int x = 0;
    
    while (x < 1 || x > 3)
    {
        printf("Desired Demonstration (1, 2, or 3): ");
        scanf("%d", &x);
    }
    

    // Selection of Demonstration:
    switch (x)
    {
    
        case 1:
            runTest();
            break;
    
        case 2:
            runDefault();
            break;

        case 3:
            runUserInputted();
            break;

        default:
            break;
    }


    scanf("%d", &x);    // Used to maintain the cmd window open when program is done running

    return 0;
}






/* Cell */

Cell* createCell()
{
    Cell* newCell = malloc(sizeof(Cell));
    newCell->alive_status = 0;
    newCell->alive_neighbors = 0;
    newCell->next = NULL;
    return newCell;
}   /* Creates Cell structure with the desired properties */

Cell* getCell(Grid* grid, int y, int x)
{
    Row* row = getRow(grid, y);
    Cell* cell = getColumn(row, x); 

    return cell;
}   /* Combines getRow and getColumn into a single function */

int getAlive_Status(Cell* cell)
{
    if (cell != NULL) return cell->alive_status;

}   /* Extracts the 'alive_status' of cell */

int getNeighbor_Count(Cell* cell)
{
    if (cell != NULL) return cell->alive_neighbors;
    
}   /* Extracts 'neighbor_count' of cell */

void setAlive_Status(Cell* cell, int alive_status) 
{
    if (cell != NULL) cell->alive_status = alive_status;

    return;
}   /* Sets 'alive_status' of cell to 'n' */

void setAlive_Neighbors(Cell* cell, int neighbor_count)
{
    if (cell != NULL) cell->alive_neighbors = neighbor_count;

    return;
}   /* Sets 'neighbor_count' of cell to 'n' */

int countNeighbors(Grid* grid, int pos_y, int pos_x)
{
    int alive_count = 0;
    Cell* curr_cell = getCell(grid, pos_y, pos_x);

    /* Conditionals used for handling cells on the edges */
    // Left
    if (pos_x - 1 >= 0)
    {
        if (getAlive_Status(getCell(grid, pos_y, pos_x - 1)) == 1) alive_count++;
    }

    // Right
    if (pos_x + 1 < grid->width)
    {
        if (getAlive_Status(getCell(grid, pos_y, pos_x + 1)) == 1) alive_count++;
    }


    // Above
    if (pos_y + 1 < grid->height)
    {
        if (getAlive_Status(getCell(grid, pos_y + 1, pos_x)) == 1) alive_count++;

        // Above Left
        if (pos_x - 1 >= 0)
        {
            if (getAlive_Status(getCell(grid, pos_y + 1, pos_x - 1)) == 1) alive_count++;
        }

        // Above Right
        if (pos_x + 1 < grid->width)
        {
            if (getAlive_Status(getCell(grid, pos_y + 1, pos_x + 1)) == 1) alive_count++;
        }
    }

    // Under
    if (pos_y - 1 >= 0)
    {
        if (getAlive_Status(getCell(grid, pos_y - 1, pos_x)) == 1) alive_count++;

        // Above Left
        if (pos_x - 1 >= 0)
        {
            if (getAlive_Status(getCell(grid, pos_y - 1, pos_x - 1)) == 1) alive_count++;
        }

        // Above Right
        if (pos_x + 1 < grid->width)
        {
            if (getAlive_Status(getCell(grid, pos_y - 1, pos_x + 1)) == 1) alive_count++;
        }
    }


    return alive_count;

} /* Accesses neighboring cells and counts the live ones */

int updateAlive_Status(Cell* cell)
{
    int alive_status = getAlive_Status(cell);
    int neighbor_count = getNeighbor_Count(cell);

    // Any alive cell
    if (alive_status == 1)
    {
        // With less than two alive neighbours dies
        if (neighbor_count < 2)
        {
            alive_status = 0;
        }

        // With two or three alive neighbours lives
        else if (neighbor_count == 2 || neighbor_count == 3)
        {
            alive_status = 1;
        }

        // With more than three alive neighbours dies
        else if (neighbor_count > 3)
        {
            alive_status = 0;
        }
    }

    // Any dead cell
    else if (alive_status == 0)
    {
        // With 3 alive neighbors lives
        if (neighbor_count == 3)
        {
            alive_status = 1;
        }
    }

    setAlive_Status(cell, alive_status);

    return alive_status;
} /* Assign alive status based on cell's neighbor_count */


/* /Cell */


/* CellList */
Cell* getColumn(Row* row, int pos)
{
    if (row == NULL)
    { 
        return NULL;
    }

    if (pos >= row->size) // Out of Bounds ()
    {
        return NULL;
    }

    Cell* current = row->head;      // First Cell
    for (int i = 0; i < pos; i++)   // Rest of the Cells
    {
        current = current->next;
    }

    return current;
} /* Obtains the Cell on 'x' position */


/* Row */

Row* createRow(int width) 
{
    Row* newRow = malloc(sizeof(Row));
    Cell* current = createCell(); // First Cell
    newRow->head = current;
    newRow->size = width;

    Cell* next;
    for (int i = 0; i < width - 1; i++) // Rest of the Cells
    {   
        next = createCell();

        current->next = next;
        current = next;
    }

    newRow->next = NULL;
    return newRow;
} /* Creates a row structure containing a Column */

Row* getRow(Grid* grid, int pos)
{
    if (grid == NULL)
    {
        return NULL;
    }

    if (pos >= grid->height) // Out of Bounds 
    {
        return NULL;
    }

    Row* current = grid->head;   // First Row
    for (int i = 0; i < pos; i++)   // Rest of the Rows
    {
        current = current->next;
    }

    return current;
} /* Obtains the Row on 'y' position */

/* /Row */


/* Grid */

Grid* createGrid(int height, int width) 
{
    Grid* newGrid = malloc(sizeof(Grid));
    Row* current = createRow(width); // First Row
    Row* next;
    
    newGrid->height = height;
    newGrid->width = width;
    newGrid->head = current;


    for (int i = 0; i < height - 1; i++) // Rest of the Rows
    {   
        next = createRow(width);

        current->next = next;
        current = next;
    }

    return newGrid;
} /* Creates a new Grid structure that contains 'x' rows */

void randomizeGrid(Grid* grid, int n) // Number of iterations   
{
    // Select a random column from 0 to grid->height
    // Select a random cell from 0 to grid->width

    // 'n' represents number of desired alive cells

    int x = 0;
    int y = 0;
    Cell* cell;

    int max_x = grid->width - 1;
    int max_y = grid->height - 1;


    srand(time(NULL)); // Sets a randomized seed based on the computer's clock. 

    for (int i = 0; i < n; i++)
    {
        while (1) // Used to ensure that the same cell isn't set to alive twice
        {

            x = rand()%max_x; // Returns a random integer from 0 to the desired maximum 'max_x' using the previously generated seed. 
            y = rand()%max_y; // Returns a random integer from 0 to the desired maximum 'max_y' using the previously generated seed. 

            cell = getCell(grid, x, y);

            if (getAlive_Status(cell) == 0) // Cell is dead
            {
                setAlive_Status(cell, 1);
                break;
            }

            else if (getAlive_Status(cell) == 1) // Cell is already set as alive
            {
                continue;
            }
        }
    }

    return;

} /* Sets the alive_status of random cells to 1 */

void updateAll_Neighbors(Grid* grid)
{

    Row* current_row = grid->head; // First Row
    int pos_y = 0;  // Row position
    

    while (current_row) // Until the last Row
    {
        int pos_x = 0;  // Cell (*Column*) position
        Cell* current_cell = current_row->head;  // First Cell (*Column*)
        while (current_cell) // Until the last Cell (*Column*)
        {
            int neighbor_count = 0;

            neighbor_count = countNeighbors(grid, pos_y, pos_x);
            
            setAlive_Neighbors(current_cell, neighbor_count);            

            current_cell = current_cell->next;
            pos_x++;
        }
        
        current_row = current_row->next;
        pos_y++;
    }

    return;
} /* Update neighbor_count of all the cells */

void updateAll_Alive_Status(Grid* grid)
{
    Row* current_row = grid->head; // First Row

    while (current_row) // Until the last Row
    {
        Cell* current_cell = current_row->head;  // First Cell (*Column*)
        while (current_cell) // Until the last (*Column*)
        {
            updateAlive_Status(current_cell);

            current_cell = current_cell->next;
        }

        current_row = current_row->next;
    }

    return;
} /* Update alive_status of each cell */

void printGrid(Grid* grid)
{
    for (int i = 0; i < 100; i++)
    {
        printf("\n");
    }
    

    Row* current_row = grid->head;
    while (current_row) // Until the last Row
    {
        Cell* current_cell = current_row->head;
        while (current_cell) // Until the last Cell (*Column*)
        {
            if (getAlive_Status(current_cell) == 0)
            {
                printf(" - ");
            }


            else if (getAlive_Status(current_cell) == 1)
            {
                printf(" ■ "); // X
            }

            current_cell = current_cell->next;
        }

        printf("\n");
        current_row = current_row->next;
    }
    
    return;
} /* Prints the grid on the desired format */

void simulateGrid(Grid* grid, int generations, int ms)
{
    printGrid(grid);
    // Iterates for x generations
    for (int n = 0; n < generations; n++)
    {
        usleep(ms * 1000);   // Pauses the simulation for x miliseconds.
        updateAll_Neighbors(grid);
        updateAll_Alive_Status(grid);
        
        printGrid(grid);
    }

} /* Updates neighbor_count and alive_status for each cell for n cycles */


/* /Grid */




/* Concept Demonstration */
void runTest()
{

    Grid* testgrid = createGrid(5, 5);
    Cell* cell = getCell(testgrid, 1, 1);
    setAlive_Status(cell, 1);
    printGrid(testgrid);

}


void runDefault()
{
    int delay = 1000;
    int size = 40;
    Grid* grid = createGrid(size, size);
    int generations = 100;
    Cell* cell = NULL;
    



    // Prediscovered Patterns
    cell =  getCell(grid, 1, 2);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 2, 2);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 3, 2);
    setAlive_Status(cell, 1);


    cell =  getCell(grid, 5, 9);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 6, 9);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 5, 10);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 5, 8);
    setAlive_Status(cell, 1);


    cell =  getCell(grid, 11, 27);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 12, 27);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 11, 28);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 11, 26);
    setAlive_Status(cell, 1);



    cell =  getCell(grid, 25, 2);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 25, 3);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 26, 2);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 26, 3);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 25, 12);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 26, 12);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 27, 12);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 24, 13);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 28, 13);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 23, 14);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 29, 14);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 23, 15);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 29, 15);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 26, 16);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 24, 17);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 28, 17);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 25, 18);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 26, 18);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 27, 18);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 26, 19);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 23, 22);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 24, 22);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 25, 22);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 23, 23);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 24, 23);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 25, 23);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 22, 24);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 26, 24);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 21, 26);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 22, 26);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 26, 26);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 27, 26);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 23, 36);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 24, 36);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 23, 37);
    setAlive_Status(cell, 1);
    cell =  getCell(grid, 24, 37);
    setAlive_Status(cell, 1);




    simulateGrid(grid, generations, delay);

    return;
}


void runUserInputted()
{

    Grid* grid = NULL;
    int size = 0;
    int generations = 0;
    int live_cells = 0;
    int delay = 1000;
    
    // Size of the grid input
    while (1)
    {   
        printf("\nEnter the Size of the grid: "); 
        scanf("%d", &size);

        if (size < 2 || size > 50)
        {
            printf("\nInvalid Size. Permitted Range is {2, ..., 50}");   
        }

        else
        {
            // Number of generations input
            while (1)
            {
                printf("\nEnter the number of Generations: ");
                scanf("%d", &generations);

                if (generations <= 0)
                {
                    printf("\nInvalid number of Generations. Enter a value above 0.");
                }

                else
                {
                    while (1)
                    {
                        printf("\nEnter the starting number of live cells: ");
                        scanf("%d", &live_cells);

                        if (live_cells <= 0)
                        {
                            printf("\nInvalid number of live cells. Enter a value above 0.");
                        }

                        else
                        {
                            break;
                        }
                    }

                    break;
                }
            }
            
            break;
        }
    }
    

    grid = createGrid(size, size);
    randomizeGrid(grid, live_cells);
    printGrid(grid);

    simulateGrid(grid, generations, delay);

    return;
}


/* /Concept Demonstration */





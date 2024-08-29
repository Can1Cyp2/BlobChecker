/* This program was made by Sebastian Landry on May 3rd 2020 */
#include <iostream>
using namespace std;
#include <vector>   // needed to use vector class
typedef vector <char> oneRow;
typedef vector <oneRow> matrix;
#include <stdlib.h> //needed for rand function


void FillMatrix(matrix &grid, int row, int col){
    /* Fills the matrix with an * or a space */

    int randnum; //a random number (either one or two)

    for(int x=0; x < row; x++){
        for(int y=0; y < col; y++){

            randnum = rand()%2;
            if(randnum == 1)
                grid[x][y]='*';
            else
                grid[x][y]=' ';
        }
    }
    return;
}


void DisplayMatrix(matrix grid){
    /* Displays the matrix */
    for(int x=grid.size()-1; x >= 0; x--){
        cout << x << " "; //Displaying the row numbers
        for(int y=0; y < grid[0].size(); y++){
            cout << grid[x][y] << " ";  //Displaying the contents of the matrix
        }
        cout << endl;
    }
    cout << "  ";
    for(int i=0; i < grid[0].size(); i++) //Displaying the column numbers
        cout << i << " ";
    return;
}

int blob_check(matrix &grid, int x, int y){
    /* Checks for the size of a blob*/
    int total; //The size of the blob
    if((x >= grid.size()) || (x < 0) || (y >= grid[0].size()) || (y < 0))//Checking to see if the users entry is on the grid
        total = 0;
    else{
        if(grid[x][y] != '*')
            total = 0;
        else{
            grid[x][y]= ' ';
            total = 1 + blob_check(grid, x-1, y)
            + blob_check(grid, x-1, y+1)
            + blob_check(grid, x, y+1)
            + blob_check(grid, x+1, y+1)
            + blob_check(grid, x+1, y)
            + blob_check(grid, x+1, y-1)
            + blob_check(grid, x, y-1)
            + blob_check(grid, x-1, y-1);
        }
   }
    return(total);
}


int main(){
    int row, col; //The rows and columns for the grid

    cout << "Please enter the number of rows for your grid: ";
    cin >> row;
    cout << "Please enter the number of columns for your grid: ";
    cin >> col;

    matrix grid(row,oneRow(col));     //Making the matrix
    FillMatrix(grid, row, col); //Filling the matrix

    matrix old_grid = grid; //A copy of the original grid
    bool again = true; //Whether the user would like to check another point on the grid or not
    while(again){
        cout << endl;
        DisplayMatrix(grid); //Displaying the matrix

        int x, y; //The users input for a row (x) and a column (y)
        cout << endl << "Please enter a row to check: ";
        cin >> x;
        cout << "Please enter a column to check: ";
        cin >> y;
        cout << endl;

        cout << "At (" << x << ", " << y << ") the blob size is " << blob_check(grid, x, y);

        char answer; //User input based on if they would like to continue checking the grid or not
        cout << endl << "Check another? (y/n): ";
        cin >> answer;

        if(answer == 'y'){  //if y the code will loop
            again = true;
            grid = old_grid;    //changing the edited grid back to the original
        }
        else
            again = false;
    }

    return(0);
}

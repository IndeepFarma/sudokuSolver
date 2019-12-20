#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Declaring function prototypes
bool isEmpty(int *row, int *col, int grid[9][9]);
bool isNotValidBox(int grid[9][9], int startRow, int startCol, int num);
bool isValid(int grid[9][9], int row, int col, int num);
bool solveGrid(int grid[9][9]);
void genGrid(int grid[9][9]);

//This function solves the puzzle
bool solveGrid(int grid[9][9])
{
  //Declaring functions
  int num = 1;
  int row = 0;
  int col = 0;

  //Checks if empty places
  if(!isEmpty(&row, &col, grid))
  {
    return 1;
  }

  //Recursively solve the grid
  for(num = 1; num < 10; num++)
  {
    if(isValid(grid, row, col, num))
    {
      grid[row][col] = num;

      if(solveGrid(grid))
      {
        return true;
      }

      grid[row][col] = 0;
    }
  }

  return false;
}

//This function checks whether or not the space on the grid is empty
bool isEmpty(int *row, int *col, int grid[9][9])
{
   for(*row = 0; *row < 9; (*row)++)
    {
      for(*col = 0; *col < 9; (*col)++)
      {
        if(grid[*row][*col] == 0)
        {
          return true;
        }
      }
    }
    return false;
}

//This function checks if the number to insert is a valid insertion
bool isValid(int grid[9][9], int row, int col, int num)
{
  //Declaring variables
  int i = 0;

  //Checks that no other col in row has the same number
  for(i = 0; i < 9; i++)
  {
    if(grid[row][i] == num)
    {
      return false;
    }
  }

  //Checks that no other row in col has the same number
  for(i = 0; i < 9; i++)
  {
    if(grid[i][col] == num)
    {
      return false;
    }
  }

  //Checks that no 3x3 box has same number
  if(isNotValidBox(grid, row - (row % 3), col - (col % 3), num))
  {
    return false;
  }

  return true;

}

bool isNotValidBox(int grid[9][9], int startRow, int startCol, int num)
{
  //Declaring variables
  int i = 0;
  int j = 0;

  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      //Checks through the 3x3 box to see if theres the same number
      if(grid[i + startRow][j + startCol] == num)
      {
        return true;
      }
    }
  }

  return false;
}

//This function generates the grid display
void genGrid(int grid[9][9])
{
  //Declaring function variables
  int i = 0;
  int j = 0;
  int lines = 0;

  //Display grid
  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      //Add divisors
      if(j == 3 || j == 6)
      {
        printf("|");
      }

      //Print numbers
      printf("%d ", grid[i][j]);
    }
    
    //Add divisors for rows
    if(i == 2 || i == 5 )
    {
      printf("\n");
      for(lines = 0; lines <= (9 * 2); lines++)
      {
        printf("-");
      }
    }

    printf("\n");
  }
}

int main(){
  //Create the sudokuMatrix
  int grid[9][9] = {  {3, 0, 6, 5, 0, 8, 4, 0, 0}, 
                      {5, 2, 0, 0, 0, 0, 0, 0, 0}, 
                      {0, 8, 7, 0, 0, 0, 0, 3, 1}, 
                      {0, 0, 3, 0, 1, 0, 0, 8, 0}, 
                      {9, 0, 0, 8, 6, 3, 0, 0, 5}, 
                      {0, 5, 0, 0, 9, 0, 6, 0, 0}, 
                      {1, 3, 0, 0, 0, 0, 2, 5, 0}, 
                      {0, 0, 0, 0, 0, 0, 0, 7, 4}, 
                      {0, 0, 5, 2, 0, 6, 3, 0, 0} };

  printf("Original Grid: \n");
  genGrid(grid);

  printf("\nSolved Grid: \n");

  if(solveGrid(grid) == true)
  {
    genGrid(grid);
  }

  return 0;
}
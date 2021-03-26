#include "sudoku.h"
//Partners: smruthi2, manogna3
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------
//In this program, we are solving a sudoku that is 9 by 9. This program uses two dimensional arrays and
//checks if the number to be placed is valid and according to the rules of sudoku. In this program, we
//use nested loops and recursion to solve the sudoku.
// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);


  for (int col=0; col<9; col++){//iterate through columns
    if(sudoku[i][col]==val){//check if value is already in element specified by row index and column index
      return 1; //if it is, return 1
    }

  }

  // BEG TODO
  
  return 0; //else , return 0
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  for (int row=0; row<9; row++){//iterate through rows
    if(sudoku[row][j]==val){//check if value is already in element specified in row index and column index.
      return 1; //return 1 if it is
    }
  // BEG TODO

  
  
 
  // END TODO
}
return 0;  //return 0 if value can be placed in specified column
}
// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  int actualrow=0; //initializing actualrow variable
  int actualcolumn=0; //initializing actualcolumn variable
  actualrow=(i/3)*3; //calculating actual row in the 3x3 zone of the sudoku
  actualcolumn=(j/3)*3; //calculating actual columnin the 3x3 zone of the sudoku

  
  for (int r=actualrow; r<=actualrow+2; r++){ //iterate from first row index in the 3x3 zone specified by actualrow
    for (int c=actualcolumn; c<=actualcolumn+2; c++){ //iterate from first column index in the 3x3 zone specified by actualcolumn
      if (sudoku[r][c]==val){ //if value in sudoku is equal to val 
        return 1; //return 1
      }
    }
  }
  // BEG TODO
  
  return 0; //return 0
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);
  if(is_val_in_row(val, i, sudoku)==0 && is_val_in_col(val, j, sudoku)==0 && is_val_in_3x3_zone(val, i, j, sudoku)==0){
    //check if all the three conditions met for the value to be placed in the index of the sudoku
    return 1;  //return 1 if it is
  }
  // BEG TODO
  return 0;  //return 0 if not
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.  
  int zerocount=0; //initialize counter for how many zeroes there are

  int index1=0; //initialize row index of empty cell
  int index2=0; //initialize column index of empty cell
  int i, j; //declare row and column index
  for (i=0; i<9; i++){ //iterate through rows of sudoku
    for (j=0; j<9; j++){ //iterate through columns of sudoku
      if (sudoku[i][j]==0) { 
       //check if element is empty 
        zerocount++;      
        //if it is, increment zerocount variable
  }
    }
  }
  if (zerocount==0){ //if zerocount is 0
    return 1;        //return 1
  }
  
  else { //else, if there are empty elements, find the indices of the first empty location
   for (i=0; i<9; i++){  //iterate through rows
    for (j=0; j<9; j++){ //iterate through columns
      if(sudoku[i][j]==0){ //check if element at row and column index are 0
        if (index1!=i){  
          index1=i;  //set index1 to empty element row index
        }
        if(index2!=j){
          index2=j;  //set index2 to empty element column index 
        }
          
          i=10;  //set row index to 10 to break out of loops
          j=10; //set column index to 10 to break out of loops
      }



    }
   }
  }

  
   
  for (int num = 1; num <= 9; num++) {  //iterate from 1 to 9 to check if num is valid
    if ((is_val_valid(num, index1,index2, sudoku)==1)) {  //check if num at row index and column index of sudoku is valid
         sudoku[index1][index2] = num; //store value into sudoku location that was empty
      if (solve_sudoku(sudoku)) { //recursion with sudoku
        return 1; //return 1
      }
      sudoku[index1][index2] = 0;  //set sudoku at index values to 0
    }
  }
  return 0; //return 0 




  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}







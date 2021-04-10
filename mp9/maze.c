//Partners: smruthi2, manogna3
 //Introduction: This program utilizes dynamic memory allocation, matrices, I/O and nested for loop
 //to read a maze from a file and recursively find a path to the end of the maze.
 
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
 
 
/*
* createMaze -- Creates and fills a maze structure from the given file
* INPUTS:       fileName - character array containing the name of the maze file
* OUTPUTS:      None
* RETURN:       A filled maze structure that represents the contents of the input file
* SIDE EFFECTS: None
*/
maze_t * createMaze(char * fileName)
{
   
   FILE *openfile; //create pointer to file
   openfile =fopen(fileName,"r"); //read the file and store location in openfile pointer
  
   int r; //create row index variable
   int c; //create column index variable
   if(openfile == NULL) //check if pointer is NULL
     return NULL; //return NULL if pointer is NULL
   
 
  
   fscanf(openfile, "%d %d", &c, &r); //read column and row size from file
    
   maze_t *mazeptr=malloc(sizeof(maze_t)); //allocate memory for maze
   mazeptr->width=c; //set width member to column size from file
   mazeptr->height=r; //set height member to column size from file
  
   mazeptr->cells=(char**)malloc (r*sizeof(char*)); //allocates space for rows
   int a;
   for (a=0; a<r; a++){ //for loop to iterate through the rows
       mazeptr->cells[a]=(char*)malloc(c*sizeof(char)); //allocates space for columns
   }

   int i; //create variable for row index
   int j; //create variable for column index
   //nested for loop to iterate through the maze 
   for (i=0; i<r; i++){ 
       for (j=0; j<c; j++){
        char letter= fgetc(openfile); //get the character from the file and store it in letter variable
        if (letter=='\n'){   //check if the letter is a new line character
            letter=fgetc(openfile); //goes to the next character if new line
        }
        if(letter!='\n'){ //if not, newline character
            mazeptr->cells[i][j]=letter; //store it in the maze current element
        }
        
        if (letter==START){ //if the letter is 'S'
            mazeptr->startRow=i; //store current index into startRow 
             mazeptr->startColumn=j; //store current index into StartColumn 
        }
 
       if (letter==END){ //if the letter is 'E'
            mazeptr->endRow=i; //store current index into endRow
             mazeptr->endColumn=j; //store current index into endRow
        
       }
   }
    
   }
   fclose(openfile);//close the file
   return mazeptr; //return the pointer to the maze

}
 
/*
* destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
* INPUTS:        maze -- pointer to maze structure that contains all necessary information
* OUTPUTS:       None
* RETURN:        None
* SIDE EFFECTS:  All memory that has been allocated for the maze is freed
*/
void destroyMaze(maze_t * maze)
{
int i; //declare loop variable
   for (i=0; i<maze->height; i++){ //loop to iterate through the rows 
       free(maze->cells[i]); //free rows
      
   }
   free (maze->cells); //free cells
   free (maze); //free maze
 
   maze=NULL; //set maze to NULL
  
}
 
/*
* printMaze --  Prints out the maze in a human readable format (should look like examples)
* INPUTS:       maze -- pointer to maze structure that contains all necessary information
*               width -- width of the maze
*               height -- height of the maze
* OUTPUTS:      None
* RETURN:       None
* SIDE EFFECTS: Prints the maze to the console
*/
void printMaze(maze_t * maze)
{

   int i;   //declare loop variables(row and col)
   int j;
   //nested for loop to print out the maze cell by cell 
   for (i=0; i<maze->height; i++){
      
       for (j=0; j< maze->width; j++){
           printf("%c", maze->cells[i][j]);
          
          
       }
       printf("\n");    //print new liine
   }
}
 
/*
* solveMazeManhattanDFS -- recursively solves the maze using depth first search,
* INPUTS:               maze -- pointer to maze structure with all necessary maze information
*                       col -- the column of the cell currently beinging visited within the maze
*                       row -- the row of the cell currently being visited within the maze
* OUTPUTS:              None
* RETURNS:              0 if the maze is unsolvable, 1 if it is solved
* SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
*/
 

int solveMazeDFS(maze_t * maze, int col, int row)
{
   //check if the row and col areee within the bounds of matrix
   if (col<0||(col>=maze->width)||row<0 || row>=maze->height){
       //if so, it is invalid
       return 0;
   }
 
 
    //check if the cell is not empty
   if (maze->cells[row][col]==WALL||maze->cells[row][col]==VISITED||maze->cells[row][col]==PATH){
       return 0;    //return false and can't move to the cell
   }
   //check if the end is reached,
   if (maze->cells[row][col]==END){
       maze->cells[maze->startRow][maze->startColumn]=START; //start can be overwritten, so set it back to proper row and column location
       return 1;//return cause it reached end of maze
   }
  

   //if the cell is not the end, set it equal to the '*'
   if (maze->cells[row][col]!=END){
          maze->cells[row][col]=PATH;
  
   }
 //recurisve calls to left, right, up and down
   if (solveMazeDFS(maze,col-1,row)){
       return 1;
   }
 
   if (solveMazeDFS(maze,col+1, row)){
       return 1;
   }
   if (solveMazeDFS(maze,col, row-1)){
       return 1;
   }
   if (solveMazeDFS(maze,col, row+1)){
       return 1;
   }
 
 //mark as visited if not 'S' or 'E'
   if (maze->cells[row][col]!=START && maze->cells[row][col]!=END){
       maze->cells[row][col]=VISITED;
   }
 
 
 
  
   return 0; //return 0, if none of the above is successful
}
 
 
 



//partners: manogna3, smruthi2
//This program simulates 2048 using data structures and pointers 
//in order to create an instance of the game data structure.
//It utilizes  4 functions to slide the tiles and merge them accordingly.
//It constantly accesses members of the data structures to check 
//if values within a cell can be changed or if it is empty.
#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //  Initialize all other variables in game struct
    mygame->rows = rows;           //setting rows of game to inputted rows
    mygame->cols = cols;            //setting cols of game to inputted cols
    for(int a = 0; a < rows*cols; a++)
    {
        *(mygame->cells+a)= -1;     //initializes cells in game to -1
    }
    mygame->score = 0;          //sets score to 0

    return mygame;                 // returns a game of struct game
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

     //  Initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows;
    (*_cur_game_ptr)->cols = new_cols;
    //reinitializes cells in current game to -1
    for(int a = 0; a < new_rows*new_cols; a++)
    {
        *((*_cur_game_ptr)->cells+a) = -1;          
    }
    //sets score to 0 again
    (*_cur_game_ptr)->score = 0; 
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{

    if(row<0 || row >= cur_game->rows)          //check if row exists and is within bounds
    {
        return NULL;                            //if not return null
    }
    if(col < 0 || col >= cur_game->cols)        //check if col exists and is within bounds
    {
        return NULL;
    }
    //if cell is valid, then return the pointer to the cell 
    return cur_game->cells + row * cur_game->cols + col;   
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //initialize counter to keep track of how many changes are made
    int moved = 0;
    //create an instance of game by using the make_game function
    game * copy_game = make_game(cur_game->rows, cur_game->cols);
    //nested for loop that copies values from cur_game's cells to copygame's cells
    for(int a = 0; a < cur_game->rows; a++)
    {
        for(int b = 0; b < cur_game->cols; b++)
        {
             *(copy_game->cells + (a * cur_game->cols + b)) =  *(cur_game->cells+ (a * cur_game->cols + b));
        }
    }
    int i, j;
    //for loop that slides tiles upward in the game board
    for(j = 0; j < cur_game->cols; j++)
    {
        //index of cell that is empty and can be filled
        int empty;
        //empty for loop to find the first nonempty cell in the column
        for(empty = 0; empty<cur_game->rows && ((*(cur_game->cells+(empty * cur_game->cols + j))) !=-1); empty++);
        //for loop that checks the values after empty to move tiles up accordingly
        for(i = empty+1; i < cur_game->rows; i++)
        {
            //if the tile isn't empty, it moves it up and sets the current cell to -1
            if(*(cur_game->cells+(i * cur_game->cols + j)) !=-1)
            {
                (*(cur_game->cells+(empty * cur_game->cols + j))) = (*(cur_game->cells+(i * cur_game->cols + j)));
                (*(cur_game->cells+(i * cur_game->cols + j))) = -1;
                moved++;            //increments counter to keep track of # of changes
                empty++;            //increments index
            }
        }
    }

    int m, n;
    //nested for loop that merges two tiles when sliding upward based on the values of the tiles
    for(m = 0; m < cur_game->rows-1; m++)
    {
        for(n = 0; n < cur_game->cols; n++)
        {
            //if a tile is empty, no merging takes place/skip
            if((*(cur_game->cells+(m * cur_game->cols + n))) == -1) continue;
            //otherwise, check if the values are equal
            if((*(cur_game->cells+(m * cur_game->cols + n))) == (*(cur_game->cells+((m+1) * cur_game->cols + n)) ))
            {
                //if so, merge and set top tile to double the value
                (*(cur_game->cells+(m * cur_game->cols + n)) *= 2);
                //increment score with the value of the merged tile
                cur_game->score += (*(cur_game->cells+(m* cur_game->cols + n)));
                //set the bottom tile to empty(-1)
                (*(cur_game->cells+((m+1) * cur_game->cols + n)) = -1);
                //increment the counter that kweeps track of # of changes
                moved++;
            }
        }
    }

   
   int a, b;
   //for loop that slides up the tiles after merging so holes will not exist
    for(b = 0; b < cur_game->cols; b++)
    {   
        int empty;
        //gets first nonempty cell
        for(empty = 0; empty<cur_game->rows && ((*(cur_game->cells+(empty * cur_game->cols + b))) !=-1); empty++);
        //for loop that goes through from indes after empty
        for(a = empty+1; a < cur_game->rows; a++)
        {
            //if the tiles is not empty
            if((*(cur_game->cells+(a * cur_game->cols + b))) !=-1)
            {
                //setting the top tile to what the bottom tile's value is 
                (*(cur_game->cells+(empty * cur_game->cols + b))) = (*(cur_game->cells+(a* cur_game->cols + b)));
                //setting bottom tile to empty
               (*(cur_game->cells+(a * cur_game->cols + b))) = -1; 
               moved++;
                empty++;
            }
        }
    }
   
    //if there is no changes happening in the cells, return 0 so unnecessary shifts won't be made
    if(moved == 0)
    {
        return 0;
    }
        
    return 1;
}


int move_s(game * cur_game) //slide down function
{
    game * copy_game = make_game(cur_game->rows, cur_game->cols); //make instance of game in copy_game
    for(int a = 0; a < cur_game->rows; a++) //nested for loop to copy values into copy_game
    {
        for(int b = 0; b < cur_game->cols; b++)
        {
             *(copy_game->cells + (a * cur_game->cols + b)) =  *(cur_game->cells+ (a * cur_game->cols + b)); //copy game 
        }
    }
 int i, j;
 int moved = 0;
 //for loop to iterate the cur_game values in the columns
    for(j = 0; j < cur_game->cols; j++)
    {
        int empty;
    //for loop to go through the values
        for(empty = cur_game->rows; empty>=0 && ((*(cur_game->cells+(empty * cur_game->cols + j))) !=-1); empty--);
        for(i = empty-1; i >=0; i--)
        {
            //check if value is no empty
            if(*(cur_game->cells+(i * cur_game->cols + j)) !=-1)
            {
                //set bottom tile to the value (slide down)
                (*(cur_game->cells+(empty * cur_game->cols + j))) = (*(cur_game->cells+(i * cur_game->cols + j)));
                //set the other tile to empty
                (*(cur_game->cells+(i * cur_game->cols + j))) = -1;
            //increment moved 
                moved++;
                empty--;
            }
        }
    }


    int m, n;
    //nested for loop to merge values
    for(m = cur_game->rows-1; m >=0 ; m--)
    {
        for(n = 0; n < cur_game->cols; n++)
        {
            //check if it is not empty
            if((*(cur_game->cells+(m * cur_game->cols + n))) == -1) continue;
                //check if the tiles are equal
            if((*(cur_game->cells+(m * cur_game->cols + n))) == (*(cur_game->cells+((m-1) * cur_game->cols + n)) ))
            {
                (*(cur_game->cells+(m* cur_game->cols + n)) *= 2); //if they are equal, merge and set bottom tile to double the value
                cur_game->score += (*(cur_game->cells+(m* cur_game->cols + n))); //increment score
                (*(cur_game->cells+((m-1) * cur_game->cols + n)) = -1); //set the top tile to empty, -1
                moved++; //increment moved 
            }
        }
    }

   // slidedown(&cur_game, cur_game->rows, cur_game->cols);
   int a, b;
   //for loop to iterate through the columns of cur_game
    for(b = 0; b < cur_game->cols; b++)
    {
        int empty;
//iterate through the rows
        for(empty = cur_game->rows; empty>=0 && ((*(cur_game->cells+(empty * cur_game->cols + b))) !=-1); empty--);
        for(a = empty-1; a >=0; a--)
        {
            if(*(cur_game->cells+(a * cur_game->cols + b)) !=-1) //check if its not empty
            {
                (*(cur_game->cells+(empty * cur_game->cols + b))) = (*(cur_game->cells+(a * cur_game->cols + b))); //slide down
                (*(cur_game->cells+(a * cur_game->cols + b))) = -1; //set top tile to empty, -1
                empty--; //decrement empty
                moved++; //increment moved
            }
        }
    }
 
    if(moved == 0) //check if moved is equal to 0 and no changes were made to the board
    {
        return 0; 
    }
     return 1;
    
}

//moves slides left
int move_a(game * cur_game) //slide left
{
    int moved = 0;
    //instance of game
    game * copy_game = make_game(cur_game->rows, cur_game->cols);
    for(int a = 0; a < cur_game->rows; a++)
    {
        for(int b = 0; b < cur_game->cols; b++)
        {
             *(copy_game->cells + (a * cur_game->cols + b)) =  *(cur_game->cells+ (a * cur_game->cols + b));
        }
    }
    int i, j;
    //for loop that slides tiles to the left
    for(i = 0; i < cur_game->rows; i++)
    {
        int empty;
        //find nonemtpy cell
        for(empty = 0; empty<cur_game->cols && ((*(cur_game->cells+(i * cur_game->cols + empty))) !=-1); empty++);
        //for loop that goes through left side of empty and slides them to the left
        for(j = empty+1; j < cur_game->cols; j++)
        {
            if(*(cur_game->cells+(i * cur_game->cols + j)) !=-1)
            {
                (*(cur_game->cells+(i * cur_game->cols + empty))) = (*(cur_game->cells+(i * cur_game->cols + j)));
                        
                (*(cur_game->cells+(i * cur_game->cols + j))) = -1;
                  //increment counter  
                empty++;
                moved++;
            }
        }
    }

    int m, n;
    for(m = 0; m < cur_game->rows; m++)
    {
        //nested for
        for(n = 0; n < cur_game->cols; n++)
        {   
            if((*(cur_game->cells+(m * cur_game->cols + n))) == -1) continue;
            //merges the tiles to the left by doubling the tile on the left 
            if((*(cur_game->cells+(m * cur_game->cols + n))) == (*(cur_game->cells+(m * cur_game->cols + (n+1))) ))
            {
                (*(cur_game->cells+(m * cur_game->cols + n)) *= 2);
                cur_game->score += (*(cur_game->cells+(m* cur_game->cols + n)));
                (*(cur_game->cells+(m * cur_game->cols + (n+1))) = -1);
                //increment counter
                moved++;
            }
        }
    }

   int a, b;
   //for loop that slides tile left
    for(a = 0; a < cur_game->rows;a++)
    {
        int empty;
        //finds nonempty
        for(empty = 0; empty<cur_game->cols && ((*(cur_game->cells+(a * cur_game->cols + empty))) !=-1); empty++);
        
        for(b = empty+1; b < cur_game->cols; b++)
        {
            //finds nonempty and moves it to the left 
            if(*(cur_game->cells+(a * cur_game->cols + b)) !=-1)
            {
                (*(cur_game->cells+(a * cur_game->cols + empty))) = (*(cur_game->cells+(a * cur_game->cols + b)));
                        
                (*(cur_game->cells+(a * cur_game->cols + b))) = -1;
                    moved++;
                empty++;
            }
        }
    }

    //checks if the values in cells are being changed, if not then just return 0
    if(moved == 0)
    {
        return 0; 
    }
    return 1;
}

int move_d(game * cur_game){ //slide to the right
game * copy_game = make_game(cur_game->rows, cur_game->cols);
    for(int a = 0; a < cur_game->rows; a++)
    {
        for(int b = 0; b < cur_game->cols; b++)
        {
             *(copy_game->cells + (a * cur_game->cols + b)) =  *(cur_game->cells+ (a * cur_game->cols + b));
        }
    }
    int i, j;
    int moved = 0;
    for(i = 0; i < cur_game->rows; i++)
    {
        int empty;
        //finds nonempty cell in the list of tiles
        for(empty = cur_game->cols-1; empty>=0 && ((*(cur_game->cells+(i * cur_game->cols + empty))) !=-1); empty--);
        for(j = empty-1; j >= 0; j--)
        {
            //if tile is not empty then set the tile on the right to the value, so tiles are slid to the right
            if(*(cur_game->cells+(i * cur_game->cols + j)) !=-1)
            {
                (*(cur_game->cells+(i * cur_game->cols + empty))) = (*(cur_game->cells+(i * cur_game->cols + j)));
                        
                (*(cur_game->cells+(i * cur_game->cols + j))) = -1;
                 moved++;   
                empty--;
            }
        }
    }

    int m, n;
    for(m = 0; m < cur_game->rows; m++)
    {
        for(n = cur_game->cols; n >=0 ; n--)
        {
            if((*(cur_game->cells+(m * cur_game->cols + n))) == -1) continue;
            //merging the values to the right and settring the tile on the right to double the value of 
            //equivalent tiles
            if((*(cur_game->cells+(m * cur_game->cols + n))) == (*(cur_game->cells+(m * cur_game->cols + (n-1))) ))
            {
                (*(cur_game->cells+(m * cur_game->cols + n)) *= 2);
                cur_game->score += (*(cur_game->cells+(m* cur_game->cols + n)));
                //sets other tile to empty
                (*(cur_game->cells+(m * cur_game->cols + (n-1))) = -1);
                moved++;
            }
        }
    }

   int a, b;
    for(a = 0; a < cur_game->rows; a++)
    {
        int empty;
        //find nonempty cell
        for(empty = cur_game->cols-1; empty>=0 && ((*(cur_game->cells+(a * cur_game->cols + empty))) !=-1); empty--);
        for(b = empty-1; b >= 0; b--)
        {
            //if the value is not empty then change the values of the tiles by sliding to the right
            if(*(cur_game->cells+(a * cur_game->cols + b)) !=-1)
            {
                (*(cur_game->cells+(a * cur_game->cols + empty))) = (*(cur_game->cells+(a * cur_game->cols + b)));
                        
                (*(cur_game->cells+(a * cur_game->cols + b))) = -1;
                moved++;
                empty--;
            }
        }
    }

   //if no changes made, return 0
    if(moved == 0)
    {
        return 0;
    }
    return 1;
}

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
    //1 if any empty spaces on board or any 2 adjacent tiles on board
    //otherwise return 0
    
 */
{
    //nested for loop that goes through all the cells 
    for(int t = 0; t < cur_game->rows; t++)
    {
        for(int b = 0; b < cur_game->cols; b++)
        {
            //if any cell is empty, the game can be played so return 1
            if( *(cur_game->cells + t*cur_game->cols+b) == -1)
                return 1;
                //chweck the values ot the left of the b to see if any adjacent values
            if(b > 0 )      //left case
            {
                //if the values are the same, return 1 bc game can still be plahyed
                if(*(cur_game->cells + t*cur_game->cols+(b-1) ) == *(cur_game->cells + t*cur_game->cols+(b)))
                    return 1;
            }
            //check values to the right of b to see if any same values and return 1
             if(b < cur_game->cols-1 )      //right case
            {
                if(*(cur_game->cells + t*cur_game->cols+(b+1) ) == *(cur_game->cells + t*cur_game->cols+(b)))
                    return 1;
            }
            //check values below it to see if any same values and return 1 
            if(t < cur_game->rows-1 )      //down case
            {
                if(*(cur_game->cells + (t+1)*cur_game->cols+b ) == *(cur_game->cells + t*cur_game->cols+b))
                    return 1;
            }
            //check values above it to see if any same values and return 1
            if(t > 0 )      //up case
            {
                if(*(cur_game->cells + (t-1)*cur_game->cols+b ) == *(cur_game->cells + t*cur_game->cols+b))
                    return 1;
            }
        }
    }
    //if none of it is possible, return 0--> game endEDDDDDD
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

   if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
      printf("Game Over!\n");
       return 0;
    }
    return 1;
}

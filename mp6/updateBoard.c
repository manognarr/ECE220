/*  Partners: smruthi2, manogna3
    This program uses a 2D array to simulate the Game of Life board, and updates this board
    based on the neighbors of each cell, specifically checking how many are 0 or 1. This 
    program uses the original board values to update the board each time. We used nested
    for loops to access the two dimensional arrays and update the values.
*/


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */





int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

int liveneighbor=0;  //initializing variable that keeps track of liveneighbors
for (int a=row-1; a<=row+1; a++){ //loop to iterate through each row of board
    if(a>=0 && a<=boardRowSize-1){ //check if index is within board size
        for (int b=col-1; b<=col+1; b++){ //inner loop to iterate through column of each row
            if(b>=0 && b<=boardColSize-1){ //check if index is within board size
                    if(board[a*boardColSize+b]==1){ //check if value of cell is 1
                        liveneighbor++; //increment liveneighbor
                    }
                }
        
        }
    }
}

if (board[row*boardColSize+col]==1){ //check if current cell is 1
    liveneighbor--;                 //if it is, decrement liveneighbor by 1
}

return liveneighbor;                //return liveneighbor variable

}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */

void updateBoard(int* board, int boardRowSize, int boardColSize) {
    
   
    int boardcopy[boardRowSize*boardColSize]; //declaring copy of board
    
    for (int r=0; r<boardRowSize; r++){ //outer loop to iterate through rows

    for (int c=0; c<boardColSize; c++){ //inner loop to iterate through columns
        boardcopy[r*boardColSize+c]=board[r*boardColSize+c]; //duplicate val into boardcopy
    }
        
    }


    for (int i=0; i<boardRowSize; i++){ //outer loop to iterate through rows
        for (int j=0; j<boardColSize; j++){ //inner loop to iterate through columns
            int result=countLiveNeighbor(boardcopy, boardRowSize, boardColSize, i, j); 
            //calls on function to check how many neighbors are live
        
            if (boardcopy[i*boardColSize+j]==1){ //check if original loc value is 1
                if(result==2 || result==3){     //if 2 or 3 neighbors are live
                    board[i*boardColSize+j]=1;  //update board value to 1
                  
                }
                else if(result<2){              //check if less than 2 live neighbors
                    board[i*boardColSize+j]=0; //update board value to 0
                    

                }
                else{
                    board[i*boardColSize+j]=0;  //update board value to 0
                   
                }
            }

            if(boardcopy[i*boardColSize+j]==0){  //check if original loc value is 0
                if (result==3){                  //check if there are 3 live neighbors
                     board[i*boardColSize+j]=1;  //update board value to 1
                     
                }
            }
        }
    }


}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int boardcompare[boardRowSize*boardColSize]; //declare copy of board 
    for (int a=0; a<boardRowSize; a++){         //iterate through rows
        for (int b=0; b<boardColSize; b++){    //iterate through columns
             boardcompare[a*boardColSize+b]=board[a*boardColSize+b]; 
             //duplicate each value from board to boardcompare
        }
    }



    for (int i=0; i<boardRowSize; i++){ //iterate through updated board rows
        for (int j=0; j<boardColSize; j++){ //iterate through updated board columns
            int result=countLiveNeighbor(boardcompare, boardRowSize, boardColSize, i, j); 
            //call function to keep track of number of live neighbors
        
            if (board[i*boardColSize+j]==1){ //check if updated board value is 1
                if(result==2 || result==3){ //check if there are 2 or 3 live neighbors
                    boardcompare[i*boardColSize+j]=1; //update copy of board to 1
                    
                }
                else if(result<2){          //check if there are less than 2 live neighbors
                    boardcompare[i*boardColSize+j]=0; //update copy of board to 0
                    

                }
                else{
                    boardcompare[i*boardColSize+j]=0; //update copy of board to 0
                   
                }
            }

            if(board[i*boardColSize+j]==0){  //check if current loc value is 0
                if (result==3){              //if there are three live neighbors
                     boardcompare[i*boardColSize+j]=1; 
                     //update copy of board to 1
                   
                }
            }
        }
    }



    for (int a=0; a<boardRowSize; a++){ //outer loop to iterate through each row of board
        for (int b=0; b<boardColSize; b++){ //inner loop to iterate through each column of board
            if (boardcompare[a*boardColSize+b]!=board[a*boardColSize+b]){  
                //check if each board's elements are the same
                return 0; //done updating board

            }
        
                
            
        }
    }


   
 return 1; //otherwise, return 1
    


}

                
                
            



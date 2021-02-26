//Partners: smruthi2, manogna3
//This program prints out a certain row in Pascal's triangle based on the user's input. 
//It uses the data type, unsigned long and uses two for loops to calculate the Pascal's
//triangle row and prints the row.
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row; //declare row variable

  printf("Enter a row index: "); //prompt user for row index
  scanf("%d",&row); //read the input

//initialize variables for outer and inner loop and result

    unsigned long n=0; 
    unsigned long k=0;
//first value of every row is 1
    unsigned long result=1;
   
    
    //outer loop that goes up to row 
    for (n=0; n<=row; n++){
        result=1;
    //inner loop that goes up to n
        for(k=1; k<=n; k++){
            result=(result*(row+1-k))/(k); //calculates the value to be outputted based on row position
           
        }
        printf("%lu ", result); //print final result
    }





 

  return 0;
}



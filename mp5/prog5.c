/*     
*
* prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
*           student code -- GOLD VERSION by Steven S. Lumetta
*/
 
 
/*
partners: manogna3, smruthi2
* The functions that you must write are defined in the header file.
* Blank function prototypes with explanatory headers are provided
* in this file to help you get started.
*/
//In this program, we simulated the game of Wheel of Fortune where the user can enter 
//up to 10 guesses and see if their guess matches the solution that was placed in a
//two dimensional array that was randomly placed with words from a pool. The program 
//keeps track of the user's points and the number of misplaced matches and perfect
//matches by traversing through the solutions and guesses arrays.
 
 
 
#include <stdio.h>
#include <stdlib.h>
 
#include "prog5.h"
 
int guess_number; 
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
* INPUT: none
* OUTPUT: none
*/
void print_pool() {
   printf("Valid term to guess:\n\t");
   for(int i = 0; i < 8 ; ++i) {
       printf("%s ", pool[i]);
   }
   printf("\n");
}
 
/*
* is_valid -- This function checks whether a string is valid
* INPUTS: str -- a string to be checked
* OUTPUTS: none
* RETURN VALUE: 0 if str is invalid, or 1 if str is valid
* SIDE EFFECTS: none
*/
int is_valid(char* str) {
   int i = 0;
  // int counter=0;
   if (str == NULL) {
       return 0;
   }
 
 
   for (i = 0; i < 8; i++) {
       if (strcmp(str, pool[i]) == 0) {
           return 1;
       }
   }
   return 0;
}
 
 
/*
* set_seed -- This function sets the seed value for pseudorandom
* number generation based on the number the user types.
* The input entered by the user is already stored in the string seed_str by the code in main.c.
* This function should use the function sscanf to find the integer seed value from the
* string seed_str, then initialize the random number generator by calling srand with the integer
* seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
* INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
* OUTPUTS: none
* RETURN VALUE: 0 if the given string is invalid (string contains anything
*               other than a single integer), or 1 if string is valid (contains one integer)
* SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
*               if string is invalid. Prints nothing if it is valid.
*/
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below
   int seed; //variable to hold seed
   char post[2]; //a character array with length 2
   

   //check if the seed entered is exactly one integer.
   if (sscanf (seed_str, "%d%1s", &seed, post) != 1) { 
     printf("%s", "set_seed: invalid seed\n");
     return 0;
   }
 
   else{
         srand(seed); //call srand function and pass in the user entered seed value.
         return 1;
     }
  
   // your code here
}
 
 
/*
* start_game -- This function is called by main.c after set_seed but before the user makes guesses.
*               This function creates the four solution numbers using the approach
*               described in the wiki specification (using rand())
*               The four solution numbers should be stored in the static variables defined above.
*               The values at the pointers should also be set to the solution numbers.
*               The guess_number should be initialized to 1 (to indicate the first guess)
*               The score should be initialized to -1. 
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
*/
void start_game () {
   //your code here
  int index=0; //initialize index
 
 
   for (int i=0; i<4; i++){ //loop through that picks four random numbers
       index=rand()%8;
    
      memset(solutions[i], '\0', 10); //set each row's last element to NULL
      strcpy(solutions[i], pool[index]); ///copy randomly chosen words from pool to solutions.
      
     
   }
 
   guess_number=1; //set guess_number to 1
   max_score=-1; //set max_score to -1
 
 
}
 
/*
* make_guess -- This function is called by main.c after the user types in a guess.
*               The guess is stored in the string guess_str.
*               The function must calculate the number of perfect and misplaced matches
*               for a guess, given the solution recorded earlier by start_game
*               The guess must be valid (contain only 4 strings from pool). If it is valid
*               the number of correct and incorrect matches should be printed, using the following format
*               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
*               If valid, the guess_number should be incremented.
*               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
*               For an invalid guess, the guess_number is not incremented.
* INPUTS: guess_str -- a string consisting of the guess typed by the user
* OUTPUTS: none
* RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid,
*               or 0 if it is invalid
* SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
*               or an error message (invalid guess)
*               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
*/
int make_guess (const char guess_str[]) {
//   // your code here
char guesstemp [strlen(guess_str)]; //declare duplicate array to hold guess_str
char* guess [10]; //intialize pointer array to check if words are valid
char guesses[4][10]; //2D array that holds user guesses
char post[2]; //character array of length 2


//check if user has entered exactly four words, and place them in guesses array
if(sscanf(guess_str, "%s%s%s%s%1s", guesses[0], guesses[1], guesses[2], guesses[3], post)!= 4)
{
   printf("number of input!= 4\n");
   printf("%s", "make_guess: invalid guess\n"); 

   return 0;
}
 


int currentscore = 0; //initialize currentscore variable
 
 

 //iterate through guess_str and duplicate guess_str in guesstemp
for (int a=0;a<strlen(guess_str); a++){
   guesstemp[a]=guess_str[a];
}
 
 
char* ptr = strtok(guesstemp," "); //check for space and put one word at a time into ptr location
int b=0;
 

 //loop that goes through different words and puts them into guess
 
while (ptr!=NULL){
    guess[b]=ptr;
    b++;
    ptr=strtok(NULL, " ");
  
   
}
 
 //check if each word in guess is valid.
for (int c=0; c<4; c++){
if (is_valid(guess[c])!=1){
     printf("%s", "make_guess: invalid guess\n");
     return 0;
 }
 


int perfectmatches; //declare perfectmatches variable
  int misplacedmatches; //declare misplacedmatches variable
  perfectmatches = 0; //initialize perfectmatches to 0
  misplacedmatches = 0; //initialize misplacedmatches to 0



  int guesscheck[4]={0,0,0,0}; //initialize guesscheck array to mark matched guesses
  int solcheck[4]={0,0,0,0}; //initialize solcheck array to mark matched solutions

  //loop through guesses and solutions arrays to check for perfect matches
  for (int j=0; j<4; j++)
  {
   
   if (strcmp(guesses[j], solutions[j])==0 )
   {
       //mark paired words as 1 in guesscheck and solcheck arrays.
              guesscheck[j]=1;
              solcheck[j] = 1;
              perfectmatches++; //increment perfectmatches variable
   }
 
}
 //print guessnumber and perfectmatches 
   printf("With guess %d, you got %d perfect matches and ",guess_number, perfectmatches);


//nested for loop to check if there are any misplaced matches
  for(int a = 0; a < 4; a++)
  {
      for(int b = 0; b < 4; b++)
      {
          if((strcmp(guesses[a], solutions[b]) == 0) && guesscheck[a]!= 1 && solcheck[b]!= 1 && a!=b)
          {
              //mark paired words as 1 in guesscheck and solcheck arrays.
              guesscheck[a]=1;
              solcheck[b]=1;
              misplacedmatches++; //increment misplacedmatches variable
             
          }
      }
  }
  
  currentscore = perfectmatches*1000 + misplacedmatches*100; //update currentscore
   printf("%d misplaced matches.\n", misplacedmatches); //print number of misplaced matches
  

  //check to see if currentscore is greater than maxscore
      if(currentscore >= max_score)
      {
          max_score = currentscore; //if it is, set maxscore to the currentscore
      }
      printf("Your score is %d and your current max score is %d.\n", currentscore, max_score );
      

      //check if user's guess were all perfect matches and if so, return 2 to end the game
      if(perfectmatches == 4)
      {
          printf("You won in %d guesses", guess_number); 
          return 2;
      }
       guess_number++; //increment guessnumber
      return 1;
 
 
 
 
}
 
 
 
 
 
 
 
 
 
 
 
 
 
return 1;
}
 

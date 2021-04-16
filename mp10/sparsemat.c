//Partners: smruthi2, manogna3
//Intro: In this program, we use linked list, file input, output, and pointers to access a matrix in a file and order
//the matrix by row and column and display it in an output file. The data is stored in the format of tuples in a linked list
//which we iterate through to insert, replace and delete nodes based on the values/and order.

#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>

sp_tuples * load_tuples(char* input_file)
{
  FILE *openfile; //create pointer to file
   int r=0; //initialize row variable for loading row size
  int c=0; //initialize column variable for loading column size
  int row = 0; //initialize row variable for loading each value at specified row in matrix
  int col = 0; //initialize column variable for loading each value  at specified column in matrix
  float value=0.0; //initialize value 
  openfile=fopen(input_file, "r"); //open file to read
  sp_tuples *tuplesptr=malloc(sizeof(sp_tuples)); //allocate memory to point to tuples
   fscanf(openfile, "%d  %d", &r, &c); //read row and column size
  tuplesptr->m=r; //set row size member to r
  tuplesptr->n=c; //set column size member to c
  tuplesptr->nz = 0; //initialize nz to 0
  tuplesptr->tuples_head = NULL; //set head to NULL
           while(!(feof(openfile))) //loop to iterate through file until EOF 
          {
              fscanf(openfile, "%d %d %fl", &row, &col, &value); //read corresponding row, column and value 
              set_tuples(tuplesptr, row, col, value); //call set_tuples to update the tuples
          }
     fclose(openfile); //close the file
  return tuplesptr; //return the pointer to tuples
}
double gv_tuples(sp_tuples * mat_t,int row,int col)

{
  sp_tuples_node *node; //create node to iterate through linked list
  double value = 0.0; //initialize value variable
  node = mat_t->tuples_head; //initialize node to point to tuples head
  while(node != NULL) //iterate until node is equal to NULL
  {
      if(node->row == row && node->col == col) //check if row and column members of node are the same as the parameters
      {
          value = node->value; //if they are, set value to node value member
      }
      node = node->next; //increment node to point to the next node
  }
  return value; //return the value
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  sp_tuples_node *curnode; //declare node pointer to iterate through linked list
  sp_tuples_node *temp; //declare temp pointer for inserting in linked list
 
 // int index = (row * mat_t->n + col);
 // int rowfound=0;
  curnode=mat_t->tuples_head; //initialize curnode to tuples head
  if (value==0) //check if value is 0
  {
      if(gv_tuples(mat_t, row, col)!=0) //if it is, also check if the value exists
      {
          while (curnode!=NULL && curnode->next!=NULL) //check if node pointer and next that is iterating is not NULL
          {
              if(curnode->next->row==row && curnode->next->col == col) //check if next node is equal to row and column passed in
              {
                  if(curnode == mat_t->tuples_head) //check if location of curnode is pointing to head, if it is insert value at head
                  {
                      temp = curnode; //set temp to curnode which points to head
                      mat_t->tuples_head = mat_t->tuples_head->next; //set head to next node
                      free(temp); //free temp allocated memory to delete node
                      mat_t->nz--; //decrement nz member of mat_t
                  }
                  temp=curnode->next; //if not equal to head, then set temp node to curnode next
                  curnode->next=temp->next; //set temp next to curnode next 
                  free(temp);  //free, delete temp node 
                  mat_t->nz--; //decrement nz 
              }
              curnode=curnode->next; //increment curnode to next node
          }
      }
  }
 
   else{   //all other values
      if(gv_tuples(mat_t, row, col)!=0)     //if value already exists, replace the value
      {
          while(curnode != NULL) //loop until curnode is NULL
          {
              if(curnode->row == row && curnode->col == col) //check if curnode row is equal to row and curnode col is equal to col
              {
                  curnode->value = value; //set curnode value to value
                  return; //break once value has been set
              }
              curnode = curnode->next; //increment curnode to next node
          }
      }
      else                                //if value doesn't exist, create node and insert into linked list
      {
          sp_tuples_node *nodetraverse = mat_t->tuples_head; //initialize nodetraverse to point to tuples head
           sp_tuples_node *nodetraverse2 =NULL; //initialize nodetraverse2 to point to NULL
          if(nodetraverse == NULL) //if nodetraverse is NULL, and linkedlist is empty
          {
             sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node)); //allocate memory to insert newnode2
              mat_t->tuples_head = newnode2; //point head to newnode2
              newnode2->next = NULL; //point next of newnode2 to NULL as there is only one element
              newnode2->row = row; //set newnode2 row member to row
              newnode2->col = col; //set newnode2 column member to col
              newnode2->value = value; //set newnode2 value to value
              mat_t->nz++; //increment nz member of mat_t
              return; //break out of loop
          }
          
       else{ //if none of the above
          while(nodetraverse != NULL) //loop until nodetraverse is NULL
          {
            //check if current node is greater than row and it is at head, or if nodetraverse row is the same as row, but col is greater at tuples head position
             if((nodetraverse->row > row && nodetraverse==mat_t->tuples_head) ||
             (nodetraverse->row == row && nodetraverse->col > col && nodetraverse==mat_t->tuples_head))
             {
                 sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node)); //allocate memory for newnode2 to insert
                 newnode2->next = mat_t->tuples_head; //set newnode2 next to point to tuples head 
                 mat_t->tuples_head = newnode2; //set head to newnode2 (insert node before head)
                 mat_t->nz++; //increment nz 
                 newnode2->row= row; //set newnode2 member to row
                 newnode2->col = col; //set newnode2 member to col 
                 newnode2->value = value; //set newnode2 member to value
                 return; //break out of loop
             }
              
              else if (nodetraverse->row > row ) //check if nodetraverse member row is greater than row
              {
                 
                 // printf("in the if head");
                  sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node)); //create newnode2 and allocate memory for it
                 
                   newnode2->next = nodetraverse; 
                   if(nodetraverse2 != NULL) //check if nodetraverse2 is not equal to NULL
                   {
                       nodetraverse2->next= newnode2; //insert newnode2 before nodetraverse
                   }
                      
                   newnode2->row=row; //set newnode2 member to row
                   newnode2->col=col; //set newnode2 member to column
                   newnode2->value=value; //set newnode2 value to value
                   mat_t->nz++; //increment nz
                   //nodetraverse2 = nodetraverse;
                   return;
                  
              }
              else if(nodetraverse->row == row) //check if nodetraverse row is equal to row
              {
                  if(nodetraverse->col > col) //check if nodetraverse col is greater
                  {
                      sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node)); //allocate memory for newnode2
                   newnode2->next = nodetraverse; 
                   if(nodetraverse2 != NULL) //check if nodetraverse2 is not equal NULL
                   {
                       nodetraverse2->next= newnode2; //insert newnode2 before greater column
                   }
                   //set corresponding row, col and value members for newnode2 and increment nz member
                   newnode2->row=row; 
                   newnode2->col=col;
                   newnode2->value=value;
                   mat_t->nz++;
                   return;
                  }
                 
              }
             
             
           if(nodetraverse->next == NULL) //check if nodetraverse next is NULL, at the end of linked list
           {
               sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node)); //allocate memory for newnode2
               nodetraverse->next = newnode2; //insert newnode2 at the end
              newnode2->next = NULL; //set newnode2 next is NULL as it is at the end of the linked list
              //set newnode2 corresponding row, col and value members and increment nz members
              newnode2->row = row;
              newnode2->col = col;
              newnode2->value = value;
              mat_t->nz++;
              return;
           }
           
           //update nodetraverse2 and nodetraverse to next
           nodetraverse2 = nodetraverse;
           nodetraverse = nodetraverse->next;
 
          }
 
       }
      }
  } 
  return;
}

 
void save_tuples(char * file_name, sp_tuples * mat_t)
{
 
FILE *outputfile=fopen(file_name, "w"); //open the file to write 
fprintf(outputfile, "%d %d \n", mat_t->m, mat_t->n); //write the row and column size to the file
 
sp_tuples_node *node; //declare node
 
  node = mat_t->tuples_head; //set node to mat_t tuples head
  while(node != NULL) //loop until node is NULL
  {
      fprintf(outputfile, "%d %d %lf \n", node->row, node->col, node->value); //write the node row, column and value to the file
 
      node = node->next; //update node to the next 
  }
 
   fclose(outputfile); //close the file
  return;
}
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
   sp_tuples *matC = (sp_tuples *)malloc(sizeof(sp_tuples)); //allocate memory for the matrix that holds the sum
   matC->m = matA->m; //set row size
   matC->n = matA->n; //set column size
   matC->nz = 0; //initialize nz to 0
   matC->tuples_head = NULL; //set tuples head of matc to NULL
   sp_tuples_node *node = matA->tuples_head;  //create node to iterate through matA
  
   while(node != NULL) //loop until node is NULL
   {
       double value = node->value; //set value variable to node value
       int col = node->col; //set col variable to node col
       int row = node->row; //set row variable to node row
       set_tuples(matC, row, col, value); //set_tuples function to matA values
       node = node->next; //update node to next 
   }
  
   node = matB->tuples_head; //set node to matB tuples head
   while(node != NULL) //loop until node is NULL
   {
       double value = node->value; //set value variable to matB node value
       int col = node->col; //set col variable to matB node col
       int row = node->row; //set row variable to matB node row
       double matcvalue = gv_tuples(matC, row, col); //gv_tuples to get value and put it in matcvalue variable
       set_tuples(matC, row, col, matcvalue+value); //set_tuples function to add matA values to matB values
       node = node->next; //update node to next
   }
return matC; //return matrix with added elements
}
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
  return matA;
}
 void destroy_tuples(sp_tuples * mat_t){
   sp_tuples_node *node; //create node
 
  node = mat_t->tuples_head; //set it to mat_t tuples head
  while(node != NULL) //iterate until node is NULL
  {
      free(node); //free the node 
 
      node = node->next; //update the node to nex
  }
  free(mat_t); //free the matrix, mat_t
  return;
}
 
 
 



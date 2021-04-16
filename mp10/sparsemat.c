#include "sparsemat.h"
 
#include <stdio.h>
#include <stdlib.h>
 
 
 
/*
load_tuples should open a file with the name 'input_file', read the data from the file,
and return a matrix of the list of tuples type. If any coordinates repeat in the input file,
the newer coordinates ( a lower line closer to the end of  the text document ) should overwrite the old line.
If there is an entry with a value of 0 then the corresponding node should be deleted if it exists.
The elements in the input text file may be unordered (unlike the example text file above),
but the list of tuples returned will need to be in order.
You do not have to handle cases where the input_file doesn't match the specified format.
 
 
*/
 
sp_tuples * load_tuples(char* input_file)
{
   FILE *openfile;
  
   int r=0;
   int c=0;
   int row = 0;
   int col = 0;
   float value=0.0;
   openfile=fopen(input_file, "r");
   sp_tuples *tuplesptr=malloc(sizeof(sp_tuples));
  
   fscanf(openfile, "%d  %d", &r, &c);
   tuplesptr->m=r;
   tuplesptr->n=c;
   tuplesptr->nz = 0;
   tuplesptr->tuples_head = NULL;
  
 
           while(!(feof(openfile)))
           {
               fscanf(openfile, "%d %d %fl", &row, &col, &value);
               set_tuples(tuplesptr, row, col, value);
           }
      fclose(openfile);
 
   return tuplesptr;
}
 
 
double gv_tuples(sp_tuples * mat_t,int row,int col)
//gv_tuples return the value of the element at the given row and column within the matrix.
{
   sp_tuples_node *node;
   double value = 0.0;
   node = mat_t->tuples_head;
   while(node != NULL)
   {
       if(node->row == row && node->col == col)
       {
           value = node->value;
       }
       node = node->next;
   }
   return value;
}
 
 
/*set_tuples sets the element at row and col to value. This function will need to do several things:
 
if value is 0, it will need to find the node at row and col if it exists, and delete it from the list.
Be sure to free the nodes from memory or they will be lost forever.
For any other value, the function will need to find the correct location for the node within the sorted linked list.
If the entry already exists, the function should replace the old value.
If the entry doesn't exist, a node should be created and inserted into the linked list.*/
 
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
   sp_tuples_node *curnode;
   sp_tuples_node *temp;
   
  // int index = (row * mat_t->n + col);
  // int rowfound=0;
 
   curnode=mat_t->tuples_head;
   if (value==0)
   {
       if(gv_tuples(mat_t, row, col)!=0)
       {
           while (curnode!=NULL && curnode->next!=NULL)
           {
               if(curnode->next->row==row && curnode->next->col == col)
               {
                   if(curnode == mat_t->tuples_head)
                   {
                       temp = curnode;
                       mat_t->tuples_head = mat_t->tuples_head->next;
                       free(temp);
                       mat_t->nz--;
                   }
                   temp=curnode->next;
                   curnode->next=temp->next;
                   free(temp);
                   mat_t->nz--;
               }
               curnode=curnode->next;
           }
       }
   }
   
    else{   //all other values
       if(gv_tuples(mat_t, row, col)!=0)     //if value already exists, replace the value
       {
           while(curnode != NULL)
           {
               if(curnode->row == row && curnode->col == col)
               {
                   curnode->value = value;
                   return;
               }
               curnode = curnode->next;
           }
       }
       else                                //if value doesn't exist, create node and insert into linked list
       {
           sp_tuples_node *nodetraverse = mat_t->tuples_head;
            sp_tuples_node *nodetraverse2 =NULL;
           if(nodetraverse == NULL)
           {
              sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
               mat_t->tuples_head = newnode2;
               newnode2->next = NULL;
               newnode2->row = row;
               newnode2->col = col;
               newnode2->value = value;
               mat_t->nz++;
               return;
           }
            
        else{
           while(nodetraverse != NULL)
           {
              
              if((nodetraverse->row > row && nodetraverse==mat_t->tuples_head) || 
              (nodetraverse->row == row && nodetraverse->col > col && nodetraverse==mat_t->tuples_head))
              {
                  sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
                  newnode2->next = mat_t->tuples_head;
                  mat_t->tuples_head = newnode2;
                  mat_t->nz++;
                  newnode2->row= row;
                  newnode2->col = col;
                  newnode2->value = value;
                  return;
              }
                
               else if (nodetraverse->row > row )
               {
                   
                  // printf("in the if head");
                   sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
                   
                    newnode2->next = nodetraverse;
                    if(nodetraverse2 != NULL)
                    {
                        nodetraverse2->next= newnode2;
                    }
                        
                    newnode2->row=row;
                    newnode2->col=col;
                    newnode2->value=value;
                    mat_t->nz++;
                    //nodetraverse2 = nodetraverse;
                    return;
                    
               }
               else if(nodetraverse->row == row)
               {
                   if(nodetraverse->col > col)
                   {
                       sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
                    newnode2->next = nodetraverse;
                    if(nodetraverse2 != NULL)
                    {
                        nodetraverse2->next= newnode2;
                    }
                    newnode2->row=row;
                    newnode2->col=col;
                    newnode2->value=value;
                    mat_t->nz++;
                    return;
                   }
                   
               }
               
               
            if(nodetraverse->next == NULL)
            {
                sp_tuples_node *newnode2= (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
                nodetraverse->next = newnode2;
               newnode2->next = NULL;
               newnode2->row = row;
               newnode2->col = col; 
               newnode2->value = value;
               mat_t->nz++;
               return;
            }
            nodetraverse2 = nodetraverse;
            nodetraverse = nodetraverse->next;

           }
   
        }
       }
   }  
   return;
}
 
 
 
 
 //save_tuples writes the data in a sparse matrix structure to a text file in the format specified above.
 // Because of the way the linked lists are ordered, writing the entries of the matrix as you traverse the list 
 //will give an output in row major order. 
 //Your text file output must be in this order even though load_tuples should able to handle reading un-ordered text files.


void save_tuples(char * file_name, sp_tuples * mat_t)
{

FILE *outputfile=fopen(file_name, "w");
fprintf(outputfile, "%d %d \n", mat_t->m, mat_t->n);

 sp_tuples_node *node;
   
   node = mat_t->tuples_head;
   while(node != NULL)
   {
       fprintf(outputfile, "%d %d %lf \n", node->row, node->col, node->value);

       node = node->next;
   }

    fclose(outputfile);
   return;
}
 
 
 
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
    sp_tuples *matC = (sp_tuples *)malloc(sizeof(sp_tuples));
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;
    sp_tuples_node *node = matA->tuples_head;
    
    while(node != NULL)
    {
        double value = node->value;
        int col = node->col;
        int row = node->row;
        set_tuples(matC, row, col, value);
        node = node->next;
    }
    
    node = matB->tuples_head;
    while(node != NULL)
    {
        double value = node->value;
        int col = node->col;
        int row = node->row;
        double matcvalue = gv_tuples(matC, row, col);
        set_tuples(matC, row, col, matcvalue+value);
        node = node->next;
    }
return matC;
 
 
}
 
 
 
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
   return matA;
 
}
 
 
  
void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node *node;
   
   node = mat_t->tuples_head;
   while(node != NULL)
   {
       free(node);

       node = node->next;
   }
   free(mat_t);
   return;
} 
 
 
 
 
 
 
 
 



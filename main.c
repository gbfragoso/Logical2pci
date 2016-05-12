#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ada2asa.h"
#include "pcode.h"
#include "rpn2pci.h"
#include "btree2rpn.h"
#include "pushdown.h"

#define STACK_SIZE 50
#define TREE_SIZE 50

typedef char * string;

void reverse (char *array, int start, int end);
void mirror(char* array);

/*
 *Author: Gustavo B. Fragoso
*/

int main (int argc, char **argv){
	
	// Vector with only integers, used as a datastore
	int stack[STACK_SIZE] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
	// Result of Pushdown Automata
	int productions[50], i;
	// Binary Tree
	char btree[TREE_SIZE] = {""};
	// Reverse Polish Notation
	string rpn;
	
	FILE *input;
    
    	for (i = 0;i<TREE_SIZE;i++){
        	btree[i] = '_';
        	productions[i] = -1;
    	}
    
    	// Initial symbol
    	btree[0] = 'E';
    
    	if (argc == 2){
	    	// Expr
	    	string expr = argv[1];
	    	int size = strlen(expr);
	    	
	    	if(strlen(expr)<50){
	    		FILE *output = fopen("output.txt", "w");
	    		if(output!=NULL){
	    			fprintf(output,"Run: %s %s \n", argv[0], argv[1]);
	    			printf("Step 1. Catch regular expression ... done!\n");
	    			// Execution of Pushdown Automata results in set of productions
	    			printf("Step 2. Running pushdown automata ... ");
	    			pushDownAutomata(expr,productions,output);
	    			printf("done!\n");
	    			
	    			// Apply productions to build ASA
	    			printf("Step 3. Apply productions to build an btree ... ");
	    			ada_to_asa(btree,productions);
	    			fprintf(output,"\nBtree: %s", btree);
	    			printf("done!\n");
	    			
	    			printf("Step 4. Mirroring the btree ... ");
				mirror(btree);
				btree[50] = '\0';
				fprintf(output,"\nMirrored btree: %s", btree);
				printf("done!\n");
	    			
	    			// B-tree -> Reverse Polish Notation
	    			printf("Step 5. Running postorder trasversal on btree ... ");
	    			rpn = (string) malloc(50*sizeof(string));
	    			postOrder(btree,size, 0, rpn);
	    			fprintf(output,"\nReverse polish notation: %s\n", rpn);
	    			printf("done!\n");
	    			
	    			// RPN -> PCI
	    			printf("Step 6. Convert RPN into pcode instructions ... ");
	    			Tinstruction * instructions = toInstruction(rpn, size);
	    			printf("done!\n");
	    			
	    			// Array of instructions
				printf("Step 7. Running pcode machine ... ");
				fprintf(output,"\nOutput:\n");
				fprintf(output,"%-10s %-7s %-7s %-7s %-7s %-15s %s\n","Inst","Level","Arg","Top","Counter","Base","Stack");
				pcode(instructions, stack, output);
				printf("done!\n");
				    
				free(rpn);
				// Closing File
				fclose(output);
				   
				printf("Output file generated.\n");	
			}else{
				printf("\nError when opening the output file.");
			}
		}else{
			printf("\nToo long expression");
		}
    }else{
    		printf("Insufficient params, running like this %s \"expr\"\n", argv[0]);
    }
    
    return 0;
}

void reverse (char *array, int start, int end){
	int i , j = 0;
	char aux[50];
	for(i = end-1; i >= start; i--){
		aux[j++] = array[i];
    	}
    	j = 0;
    	for (i = start; i < end; i++){
    		array[i] = aux[j++];
    	}
}

void mirror(char* array){
	int i = 1, c = 2;
        
	while(c < 32){
		reverse(array, i , i + c);
		i += c;
		c *= 2;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[50] = {""};

char pop(){
    char rtn = stack[0];
    memmove(stack,stack+1,strlen(stack));
    return rtn;
}

char* printExpr(int cursor, char *str){
	int i,j=0, len = strlen(str);
	char *new_stk = malloc(len+1);

	for (i = 0; i<len+1;i++){
		if(i == cursor){
			new_stk[i] = '.';
			new_stk[i+1] = str[j];
			i++;
			j++;
		}else{
			new_stk[i] = str[j];
			j++;
		}
	}
	return new_stk;
}

void push(char* source, char *value){
    char *p = source;
    int len = strlen(value);
    memmove(p,p-len,strlen(source)+len);
    memcpy(p,value,len);
}

char* replace(char* str, char* a, char *b){
    int len  = strlen(str);
    int lena = strlen(a), lenb = strlen(b);
    char *p = str; 
    p = strstr(p, a);
    
    if(p){
        memmove(p+lenb, p+lena,len - (p - str) + lenb);
        memcpy(p, b, lenb);
    }
    
    return str;
}

void pushDownAutomata(char word[50], int productions[50], FILE *output){
	int i = 0, j = 0, step=2 , size = strlen(word);
    
    fprintf(output,"\nPushdown Automata\n");
    fprintf(output,"%-5s %-30s %-15s %-4s %-4s\n","Step",".w","Stack","T","P");
    fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",0,printExpr(0,word),stack,"-","-");
    
	// Initial symbol
	push(stack, "E");
	fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",1,printExpr(0,word),stack,"T0","-");
	
	while(i<size){
		switch(stack[0]){
			case 'E':
				switch(word[i]){
					case '0':
					replace(stack,"E","0");
					productions[j++] = 0;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T1","P0");
					break;
					
					case '1':
					replace(stack,"E","1");
					productions[j++] = 1;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T2","P1");
					break;
					
					case 'p':
					replace(stack,"E","p");
					productions[j++] = 2;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T3","P2");
					break;
					
					case 'q':
					replace(stack,"E","q");
					productions[j++] = 3;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T4","P3");
					break;
					
					case '!':
					replace(stack,"E","!E");
					productions[j++] = 4;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T5","P4");
					break;
					
					case '(':
					replace(stack,"E","(EAEB");
					productions[j++] = 5;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T6","P5");
					break;
				}
				break;
			case 'A':
				switch(word[i]){
					case '&':
					replace(stack,"A","&");
					productions[j++] = 6;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T7","P6");
					break;
					case '|':
					replace(stack,"A","|");
					productions[j++] = 7;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T8","P7");
					break;
					case ':':
					replace(stack,"A",":");
					productions[j++] = 8;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T9","P8");
					break;
					case '-':
					replace(stack,"A","-");
					productions[j++] = 9;
					fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T10","P9");
				}
				break;
			case 'B':
				replace(stack,"B",")");
				fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T11","P10");
				break;
			default:
				pop();
				i++;
				fprintf(output,"%-5d %-30s %-15s %-4s %-4s\n",step,printExpr(i,word),stack,"T12+","-");
				break;
		}
		step++;
	}
	productions[j++] = -1;

}
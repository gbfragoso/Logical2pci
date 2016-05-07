void applyProduction(char *array, int production, int node){
    switch(production){
        case 0:
            array[node] = '0';
        break;
        case 1:
            array[node] = '1';
        break;
        case 2:
            array[node] = 'p';
        break;
        case 3:
            array[node] = 'q';
        break;
        case 5:
            array[node] = 'A';
            array[2*node+1] = 'E';
            array[2*node+2] = 'E';
        break;
        case 6:
            array[node] = '&';
        break;
        case 7:
            array[node] = '|';
        break;
        case 8:
            array[node] = ':';
        break;
        case 9:
            array[node] = '-';
        break;
    }
}

int getLastNode(int visitedNodes[]){
    int i, max = 0;
    for(i=0;i<50;i++){
        if(visitedNodes[i] > max){
            max = visitedNodes[i];
        }
    }
    return max+1;
}

void ada_to_asa(char *array, int productions[]){
    int next = 0, i, j = 0;
    int visitedNodes[50] = { -1 };
    
    for(i=0; productions[j] != -1 ; i++){
        switch(array[next]){
            case 'E':
                // The leftmost node will receive production
                applyProduction(array,productions[j++],next);
                visitedNodes[i] = next;
                
                if(array[2*next+1] == 'E'){
                    next = 2*next+1;
                }else if(array[2*next+2] == 'E'){
                    next = 2*next+2;
                }else{
                    next = visitedNodes[i-1];
                }
            break;
            case 'A':
                applyProduction(array,productions[j++],next);
                if(array[2*next+1] == 'E'){
                    next = 2*next+1;
                }else if(array[2*next+2] == 'E'){
                    next = 2*next+2;
                }else{
                    next = visitedNodes[i-2];
                }
            break;
        }
    }

    array[getLastNode(visitedNodes)] = '\0';
}
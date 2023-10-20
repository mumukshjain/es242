#include <stdio.h>
#include<stdlib.h>
int has_lost(int a[], int player) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            for (int k = 0; k < 4 - i - j; k++) {
                int a1 = (i * (11 - i) / 2) + j + 1;
                int a2 = a1 + k + 1;
                int a3 = 6 + k + (i + j) * (9 - i - j) / 2;
                a1 = a1 - 1;
                a2 = a2 - 1;
                a3 = a3 - 1;
                
                if (a[a1] == a[a2] && a[a2] == a[a3] && a[a3] == player) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
int isover(int a[]) {
    if (has_lost(a, 1)) {
        return 2;           //1st player has lost so 2nd wins
    }
    else if (has_lost(a, 2)) {
        return 1;           //2nd player lost so 1st wins
    }
    else {
        return 0;           //no result
    }
}

int* action(int a[], int* size) {
    int* b = malloc(15 * sizeof(int));
    int count = 0;
    for (int i = 0; i < 15; i++) {
        if (a[i] == 0) {
            b[count] = i;
            count++;
        }
    }
    *size = count;
    return b;
}

int minimax(int a[], int maximizer) {
    if (isover(a) == 1) {
        return -10;
    }
    if (isover(a) == 2) {
        return 10;
    }
    
    int* indices;
    int size;
    indices = action(a, &size);
    
    if (maximizer) {
        int bestscore = -10000;
        for (int i = 0; i < size; i++) {
            if (bestscore == 10) {
                return 10;
            }
            
            a[indices[i]] = 2;
            int score = minimax(a, 0);
            a[indices[i]] = 0;
            if (score > bestscore) {
                bestscore = score;
            }
        }
        return bestscore;
    }
    else {
        int bestscore = 100000;
        for (int i = 0; i < size; i++) {
            if (bestscore == -10) {
                return -10;
            }
            a[indices[i]] = 1;
            int score = minimax(a, 1);
            a[indices[i]] = 0;
            if (score < bestscore) {
                bestscore = score;
            }
        }
        return bestscore;
    }
}

int bestmove(int a[]) {
    int bestmov = -1;
    int bestscore = -1000;
    int* indices;
    int size;
    indices = action(a, &size);
    
    for (int i = 0; i < size; i++) {
        a[indices[i]] = 2;
        int score = minimax(a, 1);
        a[indices[i]] = 0;
        if (score > bestscore) {
            bestscore = score;
            bestmov = indices[i];
        }
    }
    
    return bestmov;
}

void print_board(int a[])
{
    for (int i = 0; i < 15; ++i) {
        switch (a[i]) {
        case 0: printf("0  "); break;
        case 1: printf("R  "); break;
        case 2: printf("B  "); break;
        }
    }
}

int main() {
    int a[15] = {0};
    char turn;
    printf("Choose your colour(R/B): ");
    scanf("%c", &turn);
    while(1){
        if(turn!='R'&&turn!='B'){
            printf("Wrong input. \n");
            printf("Choose your colour(R/B): ");
            scanf("%c", &turn);
        }
        else{
            break;
        }
    }
    if(turn=='B'){
        int comp_mov = 0;
        a[comp_mov] = 2;
        print_board(a);
        printf("\n");
    }
    while (isover(a) == 0) {
        int hum_mov;
        printf("enter: ");
        scanf("%d", &hum_mov);
        while(1){
            if(hum_mov>14){
                printf("No such index \n");
                printf("enter: ");
                scanf("%d", &hum_mov);
                continue;
            }
            else if(a[hum_mov]!=0){
                printf("This edge is already coloured. Choose a diff edge \n");
                printf("enter: ");
                scanf("%d", &hum_mov);
                continue;
            }
            else{
                break;
            }
        }
        a[hum_mov] = 1;
        print_board(a);
        printf("\n");
        
        if (isover(a) == 2) {
            break;
        }
        
        int comp_mov = bestmove(a);
        a[comp_mov] = 2;
        print_board(a);
        printf("\n");
    }
    
    printf("%d\n", isover(a));
    if (isover(a)==2){
        printf("Comp won!!");
    }
    if (isover(a)==1){
        printf("human won!!");
    }
    
    return 0;
}
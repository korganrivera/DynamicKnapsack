/*
    Knapsack solver, using dynamic programming this time.
    Given the limit of weight you can carry, and a list
    of items that have different value and weight, what's
    the most valuable combination of items you can choose
    to get the most value under your weight limit?
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ITEMS 20
#define MAXWEIGHT 100

typedef struct _item {
    unsigned weight;
    double value;
}item;

int main(void){

    item items[ITEMS];
    double array[ITEMS][MAXWEIGHT + 1];
    double pickvalue, totalvalue;
    unsigned totalweight;
    int i, j;

    srand(time(NULL));

    // Give items random values.
    puts("# | WEIGHT | VALUE");
    for(i = 0; i < ITEMS; i++){
        items[i].weight = rand() % MAXWEIGHT + 1;
        items[i].value  = 1 + (double)(rand() % 100) / ((double)(rand() % 10) + 1);
        printf("%-3i %-8u %5.2lf\n", i, items[i].weight, items[i].value);
    }

    printf("\nMax weight you can carry: %u.\n", MAXWEIGHT);

    // Set first column to zeroes.
    for(i = 0; i < ITEMS; i++) array[i][0] = 0;

    // Set first row.
    for(i = 1; i <= MAXWEIGHT; i++) {
        if(items[0].weight <= i) array[0][i] = items[0].value;
        else array[0][i] = 0;
    }

    // The rest.
    for(i = 1; i < ITEMS; i++){
        for(j = 1; j <= MAXWEIGHT; j++){
            if(items[i].weight <= j) {
                pickvalue = items[i].value + array[i - 1][j - items[i].weight];
                if(pickvalue > array[i - 1][j]) array[i][j] = pickvalue;
                else array[i][j] = array[i - 1][j];
            }
            else array[i][j] = array[i - 1][j];
        }
    }

    // Figure the backtrack.
    totalvalue = totalweight = 0;
    i = ITEMS - 1;
    j = MAXWEIGHT;
    printf("You should pack these items:");
    while(i >= 0 && j > 0){
        if(!array[i][j]) break;
        if(array[i][j] == array[i - 1][j]) i--;
        else{
            printf(" %u", i);
            totalvalue  += items[i].value;
            totalweight += items[i].weight;
            j -= items[i].weight;
            i--;
        }
    }
    printf("\ntotal weight: %u, total value: %.2f.\n", totalweight, totalvalue);
}

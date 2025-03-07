#include <stdio.h>
#include <stdlib.h>

// find maximum of two number
int max(int, int);
// an knapsack implementation
int knapsack(int*, int*, int**, int, int);
// print a table
void print_table(int**, int*, int*, int, int);

// find which item have to pick to satisfy best values
/*** UNFORTUNATELY THIS FUNCTION ONLY WORK WITH SAMPLE DATA, I WILL FIGURE IT OUT LATER ***/
void find_items(int*, int**, int*, int, int);

int main(void){
    /* sample data 
    int p[] = {6, 5, 8, 9, 6, 7, 3};
    int w[] = {2, 3, 6, 7, 5, 9, 4};
    int n = 7;
    int c = 9;
    */

    // values of picking items
    int p[] = {2, 15, 15, 14, 8, 1, 20};
    // weight of picking items
    int w[] = {4, 10, 6, 9, 8, 9, 8};
    // capacity of the sack
    int c = 19;
    // number of items
    int n = 7; 

    // result table 
    int **result = (int **) malloc(sizeof(int*) * (n)); // 0 -> (n-1)
    for (int i=0; i<n; ++i)
        result[i] = (int *) malloc(sizeof(int) * (c+1)); // 0 -> c

    // best value after knapsacking
    int best_value = knapsack(p, w, result, n, c);

    print_table(result, p, w, n, c); // main stuff end here

    /*
    // to store 0/1 values 
    int to_pick[n];
    find_items(to_pick, result, w, n, c);
    for (int* i = to_pick; i<to_pick+n; ++i){
        printf("%d ", *i);
    }
    printf("\n");
    */

    // printf("%d\n", best_value);    

    // display result
    
    // I like spaghetty
    for (int i=0; i<n; ++i)
        free(result[i]);
    free(result); 
    return 0;
}
int knapsack(int *p, int *w, int **result, int n, int c){
    for (int i=0; i<n; ++i){
        for (int j=0; j<=c; ++j){
            // to space for the sack
            if ( j == 0 ){
                result[i][j] = 0;
            }
            // check if item i fit in capacity
            else if ( w[i] <= j ){
                // only one item that fit can be pick 
                if ( i == 0 )
                    result[i][j] = p[i];
                else {
                    // compare existing values to new values if this item were added
                    // max ( v[i-1, j], v[i-1, j-w[i]] + p[i] )
                    result[i][j] = max(result[i-1][j], result[i-1][j-w[i]] + p[i]);
                }
            }
            // if item i not fit the values still same
            else {
                // no items can be picked since can not pick the first item
                if ( i == 0 ){
                    result[i][j] = 0;
                }
                // result remains same as above
                else{
                    result[i][j] = result[i-1][j];
                }
            }
        }
    }
    return result[n-1][c];
}
int max(int a, int b){
    return (a>b)? a:b;
}

void find_items(int *solution, int **k, int *w, int n, int m){
    int i=n-1;
    int j=m;
    while (i>=0 && j>0){
        // check if the solution does not come from picking this item 
        if (i-1 >= 0 && k[i][j] == k[i-1][j]){
            // not picked this item
            solution[i] = 0;
            // jump to higher row
            --i;
        }
        // if the solution come from picking this item
        else{
            // pick the items
            solution[i] = 1;
            // jump to higher row
            --i;
            // j jump to remaining space
            // by reducing j by weight of picked item
            j = j-w[i];
        }
    }
        
}
// litle bit messy here
void print_table(int **table, int *p, int *w, int n, int m){
    printf("n=%d, C=%d\n", n,m);
    printf("P: ");
    for (int* i=p; i<p+n; ++i){
        printf("%d, ", *i);
    }
    printf("\nW: ");
    for (int* i=w; i<w+n; ++i){
        printf("%d, ", *i);
    }
    printf("\n\n");
    printf("  ");
    for (int i=0; i<=m; ++i)
        printf("%d ", i);
    printf("\n");
    printf("  ");
    for (int i=0; i<=m; ++i)
        printf("0,");
    printf("\n");
    for (int i=0; i<n; ++i){
        printf("%d ", i);
        for (int j=0; j<=m; ++j){
            printf("%d,", table[i][j]);
        }
        printf("\b\b\n");
    }
}


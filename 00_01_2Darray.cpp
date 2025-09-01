#include <stdio.h>  

int main() {
    int N[10][10];  
    int max_row, max_col;     
    int i, j;                 
    
    printf("Enter number of rows: ");
    scanf("%d", &max_row);
    printf("Enter number of columns: ");
    scanf("%d", &max_col);
    
    // Validate dimensions to prevent overflow
    if (max_row > 10 || max_col > 10 || max_row <= 0 || max_col <= 0) {
        printf("Invalid dimensions.\n");
        return 1;  // Exit with error
    }
    
    // Initialize array to zero
    for (i = 0; i < max_row; i++) {
        for (j = 0; j < max_col; j++) {
            N[i][j] = 0;  // Set each element to zero
        }
    }
    
    for (i = 0; i < max_row; i++) {
        for (j = 0; j < max_col; j++) {
            int new_value;  // Unique variable name for input
            
            printf("Enter value for position [%d][%d]: ", i, j);
            scanf("%d", &new_value);
            
            N[i][j] = new_value;  // Insert value
            printf("Value %d placed at [%d][%d].\n", new_value, i, j);
        }
    }
    
//display:
    printf("\nFinal 2D Array Values:\n");
    for (i = 0; i < max_row; i++) {
        for (j = 0; j < max_col; j++) {
            printf("%d ", N[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}



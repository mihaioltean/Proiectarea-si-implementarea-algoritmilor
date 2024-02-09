// 11. Debt payment
// Author: Mihai Oltean, email: mihai.oltean@gmail.com, website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Source code: https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// version 2024.02.09.0
// ----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ----------------------------------------------------------------
#define MaxN 1000
// ----------------------------------------------------------------
int read_from_file(const char* file_name, unsigned int *n, unsigned int *debt)
{
    FILE* f = fopen(file_name, "r");
    if (!f)
      return 0;

    fscanf(f, "%u", n);
    for (int i = 0; i < *n; i++)  
        fscanf(f, "%u", &debt[i]);
    fclose(f);
    return 1;
}
// ----------------------------------------------------------------
void dynamic_programming_computations(unsigned int n, unsigned int* debt, 
    unsigned int *dp_positions, unsigned int *max_paid_debt, unsigned int *max_position)
{
    long dp_array[MaxN]; // vector where DP solutions are computed
    dp_array[0] = debt[0]; 
    dp_positions[0] = INT32_MAX; // marker for no previous jump

    for (int i = 1; i < n; i++){
        *max_paid_debt = 0;
        for (int j = 0; j < i - 1; j++) 
            if (*max_paid_debt < dp_array[j]){ 
                *max_paid_debt = dp_array[j]; 
                *max_position = j; 
            }
        if (*max_paid_debt != 0){ 
            dp_array[i] = *max_paid_debt + debt[i]; 
            dp_positions[i] = *max_position;
        }
        else{
            dp_array[i] = debt[i];
            dp_positions[i] = INT32_MAX;
        }
    }
    *max_paid_debt = dp_array[0];
    *max_position = 0;
    for (int i = 1; i < n; i++)
        if (dp_array[i] > *max_paid_debt) { 
            *max_paid_debt = dp_array[i];
            *max_position = i;
    }
}
// ----------------------------------------------------------------
void recreate_solution(FILE* f, unsigned int current_pos, unsigned int *dp_positions)
{
    unsigned int next_pos = dp_positions[current_pos];
    if (next_pos != INT32_MAX) // halt marker
        recreate_solution(f, next_pos, dp_positions);
    fprintf(f, "%u ", current_pos);
}
// ----------------------------------------------------------------
int write_solution_to_file(const char* file_name, unsigned int *dp_positions, 
    unsigned int max, unsigned int max_position)
{
	  FILE* f = fopen(file_name, "w");

	  if (!f)
		    return 0;

    fprintf(f, "%u\n", max); // maximal sum

    recreate_solution(f, max_position, dp_positions);

   	fclose(f);

    return 1;
}
// ----------------------------------------------------------------
int main(void)
{
    unsigned int n;
    unsigned int debt[MaxN];
  
// set input and output from file name
    char file_name_input[1000];
    strcpy(file_name_input, "test1.in");
    char file_name_output[1000];
    strcpy(file_name_output, "test1.out");

// read input from file
    if (!read_from_file(file_name_input, &n, debt)){
		    printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name_input);
		    printf("Press Enter.");
		    getchar();
		    return 1;
	  }

    unsigned int dp_positions[MaxN];

    unsigned int max_paid_debt;
    unsigned int max_position; // position of the max value in the computation array
    dynamic_programming_computations(n, debt, dp_positions, &max_paid_debt, &max_position);

// save solution to file
	if (!write_solution_to_file(file_name_output, dp_positions, max_paid_debt, max_position)) {
	    printf("Cannot write to output file (%s). Please specify the correct filename and path.\n", file_name_output);
		printf("Press Enter.");
		getchar();
		return 1;
	}

	printf("Done.\nResults have been written to %s.\nPress Enter.\n", file_name_output);

    getchar();

    return 0;
}
// ----------------------------------------------------------------
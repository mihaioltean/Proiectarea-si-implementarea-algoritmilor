// 7.1. Overlapped segments
// Author: Mihai Oltean, email: mihai.oltean@gmail.com, website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Source code: https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// version 2024.02.07.0
// ----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// ----------------------------------------------------------------
#define MaxN 1000
// ----------------------------------------------------------------
struct t_segment{ 
  unsigned int start, end;
};
// ----------------------------------------------------------------
int read_file(const char* file_name, unsigned int *n, struct t_segment *a)
{
    FILE* f = fopen(file_name, "r");
    if (!f)
      return 0;

    fscanf(f, "%d", n);
    for (int i = *n - 1; i >= 0; i--)
        fscanf(f, "%u%u", &a[i].start, &a[i].end);
      
    fclose(f);

    return 1;
}
// ----------------------------------------------------------------
int intersect(int g, int h, struct t_segment *a)
{
    return (a[g].end >= a[h].start);
}
// ----------------------------------------------------------------
unsigned int dynamic_programming_computations(unsigned int n, struct t_segment *a)
{
    unsigned int c[MaxN];
    for (int i = n - 1; i >= 0; i--){
        unsigned int max = 1;
        for (int j = i + 1; j < n; j++)
            if (!intersect(i, j, a))
              if ((max == 1) || (max < 1 + c[j]))  
                max = 1 + c[j];
        c[i] = max;
    }
    return c[0];
}
// ----------------------------------------------------------------
int write_solution_to_file(const char* file_name, unsigned int max_segments)
{
	FILE* f = fopen(file_name, "w");

	if (!f)
		return 0;

    fprintf(f, "%u", max_segments);

    fclose(f);

    return 1;
}
// ----------------------------------------------------------------
int main(void)
{ 
    unsigned int n;     
    struct t_segment segments[MaxN];
  
// set input and output from file name
	char file_name_input[1000];
	strcpy(file_name_input, "test1.in");
	char file_name_output[1000];
	strcpy(file_name_output, "test1.out");

// read input data
    if (!read_file(file_name_input, &n, segments)){
        printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name_input);
        printf("Press Enter.");
        getchar();
        return 1;
    }
// computations
    unsigned int max_segments = dynamic_programming_computations(n, segments);

// write solution to file
    if (!write_solution_to_file(file_name_output, max_segments)){
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
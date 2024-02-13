// 12. Move robot
// Author: Mihai Oltean, email: mihai.oltean@gmail.com, website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Source code: https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// version 2024.02.13.0
// ----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ----------------------------------------------------------------
#define MaxN 6
// ----------------------------------------------------------------
int read_from_file(const char* file_name, int *n, int *m, 
  int *robot_in_row, int *robot_in_col, int *robot_out_row, int *robot_out_col, 
  int labirynth[MaxN][MaxN])
{
	// assume file is OK
	FILE*f = fopen(file_name, "r");

  	if (!f)
	  	return 0;

    fscanf(f, "%d%d", n, m);
    fscanf(f, "%d%d", robot_in_row, robot_in_col);
    fscanf(f, "%d%d", robot_out_row, robot_out_col);
    
    for (int i = 0; i < *n; i++) 
      for (int j = 0; j < *m; j++)
          fscanf(f, "%d", &labirynth[i][j]);
    fclose(f);

    return 1;
}
// ----------------------------------------------------------------
int dynamic_programming_computations(int n, int m, 
  int robot_in_row, int robot_in_col, int robot_out_row, int robot_out_col, 
  int labirynth[MaxN][MaxN])
{
    int c[MaxN][MaxN];

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
          c[i][j] = -1;

    int k = 1; 
    c[robot_in_row][robot_in_col] = 0;

    while (c[robot_out_row][robot_out_col] == -1){
        for (int i = 0; i < n; i++)
          for (int j = 0; j < m; j++)
              if (labirynth[i][j] == 0){ // empty position
                if (c[i][j] == -1) 
                  if (
                    (i > 0) && (c[i - 1][j] == k - 1) ||
                    (i + 1 < n) && (c[i + 1][j] == k - 1) ||
                    (j > 0) && (c[i][j - 1] == k - 1) ||
                    (j + 1 < m) && (c[i][j + 1] == k - 1)
                    )
                  c[i][j] = k;
              }
              else // wall
                if (k > 1)
                    if (c[i][j] == -1)
                      if (
                          (i > 0) && (c[i - 1][j] == k - 2) ||
                          (i + 1 < n) && (c[i + 1][j] == k - 2) ||
                          (j > 0) && (c[i][j - 1] == k - 2) ||
                          (j + 1 < m) && (c[i][j + 1] == k - 2)
                      )
                          c[i][j] = k;
          k++;
    }
    return c[robot_out_row][robot_out_col];
}
// ----------------------------------------------------------------
int write_solution_to_file(const char* file_name, int min_time)
{
	  FILE* f = fopen(file_name, "w");

	  if (!f)
		    return 0;

    fprintf(f, "%d", min_time);
  	fclose(f);

	  return 1;
}
// ----------------------------------------------------------------
int main(void)
{ 
    int n, m;
    int labirynth[MaxN][MaxN];

    int robot_in_row, robot_in_col, robot_out_row, robot_out_col;

    char file_name_input[1000];
    strcpy(file_name_input, "test1.in");
    char file_name_output[1000];
    strcpy(file_name_output, "test1.out");

// read input from file
    if (!read_from_file(file_name_input, &n, &m, &robot_in_row, &robot_in_col, &robot_out_row, &robot_out_col, labirynth)){
      printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name_input);
      printf("Press Enter.");
      getchar();
      return 1;
    }
    
    int min_time = dynamic_programming_computations(n, m, robot_in_row, robot_in_col, robot_out_row, robot_out_col, labirynth);

// save solution to file
	  if (!write_solution_to_file(file_name_output, min_time)) {
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
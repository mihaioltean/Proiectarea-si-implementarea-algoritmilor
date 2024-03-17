// 20. Color with 4 colors
// Author: Mihai Oltean, email: mihai.oltean@gmail.com, website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Source code: https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// version 2024.02.17.0
// ----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
// ----------------------------------------------------------------
#define MaxN 200
#define LINE_SIZE MaxN * 11 + 1
// ----------------------------------------------------------------
struct t_punct {
  unsigned int  x,y;
  int color; //color:1 .. 4;
};
// ----------------------------------------------------------------
int read_from_file(const char* file_name, int *n,  struct t_punct a[MaxN], char connections[MaxN][MaxN])
{
    FILE* f = fopen(file_name, "r");
    if (!f) 
      return 0;

    fscanf(f, "%d", n);
    for (int i = 0; i < *n; i++){
        fscanf(f, "%d%d", &a[i].x, &a[i].y);
    }
    char line[LINE_SIZE];
    fgets(line, LINE_SIZE, f); // get the entire line
    // connections
    int v;

    for (int i = 0; i < *n; i++){
      for (int j = 0; j < *n; j++)
        connections[i][j] = 0;
      fgets(line, LINE_SIZE, f); // get the entire line
     
      char* val = strtok(line, " ");
      int num_read = sscanf(val, "%d", &v);

      while (num_read > 0){
          connections[i][v - 1] = 1; 
          val = strtok(NULL, " ");
          num_read = (val == NULL) ? 0 : sscanf(val, "%d" ,&v);
      }
    }
  
    fclose(f);
    return 1;
}
// ----------------------------------------------------------------
void dynamic_programming_computations(int n, struct t_punct a[MaxN], char connections[MaxN][MaxN])
{
    for (int i = 0; i < n; i++){
      char posibil[4];
      posibil[0] = posibil[1] = posibil[2] = posibil[3] = 1;
      for (int j = 0; j < i - 1; j++) 
        if (connections[i][j])
          posibil[a[j].color - 1] = 0;

      int color = 0;
      while (!posibil[color]) 
            color++; 
      a[i].color = color + 1;
    }
}
// ----------------------------------------------------------------
int write_solution_to_file(const char* file_name, struct t_punct a[MaxN], int n)
{
	FILE* f = fopen(file_name, "w");

	if (!f)
		return 0;

  for (int i = 0; i < n; i++)
    fprintf(f, "%d %d %d\n", a[i].x, a[i].y, a[i].color);

	fclose(f);

	return 1;
}
// ----------------------------------------------------------------
int main(void)
{
    struct t_punct a[MaxN];
    char connections[MaxN][MaxN];
    int n;
  
  // set input and output from file name
    char file_name_input[1000];
    strcpy(file_name_input, "test1.in");
    char file_name_output[1000];
    strcpy(file_name_output, "test1.out");

// read input from file
	if (!read_from_file(file_name_input, &n, a, connections)){
		printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name_input);
		printf("Press Enter.");
		getchar();
		return 1;
	}

  // solve
	dynamic_programming_computations(n, a, connections);
        
    // save solution to file
	if (!write_solution_to_file(file_name_output, a, n)) {
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
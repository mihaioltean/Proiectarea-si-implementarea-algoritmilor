// Farmer's problem.c
// Author: Mihai Oltean
// Email: mihai.oltean@gmail.com
// Website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Solutions in C:	https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// version 2022.01.29.1
// ----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
// ----------------------------------------------------------------
#define MaxN 1000
// ----------------------------------------------------------------
int read_from_file(const char* file_name, int *num_corn, int* distance, int *coordinates)
{
	// assume file is OK
	FILE*f = fopen(file_name, "r");

	if (!f)
		return 0;

	fscanf(f, "%d", distance);
	fscanf(f, "%d", num_corn);

	for (int i = 0; i < *num_corn; i++)
		fscanf(f, "%d", &coordinates[i]);

	fclose(f);

	return 1;
}
// ----------------------------------------------------------------
void solve(int* coordinates, int num_corn, int x, int *num_remaining_corn, int* remaining_corn)
{
	int positions[MaxN];
	int dp_array[MaxN];

	for (int i = 0; i < num_corn; i++)
		positions[i] = 0;

	dp_array[num_corn - 1]  = 1;
	int last = num_corn - 1;
	for (int i = num_corn - 2; i >= 0; i--) {
		dp_array[i] = 1;
		while (coordinates[last - 1] - coordinates[i] >= x)
			last--;
		if (coordinates[last] - coordinates[i] >= x){
			dp_array[i] = 1 + dp_array[last];
			positions[i] = last;
		}
	}
	// now restore the solution
	*num_remaining_corn = dp_array[0];
	int p = 0;
	int k = 0;
	do {
		remaining_corn[k++] = p + 1;
		p = positions[p];
	} while (p);
}
// ----------------------------------------------------------------
int save_solution_to_file(const char* file_name, int num_remaining_corn, int* remaining_corn)
{
	// assume file is OK
	FILE* f = fopen(file_name, "w");

	if (!f)
		return 0;

	fprintf(f, "%d\n", num_remaining_corn); // Number of remaining corn
	//printf("The indexes of the remaining corn are: ");
	for (int i = 0; i < num_remaining_corn; i++)
		fprintf(f, "%d ", remaining_corn[i]);
	fclose(f);

	return 1;
}
// ----------------------------------------------------------------
int main(void)
{
	int coordinates[MaxN], remaining_corn[MaxN];
	int distance;
	int num_corn;
	int num_remaining_corn;

	// read input from file
	char file_name_input[1000];
	strcpy(file_name_input, "c:/Mihai/work/Carti/Proiectarea-si-implementarea-algoritmilor/Dynamic Programming/01. Farmer's problem/test2.in");

	if (!read_from_file(file_name_input, &num_corn, &distance, coordinates)){
		printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name_input);
		printf("Press Enter.");
		getchar();
		return 1;
	}

	solve(coordinates, num_corn, distance, &num_remaining_corn, remaining_corn);
	
	char file_name_output[1000];
	strcpy(file_name_output, "c:/temp/test1.out");

	if (!save_solution_to_file(file_name_output, num_remaining_corn, remaining_corn)) {
		printf("Cannot write to output file (%s). Please specify the correct filename and path.\n", file_name_output);
		printf("Press Enter.");
		getchar();
		return 1;
	}

	printf("Done. Results have been written to file. Press Enter.");
	getchar();

	return 0;
}
// ----------------------------------------------------------------
// 01. Farmer's problem
// Author: Mihai Oltean, email: mihai.oltean@gmail.com, website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Source code: https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// version 2024.02.12.0
// ----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
// ----------------------------------------------------------------
#define MaxN 1000
// ----------------------------------------------------------------
int read_from_file(const char* file_name, int *num_corn, int distance[MaxN], int coordinates[MaxN])
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
void dynamic_programming_computations(int coordinates[MaxN], int num_corn, int x, int *num_remaining_corn, int remaining_corn[MaxN])
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
int write_solution_to_file(const char* file_name, int num_remaining_corn, int remaining_corn[MaxN])
{
	FILE* f = fopen(file_name, "w");

	if (!f)
		return 0;

	fprintf(f, "%d\n", num_remaining_corn); // Number of remaining corn
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

// set input and output from file name
	char file_name_input[1000];
	strcpy(file_name_input, "test1.in");
	char file_name_output[1000];
	strcpy(file_name_output, "test1.out");

// read input from file
	if (!read_from_file(file_name_input, &num_corn, &distance, coordinates)){
		printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name_input);
		printf("Press Enter.");
		getchar();
		return 1;
	}

// solve
	dynamic_programming_computations(coordinates, num_corn, distance, &num_remaining_corn, remaining_corn);

// save solution to file
	if (!write_solution_to_file(file_name_output, num_remaining_corn, remaining_corn)) {
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
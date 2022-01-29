// Farmer's problem.c
// Author: Mihai Oltean
// Email: mihai.oltean@gmail.com
// Website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Solutions in C:	https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// version 2022.01.29.0
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
void solve(int* coordinates, int num_corn, int x, int* dp_array, int* positions)
{
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
}
// ----------------------------------------------------------------
void restore(int p, int *positions)
{
	printf("%d ", p + 1);
	if (positions[p])
		restore(positions[p], positions);
}
// ----------------------------------------------------------------
int main(void)
{
	int coordinates[MaxN], dp_array[MaxN], positions[MaxN];
	int distance;
	int num_corn;

	char file_name[1000];
	strcpy(file_name, "c:/Mihai/work/Carti/Proiectarea-si-implementarea-algoritmilor/Dynamic Programming/1. Farmer's problem/test1.in");

	if (!read_from_file(file_name, &num_corn, &distance, coordinates)){
		printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name);
		printf("Press Enter.");
		getchar();
		return 1;
	}

	for (int i = 0; i < num_corn; i++)
		positions[i] = 0;

	solve(coordinates, num_corn, distance, dp_array, positions);

	printf("Number of remaining corn : %d\n", dp_array[0]);
	printf("The indexes of the remaining corn are: ");
	restore(0, positions);
	printf("\n");

	printf("Done. Press Enter.");
	getchar();
	return 0;
}
// ----------------------------------------------------------------
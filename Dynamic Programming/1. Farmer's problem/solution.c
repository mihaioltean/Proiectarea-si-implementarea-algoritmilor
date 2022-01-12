// Farmer's problem.c
// Author: Mihai Oltean
// Email: mihai.oltean@gmail.com
// Website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Solutions in C:	https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// ----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
// ----------------------------------------------------------------
#define MaxN 1000
// ----------------------------------------------------------------
int read_from_file(const char* file_name, int *num_corn, int* distance, int *coordinates)
{
	FILE*f = fopen(file_name, "r");

	if (!f)
		return 1;

	if (!fscanf(f, "%d", num_corn))
		return 2;

	if (*num_corn > MaxN || *num_corn < 1)
		return 3;

	if (!fscanf(f, "%d", distance))
		return 2;

	for (int i = 0; i < *num_corn; i++)
		if (!fscanf(f, "%d", &coordinates[i]))
			return 2;

	fclose(f);

	return 0;
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

	int read_result = read_from_file(file_name, &num_corn, &distance, coordinates);

	switch (read_result){
		case 1:
			printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name);
		break;
		case 2:
			printf("The file does not contain correct data.\n");
		break;
		case 3:
			printf("Data outside of the defined interval.\n");
		break;
	}

	if (read_result) {
		printf("Press Enter.");
		getchar();
		return 1;
	}

	for (int i = 0; i < num_corn; i++)
		positions[i] = 0;

	solve(coordinates, num_corn, distance, dp_array, positions);
	printf("Number of remaining corn : %d\n", dp_array[0]);
	printf("The indecses of the remaining corn are: ");
	restore(0, positions);
	printf("\n");

	printf("Press Enter.");
	getchar();
	return 0;
}
// ----------------------------------------------------------------
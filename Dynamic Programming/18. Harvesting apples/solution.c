// 18. Harvesting Apples
// Author: Mihai Oltean
// Email: mihai.oltean@gmail.com
// Website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Solutions in C:	https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// version 2022.02.06.0
// ----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// ----------------------------------------------------------------
#define MaxN 1000
// ----------------------------------------------------------------
struct t_apple {
    int weight, height;
};
// ----------------------------------------------------------------
int read_from_file(const char* file_name, int* num_apples, int* lift_height, int* harvester_max_height, struct t_apple* apples)
{
    // assume file is OK
    FILE* f = fopen(file_name, "r");

    if (!f)
        return 0;

    fscanf(f, "%d", num_apples);
    fscanf(f, "%d", lift_height);
    fscanf(f, "%d", harvester_max_height);

    for (int i = 0; i < *num_apples; i++)
        fscanf(f, "%d%d", &apples[i].weight, &apples[i].height);

    fclose(f);

    return 1;
}
// ----------------------------------------------------------------
int compare_apples(const void* a, const void* b)
{
    return (((struct t_apple*)b)->height - ((struct t_apple*)a)->height);
}
// ----------------------------------------------------------------
void restore_solution(int position_harvested_apple, int *k, struct t_apple * apples, int* predecesor, int * harvested_apples)
{
    if (position_harvested_apple >= 0) {
        restore_solution(predecesor[position_harvested_apple], k, apples, predecesor, harvested_apples);
        harvested_apples[*k] = position_harvested_apple;
        (*k)++;
        //writeln('Culeg marul de greutate ', greutate[nr], ' si inaltime ', inaltime[nr]);
    }
}
// ----------------------------------------------------------------
void solve(int num_apples, struct t_apple* apples, int lift_height, int harvester_max_height,
            int* max_harvested_weight, int* harvested_apples, int* num_harvested_apples)
{
    int DP_array_harvested_apples_weight[MaxN];
    int DP_array_num_harvested_apples[MaxN];
    int predecesor[MaxN];
    int max_position_harvested_apple;
    // sort descendingly by height 
    qsort(apples, num_apples, sizeof(apples[0]), compare_apples);

    *max_harvested_weight = 0;
    max_position_harvested_apple = 0;
    for (int i = 0; i < num_apples; i++) {
        DP_array_harvested_apples_weight[i] = apples[0].weight;
        DP_array_num_harvested_apples[i] = 1;
        predecesor[i] = -1;
        for (int j = 0; j < i; j++)
            if ((apples[i].height + DP_array_num_harvested_apples[j] * lift_height <= harvester_max_height) &&
                (DP_array_harvested_apples_weight[i] <= apples[i].weight + DP_array_harvested_apples_weight[j])) {
                DP_array_harvested_apples_weight[i] = DP_array_harvested_apples_weight[j] + apples[i].weight;
                DP_array_num_harvested_apples[i] = 1 + DP_array_num_harvested_apples[j];
                predecesor[i] = j;
            }
        if (DP_array_harvested_apples_weight[i] > *max_harvested_weight) {
            *max_harvested_weight = DP_array_num_harvested_apples[i];
            max_position_harvested_apple = i;
        }
    }
    *num_harvested_apples = 0;
    restore_solution(max_position_harvested_apple, num_harvested_apples, apples, predecesor, harvested_apples);
}
// ----------------------------------------------------------------
int save_solution_to_file(const char* file_name, int max_harvested_weight, int num_harvested_apples, int *harvested_apples, struct t_apple* apples)
{
    // assume file is OK
    FILE* f = fopen(file_name, "w");

    if (!f)
        return 0;

    fprintf(f, "%d\n", max_harvested_weight); // max harvested weight
    for (int i = 0; i < num_harvested_apples; i++)
        fprintf(f, "%d %d\n", apples[harvested_apples[i]].weight, apples[harvested_apples[i]].height);
    fclose(f);

    return 1;
}
// ----------------------------------------------------------------

int main(void)
{
    struct t_apple apples[MaxN];
    int num_apples, lift_height, harvester_max_height;
    int harvested_apples[MaxN];
    int max_harvested_weight;
    int num_harvested_apples;


    // read input from file
    char file_name_input[1000];
    strcpy(file_name_input, "e:/books/Proiectarea-si-implementarea-algoritmilor/Dynamic Programming/18. Harvesting apples/test1.in");

    if (!read_from_file(file_name_input, &num_apples, &lift_height, &harvester_max_height, apples)) {
        printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name_input);
        printf("Press Enter.");
        getchar();
        return 1;
    }

    solve(num_apples, apples, lift_height, harvester_max_height, &max_harvested_weight, harvested_apples, &num_harvested_apples);

    char file_name_output[1000];
    strcpy(file_name_output, "c:/temp/test1.out");

    if (!save_solution_to_file(file_name_output, max_harvested_weight, num_harvested_apples, harvested_apples, apples)) {
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
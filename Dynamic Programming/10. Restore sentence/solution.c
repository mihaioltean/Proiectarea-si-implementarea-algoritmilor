// 10. Restore sentence
// Author: Mihai Oltean, email: mihai.oltean@gmail.com, website: https://mihaioltean.github.io
// Book: Mihai Oltean, Proiectarea si implementarea algoritmilor (The design and the implementation of Algorithms), Computer Libris Agora, Cluj-Napoca, 287 pages, ISBN: 973-97534-0-x, 2000 (in romanian)
// Source code: https://github.com/mihaioltean/Proiectarea-si-implementarea-algoritmilor
// version 2024.02.12.0
// ----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ----------------------------------------------------------------
#define MaxN 100
#define MaxL 100
// ----------------------------------------------------------------
typedef char t_word[MaxL];
// ----------------------------------------------------------------
int read_from_file(const char* file_name, unsigned int *num_words, char *phrase, t_word *dictionary)
{
    FILE* f = fopen(file_name, "r");
    if (!f)
		    return 0;

    fscanf(f, "%u", num_words);
    getc(f); getc(f); // get rid of new line
    fscanf(f, "%s", phrase);
    getc(f); getc(f); // get rid of new line
   
    for (int i = 0; i < *num_words; i++){ 
        fscanf(f, "%s", dictionary[i]);
        getc(f); getc(f); // get rid of new line
    }
    fclose(f);

    return 1;
}
// ----------------------------------------------------------------
char is_word_from_dictionary(char* phrase, int start, int end, t_word *dictionary, int num_words)
{
    char single_word[MaxL];
  
    strncpy(single_word, phrase + start, end - start + 1);
    single_word[end - start + 1] = 0;
    for (int v = 0; v < num_words; v++) 
      if (strcmp(dictionary[v], single_word) == 0) 
          return 1; 
          
    return 0;
}
// ----------------------------------------------------------------
void dynamic_programming_computations(char* phrase, int phrase_length, 
      int num_words, t_word *dictionary, 
      int c[MaxN + 1], int poz[MaxN + 1])
{
    c[0] = 0;
    poz[0] = -1;
    for (int i = 0; i < phrase_length; i++){
      int min = -1; 
      poz[i + 1] = 0;
      for (int j = 0; j <= i; j++)
          if (is_word_from_dictionary(phrase, j, i, dictionary, num_words))
              if ((min == -1 || min > 1 + c[j]) && 
                  c[j] != -1){ 
                  min = 1 + c[j]; 
                  poz[i + 1] = j;
              }
      c[i + 1] = min;
    }
}
// ----------------------------------------------------------------
void restore_solution(FILE* f, unsigned int k, int *poz, char* phrase)
{
    int t;
  
    t = poz[k];
    if (t != -1){
        restore_solution(f, t, poz, phrase);
        for (int i = t; i < k; i++)
            fprintf(f, "%c", phrase[i]);
        fprintf(f, " ");
    }
}
// ----------------------------------------------------------------
int write_solution_to_file(const char* file_name, int phrase_length, char* phrase, int*c, int* poz)
{
	  FILE* f = fopen(file_name, "w");

	  if (!f)
		  return 0;

    if (c[phrase_length] == -1) 
       fprintf(f, "No solution");
    else {
        fprintf(f, "%d\n", c[phrase_length]); // minimal number of words
        // phrase este urmatoarea:
        restore_solution(f, phrase_length, poz, phrase);
      }

    fclose(f);

    return 1;
}
// ----------------------------------------------------------------
int main(void)
{ 
    t_word dictionary[MaxN];
    unsigned int num_words;
    char phrase[MaxL];
 
// set input and output from file name
    char file_name_input[1000];
	  strcpy(file_name_input, "test1.in");
	  char file_name_output[1000];
	  strcpy(file_name_output, "test1.out");

// read input from file
	if (!read_from_file(file_name_input, &num_words, phrase, dictionary)){
		printf("Cannot find input file (%s). Please specify the correct filename and path.\n", file_name_input);
		printf("Press Enter.");
		getchar();
		return 1;
	}

// solve
  int c[MaxN + 1], poz[MaxN + 1];
  int phrase_length = strlen(phrase);
  dynamic_programming_computations(phrase, phrase_length, num_words, dictionary, c, poz);

// save solution to file
	if (!write_solution_to_file(file_name_output, phrase_length, phrase, c, poz)) {
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
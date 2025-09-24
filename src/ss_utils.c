#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ss_utils.h"
#include "ss_builtin.h"

char *ss_get_cwd_name(SS_INFO ss_info) {
    int idx = (int)strlen(ss_info.abs_cwd);
    int count = 0;
    char *cwd_name = (char*)malloc(64);
    if (!cwd_name) {
        perror("ss_get_cwd_name malloc error");
        exit(EXIT_FAILURE);
    }
    while (ss_info.abs_cwd[--idx] != '/') count++;
    for (int i = 0; i < count; ++i) {
        cwd_name[i] = ss_info.abs_cwd[(idx+1)+i];
    }
    return cwd_name;
}

char *ss_read_line(void) {
    char *stdin_line = NULL;
    size_t ss_stdin_line_len = SS_STDIN_LINE_LEN;
    
    if (getline(&stdin_line, &ss_stdin_line_len, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("getline error");
            exit(EXIT_FAILURE);
        }
    }
    return stdin_line;
}

int levenshtein_distance(const char *str_1, const char *str_2) {
    const int len_1 = strlen(str_1)+1;
    const int len_2 = strlen(str_2)+1;

    int **matrix = (int**)calloc(len_1, sizeof(int*));
    if (!matrix) {
        perror("matrix allocation error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < len_1; ++i) {
        int *vec = (int*)calloc(len_2, sizeof(int));
        if (!vec) {
            perror("vector allocation error");
            exit(EXIT_FAILURE);
        }
        matrix[i] = vec;
    }

    for (int i = 0; i < len_1; ++i)
        matrix[i][0] = i;

    for (int j = 0; j < len_2; ++j)
        matrix[0][j] = j;

    for (int i = 1; i < len_1; ++i) {
        for (int j = 1; j < len_2; ++j) {
            int subcost = (str_1[i-1] == str_2[j-1]) ? 0 : 1;
            int ij_cost = MIN(matrix[i-1][j]+1, matrix[i][j-1]+1);
            ij_cost = MIN(ij_cost, matrix[i-1][j-1]+subcost);
            matrix[i][j] = ij_cost;
        }
    }

    int distance = matrix[len_1-1][len_2-1];
    
    for (int i = 0; i < len_1; ++i)
        free(matrix[i]);
    free(matrix);

    return distance;
}

int get_closest_one(const char *str) {
    if (!str) {
        fprintf(stderr, "String cannot be null.");
        exit(EXIT_FAILURE);
    }

    int idx = 0;
    int distance = 999999;
    for (int i = 0; i < SS_BUILTIN_LEN; ++i) {
        int new_distance = levenshtein_distance(str, ss_builtin[i]);
        if (new_distance < distance) {
            distance = new_distance;
            idx = i;
        }
    }
    return idx;
}

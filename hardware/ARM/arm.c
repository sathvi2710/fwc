#include <stdio.h>
#include <string.h>

int is_in_array(char arr[][20], int size, const char *item) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], item) == 0)
            return 1;
    }
    return 0;
}

int main() {
    // Arrays to simulate sets
    char not_gates[10][20];
    char or_gates[10][20];
    int not_count = 0;
    int or_count = 0;

    // Add NOT gates (avoid duplicates)
    if (!is_in_array(not_gates, not_count, "~P1")) {
        strcpy(not_gates[not_count++], "~P1");
    }

    if (!is_in_array(not_gates, not_count, "~P2")) {
        strcpy(not_gates[not_count++], "~P2");
    }

    // Add OR gates
    if (!is_in_array(or_gates, or_count, "P1 + P2")) {
        strcpy(or_gates[or_count++], "P1 + P2");
    }

    if (!is_in_array(or_gates, or_count, "c + e")) {
        strcpy(or_gates[or_count++], "c + e");
    }

    if (!is_in_array(or_gates, or_count, "b + c")) {
        strcpy(or_gates[or_count++], "b + c");
    }

    // Output
    printf("Minimum NOT gates required: %d\n", not_count);
    printf("Minimum OR gates required: %d\n", or_count);

    return 0;
}

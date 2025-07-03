#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> // For malloc and free

// Function to simulate a JK flip-flop
int jk_flipflop(int q, int j, int k) {
    if (j == 0 && k == 0) {
        return q;       // No change
    } else if (j == 0 && k == 1) {
        return 0;       // Reset
    } else if (j == 1 && k == 0) {
        return 1;       // Set
    } else if (j == 1 && k == 1) {
        return 1 - q;   // Toggle
    }
    return -1; // Should not reach here, indicates an error
}

// Function to simulate the counter
char** simulate_counter(int cycles) {
    int q1 = 0;
    int q2 = 0;
    char** states = (char**)malloc(cycles * sizeof(char*));
    if (states == NULL) {
        perror("Failed to allocate memory for states");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < cycles; i++) {
        states[i] = (char*)malloc(3 * sizeof(char)); // 2 chars for Q1Q2 + null terminator
        if (states[i] == NULL) {
            perror("Failed to allocate memory for state string");
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(states[j]);
            }
            free(states);
            exit(EXIT_FAILURE);
        }
        sprintf(states[i], "%d%d", q1, q2);

        int j1 = q2;
        int k1 = 1;
        int j2 = 1 - q1;
        int k2 = 1;

        int next_q1 = jk_flipflop(q1, j1, k1);
        int next_q2 = jk_flipflop(q2, j2, k2);

        q1 = next_q1;
        q2 = next_q2;
    }
    return states;
}

// Function to check for cyclic match
bool is_cyclic_match(char** actual, int actual_len, char** option, int option_len) {
    if (actual_len != option_len) {
        return false;
    }

    int n = actual_len;
    for (int i = 0; i < n; i++) {
        bool match = true;
        for (int j = 0; j < n; j++) {
            // Calculate the index for the rotated 'actual' sequence
            int actual_idx = (i + j) % n;
            if (strcmp(actual[actual_idx], option[j]) != 0) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

// Function to free the memory allocated for the states array
void free_states(char** states, int cycles) {
    for (int i = 0; i < cycles; i++) {
        free(states[i]);
    }
    free(states);
}

int main() {
    // Options from the question
    // Note: In C, we need to manage 2D arrays of strings more explicitly.
    // For simplicity, we'll hardcode them directly where used, or create
    // helper functions if this were a larger application.
    // For this specific problem, let's create char arrays.

    // Option A
    char* optionA[] = {"11", "10", "00", "11", "10", "00"};
    int lenA = sizeof(optionA) / sizeof(optionA[0]);

    // Option B
    char* optionB[] = {"01", "10", "11", "00", "01", "10"};
    int lenB = sizeof(optionB) / sizeof(optionB[0]);

    // Option C
    char* optionC[] = {"00", "11", "01", "10", "00", "11"};
    int lenC = sizeof(optionC) / sizeof(optionC[0]);

    // Option D
    char* optionD[] = {"01", "10", "00", "01", "10", "00"};
    int lenD = sizeof(optionD) / sizeof(optionD[0]);

    // Simulate actual output
    int cycles = 6;
    char** actual_output = simulate_counter(cycles);

    // Print simulated output
    printf("Simulated State Sequence (Q1 Q2):\n");
    for (int i = 0; i < cycles; i++) {
        printf("%s", actual_output[i]);
        if (i < cycles - 1) {
            printf(" -> ");
        }
    }
    printf("\n");

    // Compare with options (cyclic match)
    printf("\nChecking options:\n");
    char* correct_option_key = NULL;

    // Option A check
    bool matchA = is_cyclic_match(actual_output, cycles, optionA, lenA);
    printf("Option A: ");
    for (int i = 0; i < lenA; i++) {
        printf("%s", optionA[i]);
        if (i < lenA - 1) {
            printf(" -> ");
        }
    }
    printf(" %s\n", matchA ? "✅" : "❌");
    if (matchA) {
        correct_option_key = "A";
    }

    // Option B check
    bool matchB = is_cyclic_match(actual_output, cycles, optionB, lenB);
    printf("Option B: ");
    for (int i = 0; i < lenB; i++) {
        printf("%s", optionB[i]);
        if (i < lenB - 1) {
            printf(" -> ");
        }
    }
    printf(" %s\n", matchB ? "✅" : "❌");
    if (matchB) {
        correct_option_key = "B";
    }

    // Option C check
    bool matchC = is_cyclic_match(actual_output, cycles, optionC, lenC);
    printf("Option C: ");
    for (int i = 0; i < lenC; i++) {
        printf("%s", optionC[i]);
        if (i < lenC - 1) {
            printf(" -> ");
        }
    }
    printf(" %s\n", matchC ? "✅" : "❌");
    if (matchC) {
        correct_option_key = "C";
    }

    // Option D check
    bool matchD = is_cyclic_match(actual_output, cycles, optionD, lenD);
    printf("Option D: ");
    for (int i = 0; i < lenD; i++) {
        printf("%s", optionD[i]);
        if (i < lenD - 1) {
            printf(" -> ");
        }
    }
    printf(" %s\n", matchD ? "✅" : "❌");
    if (matchD) {
        correct_option_key = "D";
    }

    // Show correct answer
    if (correct_option_key != NULL) {
        printf("\n✅ Correct Option: (%s)\n", correct_option_key);
    } else {
        printf("\n❌ No option matches cyclically.\n");
    }

    // Free allocated memory
    free_states(actual_output, cycles);

    return 0;
}

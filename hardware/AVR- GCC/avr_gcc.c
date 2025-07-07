#include <stdio.h>

int main() {
    int P1, P2, g;

    printf("P1 P2 | g\n");
    for (P1 = 0; P1 <= 1; P1++) {
        for (P2 = 0; P2 <= 1; P2++) {
            // Logic: g = P1 OR P2
            g = P1 || P2;
            printf("%d  %d  | %d\n", P1, P2, g);
        }
    }

    return 0;
}

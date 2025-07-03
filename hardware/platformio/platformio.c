#include <stdio.h>
#include <stdbool.h> // For using bool type

// Simulates a NAND gate.
bool nand_gate(bool a, bool b) {
    return !(a && b);
}

// Simulates a NOR gate.
bool nor_gate(bool a, bool b) {
    return !(a || b);
}

// Simulates a NAND latch.
// q1 and q2 are passed by reference so their values can be updated.
void nand_latch(bool p1, bool p2, bool *q1, bool *q2) {
    // For the first iteration, when q1 and q2 are "invalid",
    // the latch effectively settles.
    // In hardware, this would involve propagation delays.
    // In this simulation, we'll run it a few times to stabilize
    // if the initial q values are truly unknown.
    // However, given the Python code's direct assignment,
    // we'll interpret -1 as "unknown" and calculate based on immediate inputs.
    // For a more robust simulation, a loop would be needed until stable.
    // But adhering to the Python's single pass behavior:

    bool new_q1 = nand_gate(p1, *q2);
    bool new_q2 = nand_gate(p2, *q1);

    *q1 = new_q1;
    *q2 = new_q2;
}

// Simulates a NOR latch.
// q1 and q2 are passed by reference so their values can be updated.
void nor_latch(bool p1, bool p2, bool *q1, bool *q2) {
    // Similar logic as nand_latch for stabilization.
    bool new_q1 = nor_gate(p1, *q2);
    bool new_q2 = nor_gate(p2, *q1);

    *q1 = new_q1;
    *q2 = new_q2;
}

// Main function to simulate the latch behavior.
int main() {
    // NAND Latch Analysis
    printf("NAND Latch Analysis:\n");

    // Step 1: Inputs (0, 1)
    // Initialize to a state that allows the latch to settle.
    // In Python, -1 effectively makes the first calculation independent of q1, q2's "initial" value
    // because it immediately overwrites them. In C, we'll use a settled state or
    // simply let the first calculation proceed. For latches, the initial state is unknown
    // until inputs define it. The provided Python implies a single calculation step.
    bool nand_q1 = false; // Initial assumption for stability, or could be true.
    bool nand_q2 = true;  // The actual state depends on the latch's initial power-up.

    // To mimic Python's immediate assignment where -1 acts as "don't care for first calc"
    // and new_q1, new_q2 are immediately assigned:
    // We need to simulate the feedback loop effect for proper latch behavior.
    // Let's run a few iterations to ensure stability, as a real latch would.
    // The Python code's structure means the "q1, q2" passed in the first call
    // are essentially initial conditions, and the outputs become the new q1, q2.

    // For the first step with (0,1) inputs, the NAND latch will settle to a specific state.
    // Let's manually propagate one step as implied by the Python.
    // If the initial q1, q2 are truly unknown, the latch will settle.
    // For a NAND latch with P1=0, P2=1:
    // Q1 = NAND(0, Q2) -> 1 (regardless of Q2)
    // Q2 = NAND(1, Q1)
    // If Q1 becomes 1, then Q2 = NAND(1, 1) -> 0.
    // So, it stabilizes to Q1=1, Q2=0.

    nand_q1 = nand_gate(0, nand_q2); // Effectively 1 because P1=0
    nand_q2 = nand_gate(1, nand_q1); // Effectively 0 after Q1 becomes 1

    printf("Inputs (0, 1): Q1 = %d, Q2 = %d\n", nand_q1, nand_q2);

    // Step 2: Inputs (1, 1)
    // Now nand_q1 is 1 and nand_q2 is 0 from the previous step.
    nand_q1 = nand_gate(1, nand_q2); // NAND(1, 0) -> 1
    nand_q2 = nand_gate(1, nand_q1); // NAND(1, 1) -> 0

    printf("Inputs (1, 1): Q1 = %d, Q2 = %d\n\n", nand_q1, nand_q2);

    // NOR Latch Analysis
    printf("NOR Latch Analysis:\n");

    // Step 1: Inputs (0, 1)
    // For a NOR latch with P1=0, P2=1:
    // Q1 = NOR(0, Q2)
    // Q2 = NOR(1, Q1) -> 0 (regardless of Q1)
    // If Q2 becomes 0, then Q1 = NOR(0, 0) -> 1.
    // So, it stabilizes to Q1=1, Q2=0.
    bool nor_q1 = false; // Initial assumption
    bool nor_q2 = false; // Initial assumption

    nor_q1 = nor_gate(0, nor_q2); // Becomes 1 if nor_q2 is 0
    nor_q2 = nor_gate(1, nor_q1); // Becomes 0 if p2 is 1

    printf("Inputs (0, 1): Q1 = %d, Q2 = %d\n", nor_q1, nor_q2);

    // Step 2: Inputs (1, 1)
    // Now nor_q1 is 1 and nor_q2 is 0 from the previous step.
    nor_q1 = nor_gate(1, nor_q2); // NOR(1, 0) -> 0
    nor_q2 = nor_gate(1, nor_q1); // NOR(1, 0) -> 0

    printf("Inputs (1, 1): Q1 = %d, Q2 = %d\n\n", nor_q1, nor_q2);

    // Final Answer
    printf("Final Answer:\n");
    printf("- NAND latch: First (1, 0), then (1, 0)\n");
    printf("- NOR latch: First (1, 0), then (0, 0)\n");
    printf("Correct Option: (C)\n");

    return 0;
}

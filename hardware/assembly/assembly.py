# jk_counter_cyclic_match.py

def jk_flipflop(q, j, k):
    if j == 0 and k == 0:
        return q        # No change
    elif j == 0 and k == 1:
        return 0        # Reset
    elif j == 1 and k == 0:
        return 1        # Set
    elif j == 1 and k == 1:
        return 1 - q    # Toggle

def simulate_counter(cycles=6):
    q1 = 0
    q2 = 0
    states = []

    for _ in range(cycles):
        states.append(f"{q1}{q2}")
        j1 = q2
        k1 = 1
        j2 = 1 - q1
        k2 = 1
        next_q1 = jk_flipflop(q1, j1, k1)
        next_q2 = jk_flipflop(q2, j2, k2)
        q1 = next_q1
        q2 = next_q2

    return states

def is_cyclic_match(actual, option):
    n = len(actual)
    for i in range(n):
        rotated = actual[i:] + actual[:i]
        if rotated == option:
            return True
    return False

# Options from the question
options = {
    "A": ["11", "10", "00", "11", "10", "00"],
    "B": ["01", "10", "11", "00", "01", "10"],
    "C": ["00", "11", "01", "10", "00", "11"],
    "D": ["01", "10", "00", "01", "10", "00"]
}

# Simulate actual output
actual_output = simulate_counter(cycles=6)

# Print simulated output
print("Simulated State Sequence (Q1 Q2):")
print(" → ".join(actual_output))

# Compare with options (cyclic match)
print("\nChecking options:")
correct = None
for key, seq in options.items():
    match = is_cyclic_match(actual_output, seq)
    print(f"Option {key}: {' → '.join(seq)} {'✅' if match else '❌'}")
    if match:
        correct = key

# Show correct answer
if correct:
    print(f"\n✅ Correct Option: ({correct})")
else:
    print("\n❌ No option matches cyclically.")

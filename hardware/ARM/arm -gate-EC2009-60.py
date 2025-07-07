#gate question EC2009-60
# Define which segments need NOT or OR logic (based on logic circuit diagram or MCQ options)

# Gates used in expressions (simplified and reused form)
used_not_gates = set()
used_or_gates = set()

# Expressions used (based on actual segment driver logic)
# Example: Let's assume g = P1 + P2 (as found in Q59)
#          d = c + e (OR)
#          e = b + c (OR)
# We need to count the unique NOT and OR expressions

# Add NOT expressions
used_not_gates.add("~P1")
used_not_gates.add("~P2")

# Add OR expressions (only unique ones)
used_or_gates.add("P1 + P2")  # for g
used_or_gates.add("c + e")    # for d
used_or_gates.add("b + c")    # for e

# Count unique gates
not_gate_count = len(used_not_gates)
or_gate_count = len(used_or_gates)

print("Minimum NOT gates required:", not_gate_count)
print("Minimum OR gates required:", or_gate_count)

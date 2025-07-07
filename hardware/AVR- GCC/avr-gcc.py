# gate question ec200959
# Logic gate simulation for the questionS
print("P1 P2 | g")
for P1 in [0, 1]:
    for P2 in [0, 1]:
        # Logic: g = P1 OR P2
        g = P1 or P2
        print(f"{P1}  {P2}  | {g}")


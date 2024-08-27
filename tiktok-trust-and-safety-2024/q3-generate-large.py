import random

with open("q3-long.txt", "w") as f:
    for _ in range(100_000):
        f.write(str(random.randint(0, 1)))

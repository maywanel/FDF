import random

def generate_map(width, height, max_height):
    with open("custom_map.fdf", "w") as file:
        for y in range(height):
            line = " ".join(str(random.randint(0, max_height)) for _ in range(width))
            file.write(line + "\n")

generate_map(20, 20, 10)


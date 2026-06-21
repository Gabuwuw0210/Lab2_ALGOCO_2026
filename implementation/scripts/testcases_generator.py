import random
import os

OUTPUT_DIR = "../implementation/data/inputs"

os.makedirs(OUTPUT_DIR, exist_ok=True)


def generar_caso(nombre_archivo, n, M, E, max_caps_total=700):
    ruta = os.path.join(OUTPUT_DIR, nombre_archivo)

    with open(ruta, "w") as f:
        f.write(f"{n} {M} {E}\n")

        caps_restantes = max_caps_total

        for i in range(1, n + 1):
            nombre = f"anime_{i}"
            max_posible = min(30, caps_restantes - (n - i))
            q = random.randint(1, max_posible)
            caps_restantes -= q

            bono = random.randint(0, 1000000000) # 1 < v < 10^9

            f.write(f"{nombre} {q} {bono}\n")

            for _ in range(q):
                tiempo = random.randint(1, 300) # 1 < t < 300
                energia = random.randint(1, 100) # 1 < c < 100
                satisfaccion = random.randint(1, 1000000000) # 1 < v < 10^9
                f.write(f"{tiempo} {energia} {satisfaccion}\n")


for i in range(2, 14): # Esta configuracion genera 12 testcases
    n = int(i * (30 / 13))    # 1 < n < 30
    M = int(i * (3000 / 13))  # 1 < M < 3.000
    E = int(i * (500 / 13))   # 1 < E < 500

    nombre = f"caso{i-1}.txt"
    generar_caso(nombre, n=n, M=M, E=E)

print("Casos generados correctamente.")

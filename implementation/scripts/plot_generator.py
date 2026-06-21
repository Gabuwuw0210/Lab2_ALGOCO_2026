import os
import matplotlib.pyplot as plt

DATA_DIR = "data"
MEASURE_DIR = os.path.join(DATA_DIR, "measurements")
OUTPUT_DIR = os.path.join(DATA_DIR, "outputs")
PLOT_DIR = os.path.join(DATA_DIR, "plots")

os.makedirs(PLOT_DIR, exist_ok=True)

def parse_comp_file(path):
    cases = []
    bf, dp, g1, g2 = [], [], [], []

    with open(path, "r") as f:
        for line in f:
            parts = line.strip().replace("-", "").split()

            case = parts[0]
            cases.append(case)

            values = {"BF": 0, "DP": 0, "G1": 0, "G2": 0}

            i = 1
            while i < len(parts):
                key = parts[i].replace(":", "")
                val = float(parts[i + 1])
                values[key] = val
                i += 2

            bf.append(values["BF"])
            dp.append(values["DP"])
            g1.append(values["G1"])
            g2.append(values["G2"])

    return cases, bf, dp, g1, g2


def plot_basic(x, y1, y2, y3, y4, title, filename, ylabel, log=False, y_from_zero=False):
    plt.figure(figsize=(8,5))

    plt.plot(x, y1, marker='o', label="BF")
    plt.plot(x, y2, marker='o', label="DP")
    plt.plot(x, y3, marker='o', label="G1")
    plt.plot(x, y4, marker='o', label="G2")

    plt.xlabel("Caso")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.legend()

    if log:
        plt.yscale("log")

    if y_from_zero:
        plt.ylim(bottom=0)

    plt.tight_layout()
    plt.savefig(os.path.join(PLOT_DIR, filename))
    plt.close()


# comp_datos
cases, bf, dp, g1, g2 = parse_comp_file(
    os.path.join(MEASURE_DIR, "comp_datos.txt")
)

plot_basic(
    cases, bf, dp, g1, g2,
    "Comparación de resultados",
    "comp_datos.png",
    "Satisfacción"
)

# comp_tiempo
cases_t, bf_t, dp_t, g1_t, g2_t = parse_comp_file(
    os.path.join(MEASURE_DIR, "comp_tiempo.txt")
)

x = [int(c.replace("caso", "")) for c in cases_t]

plot_basic(
    x, bf_t, dp_t, g1_t, g2_t,
    "Comparación de tiempos",
    "comp_tiempo.png",
    "Tiempo (ms)",
    log=True
)

# outputs individuales
selected = ["caso3", "caso6", "caso9", "caso12"]

for caso in selected:
    path = os.path.join(OUTPUT_DIR, f"{caso}.txt")

    bf, dp, g1, g2 = 0, 0, 0, 0

    with open(path, "r") as f:
        for line in f:
            if "BF" in line:
                bf = int(line.split(":")[1])
            elif "DP" in line:
                dp = int(line.split(":")[1])
            elif "G1" in line:
                g1 = int(line.split(":")[1])
            elif "G2" in line:
                g2 = int(line.split(":")[1])

    etiquetas = ["BF", "DP", "G1", "G2"]
    valores = [bf, dp, g1, g2]

    plt.figure(figsize=(6,4))
    plt.bar(etiquetas, valores)

    plt.title(f"Resultados {caso}")
    plt.ylabel("Satisfacción")
    plt.ylim(bottom=0)
    plt.grid(axis='y')

    plt.tight_layout()
    plt.savefig(os.path.join(PLOT_DIR, f"{caso}.png"))
    plt.close()

print("Gráficos generados")

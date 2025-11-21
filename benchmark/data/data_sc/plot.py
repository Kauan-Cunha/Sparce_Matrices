import numpy as np
import matplotlib.pyplot as plt

# -----------------------------------------------------------
# 1. Carregar CSV
# -----------------------------------------------------------
# Salve os dados acima em: dados.csv
data = np.genfromtxt("/home/kauan/unicamp/semestre_4/mc458/Sparce_Matrices/benchmark/data/hash/hash_mult_esp_cinco.csv", delimiter=",", names=True)

x = data["Num_Elementos"]
y = data["Tempo_Medio_Segundos"]

# -----------------------------------------------------------
# 2. Gráfico normal
# -----------------------------------------------------------
plt.figure(figsize=(8,5))
plt.plot(x, y, 'o-', label="Dados")
plt.xlabel("Número de Elementos")
plt.ylabel("Tempo Médio (s)")
plt.title("Mult. Matrizes hash: Tempo Médio x Número de elementos não-nulos")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()


# -----------------------------------------------------------
# 3. Ajuste logarítmico (y = a*log(x) + b)
# -----------------------------------------------------------
# logx = np.log(x)

# # Ajuste linear em log(x)
# coef = np.polyfit(logx, y, 1)  
# a, b = coef

# # Curva ajustada
# y_fit = a * logx + b

# plt.figure(figsize=(8,5))
# plt.plot(x, y, 'o', label="Dados reais")
# plt.plot(x, y_fit, '-', label=f"Fit: y = {a:.2e} * ln(x) + {b:.2e}")
# plt.xlabel("Número de Elementos")
# plt.ylabel("Tempo Médio (s)")
# plt.title("Ajuste Logarítmico")
# plt.grid(True)
# plt.legend()
# plt.tight_layout()
# plt.show()


# -----------------------------------------------------------
# 4. Escala logarítmica no eixo X
# -----------------------------------------------------------
# plt.figure(figsize=(8,5))
# plt.plot(x, y, 'o-', label="Dados")
# plt.xscale("log")
# plt.xlabel("Número de Elementos (escala log)")
# plt.ylabel("Tempo Médio (s)")
# plt.title("Tempo Médio vs Número de Elementos (Escala Log)")
# plt.grid(True, which="both")
# plt.legend()
# plt.tight_layout()
# plt.show()

import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA

# --- Carga datos ---
data = np.load("/home/maximiliano-cid/Documentos/EDA/EDA-TAREA-1/data_eda.npy")
queries = np.load("/home/maximiliano-cid/Documentos/EDA/EDA-TAREA-1/queries_eda.npy")

# --- Parámetros ---
q_idx = 0      # índice de la query a ilustrar
m = 32         # número de vecinos a mostrar

# --- Limita m al número de puntos ---
m = min(m, data.shape[0])

# --- KNN con NumPy (distancia euclidiana) ---
q = queries[q_idx]                         # (D,)
dists = np.linalg.norm(data - q, axis=1)   # (N,)
nn_idx = np.argpartition(dists, m)[:m]     # vecinos no ordenados
nn_idx = nn_idx[np.argsort(dists[nn_idx])] # vecinos ordenados por distancia

# --- Si los datos tienen más de 2 dimensiones, reducir a 2D para graficar ---
if data.shape[1] > 2:
    pca = PCA(n_components=2)
    data_2d = pca.fit_transform(data)
    q_2d = pca.transform(q.reshape(1, -1))[0]
else:
    data_2d = data
    q_2d = q

# --- Plot ---
plt.figure(figsize=(6, 6))

# todos los puntos
plt.scatter(data_2d[:, 0], data_2d[:, 1], c='lightgray', s=15, label='Dataset')

# vecinos
plt.scatter(data_2d[nn_idx, 0], data_2d[nn_idx, 1],
            c='C0', edgecolors='black', s=60, label=f'{m} vecinos')

# query
plt.scatter(q_2d[0], q_2d[1], c='red', marker='*', s=200, label=f'Query #{q_idx}')

# líneas query—vecino
for i in nn_idx:
    plt.plot([q_2d[0], data_2d[i, 0]], [q_2d[1], data_2d[i, 1]], 'k--', lw=0.8)

plt.title(f'{m} vecinos más cercanos a la query #{q_idx}')
plt.legend()
plt.tight_layout()
plt.show()

import pandas as pd
import matplotlib.pyplot as plt

# carregar dados
df = pd.read_csv("dados.csv")

# faz a figura
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

# faz o scatter em 3D
sc = ax.scatter(df['Melhor_X'], df['Melhor_Y'], df['Fitness'],
                c=df['Fitness'], cmap='viridis')

# coloca as labels
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Fitness')

# adiciona barra de cor pro fitness
plt.colorbar(sc, label='Fitness')

#adiciona titulo
plt.title('Evolução no Espaço de Busca (3D)')

plt.show()
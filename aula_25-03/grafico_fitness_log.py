import pandas as pd
import matplotlib.pyplot as plt

# carregar dados
df = pd.read_csv("dados.csv")

# cria a plot
plt.plot(df['Geracao'], df['Fitness'], marker='o')

# cria a escala em log
plt.yscale('log')

# adiciona as labels
plt.xlabel('Geração')
plt.ylabel('Fitness (log)')

#adiciona o titulo
plt.title('Evolução do Fitness (Escala Logaritmica)')

#adiciona grid
plt.grid(True)

plt.show()
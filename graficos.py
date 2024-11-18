import matplotlib.pyplot as plt
import numpy as np

# Crear la figura y subplots
fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(12, 10))
axes = [ax1, ax2, ax3, ax4]

plt.rcParams.update({
    'font.size': 10,
    'axes.grid': True,
    'grid.alpha': 0.3,
    'lines.linewidth': 2
})

wave_color = '#2E86AB'  
prob_color = '#5F00BA'  
pot_color = '#353535'  

for n in range(4):
    data = np.loadtxt(f'datos_n{n}.txt', skiprows=1)
    x = data[:, 0]
    psi = data[:, 1]
    psi2 = data[:, 2]
    V = data[:, 3]
    
    ax = axes[n]
    
    # Graficar función de onda 
    ax.plot(x, psi, color=wave_color, label='Ψ(x)', linewidth=2)
    # Graficar densidad de probabilidad
    ax.plot(x, psi2, color=prob_color, label='|Ψ(x)|²', linewidth=2)
    # Graficar potencial
    ax.plot(x, V/max(V)*max(abs(psi)), color=pot_color, linestyle='--', label='V(x) (escalado)', alpha=0.6)
    
    # Títulos y etiquetas
    ax.set_title(f'Estado Cuántico n={n}', pad=10)
    ax.grid(True, alpha=0.3)
    ax.legend(frameon=True, fancybox=True, shadow=True, fontsize=9)
    ax.set_xlabel('Posición (x)')
    ax.set_ylabel('Amplitud')
    
    # Ajustar límites y aspecto
    ax.set_xlim(min(x), max(x))
    margin = 0.1 * (max(psi) - min(psi))
    ax.set_ylim(min(psi) - margin, max(psi) + margin)

# Ajustar el espaciado entre subplots
plt.tight_layout(pad=2.0)

# Título general
fig.suptitle('Grafica de Onda del Oscilador Armónico Cuántico', fontsize=14, y=1.02)

# Guardar la figura
plt.savefig('grafica.png',  dpi=300, bbox_inches='tight')
plt.close()
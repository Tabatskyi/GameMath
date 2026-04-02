import matplotlib.pyplot as plt

data = {}
with open("data.txt", "r") as f:
    for line in f:
        parts = line.split()
        if len(parts) == 3:
            key = parts[0]
            x, y = float(parts[1]), float(parts[2])
            data[key] = (x, y)

fig, ax = plt.subplots(figsize=(10, 8))

# A -5.000000000000000 2.000000000000000
# B 5.000000000000000 4.000000000000000
# C 0.000000000000000 3.000000000000000
# D -3.000000000000000 5.000000000000000
# E 3.000000000000000 4.000000000000000
# F 1.000000000000000 8.000000000000000
# H 1.000000000000000 5.000000000000000
# J -1.000000000000000 8.000000000000000
# K -3.000000000000000 9.000000000000000
# N 2.000000000000000 8.000000000000000
# M 4.000000000000000 7.000000000000000

ax.plot([data['A'][0], data['B'][0]], [data['A'][1], data['B'][1]], 
        color='black', linewidth=3, label='Wall 1 (A-B)')
ax.plot([data['E'][0], data['F'][0]], [data['E'][1], data['F'][1]], 
        color='gray', linewidth=3, label='Wall 2 (E-F)')
ax.plot([data['H'][0], data['G'][0]], [data['H'][1], data['G'][1]],
        color='green', linewidth=3, label='Wall 3 (GH)')
ax.plot([data['J'][0], data['K'][0]], [data['J'][1], data['K'][1]],
        color='brown', linewidth=3, label='Wall 4 (J-K)')
ax.plot([data['N'][0], data['M'][0]], [data['N'][1], data['M'][1]],
        color='purple', linewidth=3, label='Wall 5 (N-M)')

points = {'A': data['A'], 'B': data['B'], 'C': data['C'], 'D': data['D'], 'E': data['E'], 'F': data['F'], 'H': data['H'], 'G': data['G'], 'J': data['J'], 'K': data['K'], 'N': data['N'], 'M': data['M']}
for name, (x, y) in points.items():
    ax.plot(x, y, 'ko')
    ax.text(x, y + 0.15, name, fontsize=12, ha='center')

if 'H1' in data:
    h1_x, h1_y = data['H1']

    ax.plot([data['S'][0], h1_x], [data['S'][1], h1_y], 'r--', linewidth=2, label='Bullet Path')
    ax.plot(h1_x, h1_y, 'ro')
    ax.text(h1_x, h1_y - 0.2, 'Hit 1', color='red', fontsize=10, ha='center')
    
    if 'N1' in data:
        n1_x, n1_y = data['N1']
        ax.quiver(h1_x, h1_y, n1_x, n1_y, color='blue', scale=15, width=0.005, label='Normal Vector')

    if 'H2' in data:
        h2_x, h2_y = data['H2']

        ax.plot([h1_x, h2_x], [h1_y, h2_y], 'r--', linewidth=2)
        ax.plot(h2_x, h2_y, 'ro')
        ax.text(h2_x, h2_y + 0.2, 'Hit 2', color='red', fontsize=10, ha='center')
        
        if 'N2' in data:
            n2_x, n2_y = data['N2']
            ax.quiver(h2_x, h2_y, n2_x, n2_y, color='blue', scale=15, width=0.005)

        if 'D2' in data:
            d2_x, d2_y = data['D2']
            end_x = h2_x + (d2_x * 2)
            end_y = h2_y + (d2_y * 2)
            ax.plot([h2_x, end_x], [h2_y, end_y], 'r-', linewidth=2)
            ax.quiver(h2_x, h2_y, d2_x, d2_y, color='red', scale=15, width=0.005)

ax.set_aspect('equal', adjustable='box')
ax.grid(True, linestyle=':', alpha=0.7)
ax.set_xlim(-10, 10)
ax.set_ylim(-10, 10)
ax.set_xlabel('X Axis')
ax.set_ylabel('Y Axis')

plt.show()
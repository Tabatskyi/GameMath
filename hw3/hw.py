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

ax.plot([data['A'][0], data['B'][0]], [data['A'][1], data['B'][1]], 
        color='black', linewidth=3, label='Wall 1 (A-B)')
ax.plot([data['B'][0], data['C'][0]], [data['B'][1], data['C'][1]], 
        color='gray', linewidth=3, label='Wall 2 (B-C)')

points = {'A': data['A'], 'B': data['B'], 'C': data['C'], 'S (Origin)': data['S']}
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
ax.set_xlim(-4, 6)
ax.set_ylim(-2, 5)
ax.set_xlabel('X Axis')
ax.set_ylabel('Y Axis')

plt.show()
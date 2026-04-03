import matplotlib.pyplot as plt

data = {1: {}, 2: {}, 3: {}, 4: {}}
with open("data.txt", "r") as f:
    for line in f:
        parts = line.split()
        if len(parts) >= 6:
            task_id = int(parts[0])
            label = parts[1]
            coords = list(map(float, parts[2:6]))
            data[task_id][label] = coords

fig = plt.figure(figsize=(12, 10))
for i in range(1, 5):
    ax = fig.add_subplot(2, 2, i, projection='3d')
    task_data = data[i]

    if not task_data:
        continue

    a_orig, b_orig = task_data['a_orig'], task_data['b_orig']
    a_res, b_res = task_data['a_res'], task_data['b_res']

    same_as_orig_a = "same as original" if a_orig == a_res else ""
    same_as_orig_b = "same as am" if a_res == b_res else ""

    ax.quiver(0, 0, 0, a_orig[0], a_orig[1], a_orig[2], color='blue', label='a and b (initial)', arrow_length_ratio=0.1)
    ax.quiver(0, 0, 0, a_res[0], a_res[1], a_res[2], color='cyan', label=f'a*m {same_as_orig_a}', arrow_length_ratio=0.1)
    ax.quiver(0, 0, 0, b_res[0], b_res[1], b_res[2], color='magenta', label=f'b*am {same_as_orig_b}', arrow_length_ratio=0.1)

    ax.set_xlim([-6, 10])
    ax.set_ylim([-6, 10])
    ax.set_zlim([-6, 15])
    ax.set_xlabel('X Axis')
    ax.set_ylabel('Y Axis')
    ax.set_zlabel('Z Axis')
    ax.set_title(f'Transformation {i}')
    ax.legend(loc='upper left')

plt.tight_layout()
plt.show()
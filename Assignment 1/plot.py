import matplotlib.pyplot as plt
import numpy as np

with open('points.txt', 'r') as f:
    lines = [line.rstrip() for line in f]

n_lines = int(lines[0])
n_intersects = int(lines[n_lines + 1])

fig1, ax = plt.subplots()
ax.set_xlim(-10, 10)
ax.set_ylim(-10, 10)
ax.set_box_aspect(1)
plt.grid()
for line in lines[1:n_lines+1]:
    x1, y1, x2, y2 = [float(x) for x in line.split()]
    plt.plot([x1, x2], [y1, y2], color = 'black')
for pts in lines[n_lines + 2:]:
    x, y = [float(x) for x in pts.split()]
    plt.plot([x], [y], linestyle = '', marker = 'o', color = 'red')
plt.show()

fig1.savefig('plot-points.png', dpi = 600)
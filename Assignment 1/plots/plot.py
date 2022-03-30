import matplotlib.pyplot as plt
import numpy as np
 
with open('points.txt', 'r') as f:
    lines = [line.rstrip() for line in f]
 
n_lines = int(lines[0])
n_intersects = int(lines[n_lines+1])
 
plt.figure()
for line in lines[1:n_lines+1]:
    x1, y1, x2, y2 = [float(x) for x in line.split()]
    plt.plot([x1, x2], [y1, y2])
 
for pts in lines[n_lines+2:]:
    x, y= [float(x) for x in pts.split()]
    plt.plot([x], [y], linestyle='', marker='x', color ='red')
 
plt.title('Lines and Intersection Points')
plt.legend(numpoints=1)
plt.xlabel('X axis')
plt.ylabel('Y axis')
plt.show()
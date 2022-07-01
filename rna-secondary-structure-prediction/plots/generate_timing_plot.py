from turtle import color
import matplotlib.pyplot as plt
 
n = range(5, 1005, 5)
t = []
 
with open(".\\plots\\timing_output.txt") as f:
    for line in f:
        t.append(float(line.split()[1]))
 
plt.plot(n, t)
plt.plot(n, [(i ** 3) / 400000 for i in n])
plt.title("A Timing Analysis of the Dynamic Programming Approach")
plt.xlabel("Length of RNA Molecule chain (n)")
plt.ylabel("Time (ms)")
plt.legend(["Actual time taken", "f(n) = n³/400000"])
plt.show()
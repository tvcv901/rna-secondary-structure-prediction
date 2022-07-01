import random

bases = ['A', 'G', 'C', 'U']

f = open('data\\timing_input.txt', 'w')
for len in range(5, 1001, 5):
    sequence = ""
    for i in range(len):
        sequence += bases[random.randint(0, 3)]
    f.write(sequence + '\n')
        
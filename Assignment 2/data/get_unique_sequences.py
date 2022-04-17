f = open('data\\input_rna_sequences.txt', 'r')
sequences = f.readlines()
f.close()

unique_sequences = set(sequences)
f = open('data\\unique_rna_sequences.txt', 'w')
for sequence in unique_sequences:
    f.write(sequence)
f.close()
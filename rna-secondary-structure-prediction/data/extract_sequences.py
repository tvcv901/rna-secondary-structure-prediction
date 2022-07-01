import numpy as np
import pandas as pd
import requests
from bs4 import BeautifulSoup
import re

df = pd.read_excel('data\\Result.xls')
ndb_ids = df.iloc[:,0]
base_url = 'http://ndbserver.rutgers.edu/service/ndb/atlas/summary?searchTarget='

rna_sequences = []

for id in ndb_ids:
    url = base_url + id
    page = requests.get(url)
    soup = BeautifulSoup(page.content, 'html.parser')
    rna_sequence = soup.find('p', {"class": "chain"})
    if re.match("^[ACGU]+$", rna_sequence.text):
        rna_sequences.append(rna_sequence.text)

unique_rna_sequences = set(rna_sequences)
f = open('data\\unique_rna_sequences.txt', 'w')
for sequence in unique_rna_sequences:
    f.write(sequence)
f.close()
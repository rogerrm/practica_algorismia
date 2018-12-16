import numpy as np

paraules = []

with open('./dades_permutacions/original.txt', 'r') as f:
	for line in f.readlines():
		paraula = line.replace('\n','')
		paraules.append(paraula)

for i in range(20):
	p = np.random.permutation(50)
	with open('./dades_permutacions/text'+str(i)+'.txt', 'w') as f:
		for j in p:
			f.write(paraules[j]+' ')
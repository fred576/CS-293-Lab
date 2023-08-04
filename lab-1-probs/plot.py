import matplotlib.pyplot as plt
import math
x = []
y = []
f = open("data.txt", "r")
for line in f.readlines():
	a, b  = line.split(' ')
	b, c = b.split('\n')
	x.append(math.log2(int(a)))
	y.append(math.log2(int(b)))

#print(x, y)
plt.scatter(x, y, s = 3)
plt.show()
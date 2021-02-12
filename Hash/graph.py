import numpy as np
import matplotlib.pyplot as plt


table_file = open('collision2.txt')
table_str = table_file.read().splitlines()

column = np.zeros(len(table_str))
collision = np.zeros(len(table_str))

for i in range(len(table_str)):
    if float(table_str[i]) != 0:
        column[i] = i
        collision[i] = float(table_str[i])
    else:
        column[i] = i
        collision[i] = None


plt.plot(column, collision, '.')
plt.title('Hash Function 2')
plt.savefig('hash2.png')
plt.close()
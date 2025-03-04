import numpy as np

a = [[3, -4],
     [2, -5]]

b = [[5/7, -4/7],
     [2/7,  -3/7]]

#c = np.matmul(a, b)
c = np.matmul(b, a)

#print(np.array(a))
#print('\n', np.array(b))
print('\n', c)
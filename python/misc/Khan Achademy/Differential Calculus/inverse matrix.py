import numpy as np
from numpy.linalg import inv

a = np.array([[1., 2.], 
              [3., 4.]])
ainv = inv(a)

#print(a)
print('\n', ainv)
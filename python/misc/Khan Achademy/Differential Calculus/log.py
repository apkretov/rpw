import matplotlib.pyplot as plt
import numpy as np
import math

def func_array(x_array):
    result = []
    for item in x_array:
        result.append(math.log(item))
    return result


colour = '#0099ff'
colour_dot = colour
dot_qty = 100
x1 = 0.1
x2 = 5
#x = math.e
x = 1

#y_dot = math.log(x)
y_dot = math.log(x) / x
x_array = np.linspace(x1, x2, num=dot_qty)
y_array_1 = func_array(x_array)
y_array_2 = y_array_1 / x_array

plt.figure(1, figsize=(8, 4))

ax1 = plt.subplot(121)
ax1.plot(x_array, y_array_1, c=colour, linewidth=4)
ax1.grid(True)
ax1.axhline(c='k')
ax1.axvline(c='k')
ax1.plot(x, y_dot, 'o', c=colour_dot, markersize=10, markeredgecolor=colour)

ax2 = plt.subplot(122)
ax2.plot(x_array, y_array_2, c=colour, linewidth=4)
ax2.grid(True)
ax2.axhline(c='k')
ax2.axvline(c='k')
ax2.plot(x, y_dot, 'o', c=colour_dot, markersize=10, markeredgecolor=colour)

print('x =', x, '\tf(x) =', y_dot)
plt.show()
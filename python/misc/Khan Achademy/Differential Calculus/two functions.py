import matplotlib.pyplot as plt
import numpy as np
import math

def func1(x):
    return math.log(x)


def func2(x):
    return x**2 * math.log(x)


def func_array(x_array, func):
    result = []
    for item in x_array:
        result.append(func(item))
    return result


#x1_1 = 0.01
x1_2 = 10
#x2_1 = 0.01
x2_2 = 2.5
x1_1 = x2_1 = 0.01
#x1_2 = x2_2 = 2.5
#x1 = 0.0000001
#x2 = -0.0000001
x1 = x2 = 2

colour = '#0099ff'
colour_dot = colour
dot_qty = 100

x_array_1 = np.linspace(x1_1, x1_2, num=dot_qty)
y_array_1 = func_array(x_array_1, func1)
x_array_2 = np.linspace(x2_1, x2_2, num=dot_qty)
y_array_2 = func_array(x_array_2, func2)
y_dot_1 = func1(x1)
y_dot_2 = func2(x2)

axs = []
f, axs = plt.subplots(2, 1, sharex=True, figsize=(5, 10))
for ax in axs:
    ax.grid(True)
    ax.axhline(c='k')
    ax.axvline(c='k')
#    ax.set_aspect('equal')

axs[0].set_title('x = ' + str(x1) + '   f(x) = ' + str(y_dot_1))
axs[0].plot(x_array_1, y_array_1, c=colour, linewidth=4)
axs[0].plot(x1, y_dot_1, 'o', c=colour_dot, markersize=10, markeredgecolor='r')

axs[1].set_title('x = ' + str(x2) + '   f(x) = ' + str(y_dot_2))
axs[1].plot(x_array_2, y_array_2, c=colour, linewidth=4)
axs[1].plot(x2, y_dot_2, 'o', c=colour_dot, markersize=10, markeredgecolor='r')
plt.show()
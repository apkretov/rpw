import matplotlib.pyplot as plt
import numpy as np
import math

legend1 = 'x**3 - 6*x**2 + x - 5'
def func1(x):
    return x**3 - 6*x**2 + x - 5


legend2 = '3 * x**2 - 12 * x'
def func2(x):
    return 3 * x**2 - 12 * x


#legend3 = '-8 * x - 1'
legend3 = 'slope'
def func3(x, x3):
#    return -8 * x - 1
    return func2(x) * (x - x3) + func1(x3)


def func_array(x_array, func):
    result = []
    for item in x_array:
        result.append(func(item))
    return result


x1_1 = x2_1 = x3_1 = -2
x1_2 = x2_2 = x3_2 = 6
x1 = x2 = x3 = 1

#colour = '#0099ff'
colour = 'g'
colour_dot = colour
dot_qty = 100

x_array_1 = np.linspace(x1_1, x1_2, num=dot_qty)
y_array_1 = func_array(x_array_1, func1)
x_array_2 = np.linspace(x2_1, x2_2, num=dot_qty)
y_array_2 = func_array(x_array_2, func2)
x_array_3 = np.linspace(x3_1, x3_2, num=dot_qty)
y_array_3 = func_array(x_array_3, func3)
y_dot_1 = func1(x1)
y_dot_2 = func2(x2)
y_dot_3 = func3(x3, x3)

f, ax = plt.subplots(figsize=(6, 6))
ax.grid(True)
ax.axhline(c='k')
ax.axvline(c='k')
#ax.set_aspect('equal')

line1, = ax.plot(x_array_1, y_array_1, linewidth=4)
ax.plot(x1, y_dot_1, 'o', c=colour_dot, markersize=10, markeredgecolor='r')

line2, = ax.plot(x_array_2, y_array_2, linewidth=4)
ax.plot(x2, y_dot_2, 'o', c=colour_dot, markersize=10, markeredgecolor='r')

line3, = ax.plot(x_array_3, y_array_3, linewidth=4)
ax.plot(x3, y_dot_3, 'o', c=colour_dot, markersize=10, markeredgecolor='r')

legend1 += '   f(' + str(x1) + ') = ' + str(y_dot_1)
legend2 += '   f(' + str(x2) + ') = ' + str(y_dot_2)
legend3 += '   f(' + str(x3) + ') = ' + str(y_dot_3)
ax.legend((line1, line2, line3), (legend1, legend2, legend3))
plt.show()
import matplotlib.pyplot as plt
import numpy as np
import math

n = 20 # The number of trials.
k_str = 'k' # The k string - the expected number of successes.
p1 = 0.5 # Success probability 1.
p2 = 0.7 # Success probability 2.

legend = lambda p : 'f(' + str(n) + ', ' + k_str + ', ' + str(p) + ') = ' + str(n) + '! / (' + k_str + '! * (' + str(n) + ' - ' + k_str + ')!) * ' + str(p) + '^' + k_str + ' * (1 - ' + str(p) + ')^(' + str(n) + ' - ' + k_str + ')'

legend1 = legend(p1)
func1 = lambda k, p : math.factorial(n) / (math.factorial(k) * math.factorial(n - k)) * math.pow(p, k) * math.pow(1 - p, n - k)

legend2 = legend(p2)    
func2 = lambda k, p: func1(k, p)

def func_array(x_array, func, p):
    result = []
    for item in x_array:
        result.append(func(item, p))
    return result


x1 = n * p1
x2 = n * p2

colour = 'g'
colour_dot = colour
dot_qty = n

x_array_1 = np.arange(dot_qty + 1)
y_array_1 = func_array(x_array_1, func1, p1)
x_array_2 = np.arange(dot_qty + 1)
y_array_2 = func_array(x_array_2, func2, p2)
y_dot_1 = func1(x1, p1)
y_dot_2 = func2(x2, p2)

f, ax = plt.subplots(figsize=(6, 6))
ax.grid(True)
ax.axhline(c='k')
ax.axvline(c='k')
#ax.set_aspect('equal')

line1, = ax.plot(x_array_1, y_array_1, 'o', linewidth=4)
ax.plot(x1, y_dot_1, 'o', c=colour_dot, markersize=10, markeredgecolor='r')

line2, = ax.plot(x_array_2, y_array_2, 'o', linewidth=4)
ax.plot(x2, y_dot_2, 'o', c=colour_dot, markersize=10, markeredgecolor='r')

legend1 += '   f(' + str(n) + ', ' + str(x1) + ', ' + str(p1) + ') = ' + str(round(y_dot_1, 2))
legend2 += '   f(' + str(n) + ', ' + str(x2) + ', ' + str(p2) + ') = ' + str(round(y_dot_2, 2))
ax.legend((line1, line2), (legend1, legend2))

font = {'fontname': 'MathJax_Math'}
plt.xlabel(k_str, fontdict=font)
plt.ylabel('Temperature', fontdict=font)
plt.title('Yearly temperature in Santiago, Chile')

plt.show()
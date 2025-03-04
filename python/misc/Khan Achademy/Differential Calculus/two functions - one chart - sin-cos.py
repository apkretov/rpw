import matplotlib.pyplot as plt
import numpy as np
import math

year_days = 365.25 # Days in a year.
max_temp_day = 7 # The maximal temperature day.
high_temp = 29 # The highest yearly temperature.
low_temp = 14 # The lowest yearly temperature.
avr_temp = (high_temp + low_temp) / 2 # The average temperature.
amplitude = (high_temp - low_temp) / 2 # The amplitude.
sought_temp = 20 # The temperature sought.

legend1 = 'f(x) = ' + str(amplitude) + ' * cos(2 * pi / ' + str(year_days) + ' * (x - ' + str(max_temp_day) + ')) + ' + str(avr_temp)
def func1(x):
    return amplitude * math.cos(2 * math.pi / year_days * (x - max_temp_day)) + avr_temp


legend2 = 'f(x) = ' + str(avr_temp)
def func2(x):
    return avr_temp


def func_array(x_array, func):
    result = []
    for item in x_array:
        result.append(func(item))
    return result


x1_1 = x2_1 = 0
x1_2 = x2_2 = year_days * 2 + max_temp_day

x1 = math.acos((sought_temp - avr_temp) / amplitude) * year_days / (2 * math.pi) + max_temp_day # The 20 Celcium degrees day.
x2 = x2_2

#colour = '#0099ff'
colour = 'g'
colour_dot = colour
dot_qty = 100

x_array_1 = np.linspace(x1_1, x1_2, num=dot_qty)
y_array_1 = func_array(x_array_1, func1)
x_array_2 = np.linspace(x2_1, x2_2, num=dot_qty)
y_array_2 = func_array(x_array_2, func2)
y_dot_1 = func1(x1)
y_dot_2 = func2(x2)

f, ax = plt.subplots(figsize=(6, 6))
ax.grid(True)
ax.axhline(c='k')
ax.axvline(c='k')
#ax.set_aspect('equal')

line1, = ax.plot(x_array_1, y_array_1, linewidth=4)
ax.plot(x1, y_dot_1, 'o', c=colour_dot, markersize=10, markeredgecolor='r')

line2, = ax.plot(x_array_2, y_array_2, '--', linewidth=4)
#ax.plot(x2, y_dot_2, 'o', c=colour_dot, markersize=10, markeredgecolor='r')

legend1 += '   f(' + str(x1) + ') = ' + str(y_dot_1)
legend2 += '   f(' + str(x2) + ') = ' + str(y_dot_2)
ax.legend((line1, line2), (legend1, legend2))

plt.xticks((max_temp_day, x1, year_days, x1_2))
plt.yticks((low_temp, sought_temp, avr_temp, high_temp))

font = {'fontname': 'MathJax_Math'}
plt.xlabel('Days', fontdict=font)
plt.ylabel('Temperature', fontdict=font)
plt.title('Yearly temperature in Santiago, Chile')

plt.show()
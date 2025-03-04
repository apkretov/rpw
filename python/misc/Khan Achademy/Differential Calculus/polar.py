import numpy as np # Scatter plot on polar axis @ https://matplotlib.org/devdocs/gallery/pie_and_polar_charts/polar_scatter.html
import matplotlib.pyplot as plt

r = 1
theta1 = 2 / 3 * np.pi
theta2 = theta1 * 20

fig = plt.figure(figsize=(6, 6))
ax = fig.add_subplot(111, projection='polar')
ax.scatter(theta1, r)
ax.scatter(theta2, r)
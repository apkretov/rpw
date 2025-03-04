# Normal (Gaussian) Distribution @ https://www.w3schools.com/python/numpy_random_normal.asp

from numpy import random # Generate a random normal distribution of size 2x3:
x = random.normal(size=(2, 3))
print(x)

from numpy import random # Generate a random normal distribution of size 2x3 with mean at 1 and standard deviation of 2
x = random.normal(loc=1, scale=2, size=(2, 3))
print(x)

from numpy import random # Visualization of Normal Distribution
import matplotlib.pyplot as plt
import seaborn as sns
#sns.distplot(random.normal(size=1000), hist=False)
sns.distplot(random.normal(size=1000))
plt.show()
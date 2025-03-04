# Understanding the Normal Distribution (with Python) @ https://towardsdatascience.com/understanding-the-normal-distribution-with-python-e70bb855b027
import numpy as np
from scipy.stats import norm
import matplotlib.pyplot as plt
import seaborn as sns
mean_height = 5.5*12
stdev_height = 1*12
target = 6*12
mean_height + np.random.normal()*stdev_height

height_surveys = np.zeros((10000,10))
for i in range(height_surveys.shape[0]):
    for j in range(height_surveys.shape[1]):
        height_surveys[i,j] = mean_height +\
                              np.random.normal()*stdev_height
print('Mean Height:', round(np.mean(height_surveys)/12,1), 'feet')
print('Standard Deviation of Height:', 
      round(np.var(height_surveys)**0.5/12,1), 'foot')

# Histogram that shows the distribution for the mean of all surveys
fig, ax = plt.subplots(figsize=(12,8))
sns.distplot(np.mean(height_surveys,axis=1), 
             kde=False, label='Height')
ax.set_xlabel("Height in Inches",fontsize=16)
ax.set_ylabel("Frequency",fontsize=16)
plt.axvline(target, color='red')
plt.legend()
plt.tight_layout()

# I picked sample number 35 at random to plot earlier
np.var(height_surveys[35])**0.5    # = 12.5

# Compare mean of all surveys with inferred distribution
fig, ax = plt.subplots(figsize=(12,8))
# Plot histogram of 10,000 sample means
sns.distplot(np.mean(height_surveys,axis=1), 
             kde=False, label='True')
# Calculate stats using single sample
sample_mean = np.mean(height_surveys[35])
sample_stdev = np.var(height_surveys[35])**0.5
# Calculate standard error
std_error = sample_stdev/(height_surveys[35].shape[0])**0.5
# Infer distribution using single sample
inferred_dist = [sample_mean + np.random.normal()*\
                 std_error for i in range(10000)]
# Plot histogram of inferred distribution
sns.distplot(inferred_dist, kde=False, 
             label='Inferred', color='red')
ax.set_xlabel("Height in Inches",fontsize=16)
ax.set_ylabel("Frequency",fontsize=16)
plt.legend()
plt.tight_layout()

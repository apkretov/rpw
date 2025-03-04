from scipy.stats import norm

ϻ =	0.78
p =	0.80
n =	675
σ =	(ϻ * (1 - ϻ) / n)**0.5
z =	(p - ϻ) / σ
print(z)

#print(norm.ppf(0.5))
print(norm.cdf(z))
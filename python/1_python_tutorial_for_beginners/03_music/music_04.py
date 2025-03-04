import pandas
from sklearn.tree import DecisionTreeClassifier
from sklearn.externals import joblib

model = joblib.load("music-recommender.joblib")
predictions = model.predictions([[21, 1]])
predictions

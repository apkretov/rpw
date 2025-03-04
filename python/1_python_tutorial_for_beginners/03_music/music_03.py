from pandas import read_csv
from sklearn.tree import DecisionTreeClassifier
from sklearn.externals import joblib

music_data = read_csv("music.csv")
X = music_data.drop(columns=["genre"])
y = music_data["genre"]

model = DecisionTreeClassifier()
model.fit(X, y)

joblib.dump(music_data, "music-recommender.joblib")

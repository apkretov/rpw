from pandas import read_csv
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split

music_data = read_csv("music.csv")
music_data

X = music_data.drop(columns=["genre"])
y = music_data["genre"]

model = DecisionTreeClassifier()
model.fit(X, y)

predictions = model.predict([ [21, 1], [22, 0] ])
predictions

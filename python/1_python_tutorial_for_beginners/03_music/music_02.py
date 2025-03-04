from pandas import read_csv
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

music_data = read_csv("music.csv")
music_data

X = music_data.drop(columns=["genre"])
y = music_data["genre"]
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2)
X_test

y_test

model = DecisionTreeClassifier()
model.fit(X, y)

predictions = model.predict(X_test)
predictions

score = accuracy_score(y_test, predictions)
#score
print(f"Score: {score}")

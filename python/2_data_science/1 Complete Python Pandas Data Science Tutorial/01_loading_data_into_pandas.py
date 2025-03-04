import pandas as pd

df = pd.read_csv('pokemon_data.csv')
print(df.head(3))
# print(df.tail(3))
# df

df_xls = pd.read_excel('pokemon_data.xlsx')
# df_xls

df_txt = pd.read_csv('pokemon_data.txt', '\t')
df_txt

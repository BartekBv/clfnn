import pandas as pd

df = pd.read_csv('Iris.csv').drop(columns=['Id'])

df_encoded = pd.get_dummies(df, columns=['Species'], dtype=float)
df_shuffled = df_encoded.sample(frac=1, random_state=42).reset_index(drop=True)

rows = len(df_shuffled)
split_index = int(rows * 0.8)

train_df = df_shuffled.iloc[:split_index]
test_df = df_shuffled.iloc[split_index:]

train_df.to_csv('iris_train.csv', header=False, index=False)
test_df.to_csv('iris_test.csv', header=False, index=False)
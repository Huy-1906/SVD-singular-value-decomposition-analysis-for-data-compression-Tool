import pandas as pd
data = pd.DataFrame([[1.2, 2.3, 3.4], [4.5, 5.6, 6.7], [7.8, 8.9, 9.0]])
data.to_csv("data.csv", index=False, header=False)

import csv
from collections import defaultdict
import pandas as pd 

rows = [
    ["timestamp", "symbol", "side", "price", "qty"],
    [1, "AAPL", "BUY", 100.0, 10],
    [2, "MSFT", "SELL", 300.0, 5],
    [3, "AAPL", "SELL", 101.0, 20],
    [4, "GOOG", "BUY", 150.0, 8],
    [5, "MSFT", "BUY", 302.0, 15],
    [6, "AAPL", "BUY", 99.0, 10],
]

with open("trades.csv", "W", newline="") as f:
    writer = csv.writer(f)
    writer.writerows(rows)
    
volume = defaultdict(int)
notional = defaultdict(float)

with open("trades.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        sym = row["symbol"]
        price = float(row["price"])
        qty = int(row["qty"])
        volume[sym] += qty 
        notional[sym] += price * qty 
        
for sym in sorted(volume):
    vwap = notional[sym] / volume[sym]
    print(sym, volume[sym], round(vwap, 2))
    
with open("summary.csv", "w", newline="") as f:
    writer = csv.writer(f) 
    writer.writerow(["symbol", "volume", "vwap"])
    for sym in sorted(volume):
        writer.writerow([sym, volume[sym], round(notional[sym] / volume[sym], 2)])
        
df = pd.read_csv("trades.csv")
df["notional"] = df["price"] * df["qty"]

summary = df.groupby("symbol").agg(
    volume=("qty", "sum"),
    notionl=("noitonal", "sum"), 
)

summary["vwap"] = (summary["notional"] / summary["volume"]).round(2)
print("--- pandas ---")
print(summary)

# ---------- 4. Common pandas one-liners ----------
print("--- extras ---")
print(df[df["side"] == "BUY"])                          # filter rows
print(summary["volume"].idxmax())                        # symbol with most volume
print(df.groupby(["symbol", "side"])["qty"].sum())       # two-key groupby
print(df.sort_values("price", ascending=False).head(2))  # top 2 by price
df["cum_qty"] = df.groupby("symbol")["qty"].cumsum()     # running total per symbol
print(df)
summary.to_csv("summary_pd.csv")    

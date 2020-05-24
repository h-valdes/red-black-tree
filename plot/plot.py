import pandas as pd
import matplotlib.pyplot as plt


insert_csv = pd.read_csv("insert-1-100000.csv", header=None)
search_csv = pd.read_csv("search-1-100000.csv", header=None)

insert_csv.columns = ["name", "iterations", "avg_case", "worst_case"]
search_csv.columns = ["name", "iterations", "avg_case", "worst_case"]

insert_avg = insert_csv.pivot(index="iterations", columns="name", values="avg_case")
fig = insert_avg.plot().get_figure()
fig.savefig("insert_avg.png")

search_avg = search_csv.pivot(index="iterations", columns="name", values="avg_case")
fig = search_avg.plot().get_figure()
fig.savefig("search_avg.png")

insert_worst = insert_csv.pivot(index="iterations", columns="name", values="worst_case")
fig = insert_worst.plot().get_figure()
fig.savefig("insert_worst.png")

search_worst = search_csv.pivot(index="iterations", columns="name", values="worst_case")
fig = search_worst.plot().get_figure()
fig.savefig("search_worst.png")

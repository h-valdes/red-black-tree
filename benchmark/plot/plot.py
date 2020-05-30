import pandas as pd
import matplotlib.pyplot as plt


insert_csv = pd.read_csv("insert-1-100000.csv", header=None)
search_csv = pd.read_csv("search-1-100000.csv", header=None)

insert_csv.columns = ["name", "nodes", "avg_case", "worst_case"]
search_csv.columns = ["name", "nodes", "avg_case", "worst_case"]

# Average time

insert_avg = insert_csv.pivot(index="nodes", columns="name", values="avg_case")
fig = insert_avg.plot(style='.-').get_figure()
fig.savefig("insert_avg.png")

search_avg = search_csv.pivot(index="nodes", columns="name", values="avg_case")
fig = search_avg.plot(style='.-').get_figure()
fig.savefig("search_avg.png")

# Worst time

insert_worst = insert_csv.pivot(index="nodes", columns="name", values="worst_case")
fig = insert_worst.plot(style='.-').get_figure()
fig.savefig("insert_worst.png")

search_worst = search_csv.pivot(index="nodes", columns="name", values="worst_case")
fig = search_worst.plot(style='.-').get_figure()
fig.savefig("search_worst.png")

# Exclude the BST from search graph

search_avg_filtered = search_avg.drop(columns="BST")
fig = search_avg_filtered.plot(style='.-').get_figure()
fig.savefig("search_avg_filtered.png")

search_worst_filtered = search_worst.drop(columns="BST")
fig = search_worst_filtered.plot(style='.-').get_figure()
fig.savefig("search_worst_filtered.png")
import os
import shutil
import pandas as pd
import matplotlib.pyplot as plt

def clean_directory(directory):    
    if os.path.exists(directory):
        shutil.rmtree(directory)
    os.makedirs(directory)

def generate_plot(
    filename, output, plot_style=".", has_logy=False, exclude_name=None):
    csv = pd.read_csv(filename, header=None)
    csv.columns = ["name", "nodes", "avg_case", "worst_case"]
    avg_time = csv.pivot(index="nodes", columns="name", values="avg_case")

    if exclude_name:
        avg_time = avg_time.drop(exclude_name, axis=1)

    ax = avg_time.plot(style=plot_style, logy=has_logy)
    ax.set_ylabel("ms")
    fig = ax.get_figure()
    fig.savefig(output)

if __name__ == "__main__":
    clean_directory("./images")
    
    # Average case
    generate_plot("./csv/insert-avg.csv", "./images/insert-avg.png", 
        ".", False)
    generate_plot(
        "./csv/insert-avg.csv", "./images/insert-avg-log.png", 
        ".", True)
    generate_plot(
        "./csv/search-avg.csv", "./images/search-avg.png", 
        ".-", False)
    generate_plot(
        "./csv/search-avg.csv", "./images/search-avg-log.png", 
        ".-", True)
    
    # Worst case
    generate_plot(
        "./csv/insert-worst.csv", "./images/insert-worst.png", 
        ".", False)
    generate_plot(
        "./csv/insert-worst.csv", "./images/insert-worst-log.png", 
        ".", True)
    generate_plot(
        "./csv/search-worst.csv", "./images/search-worst.png", 
        ".-", False)
    generate_plot(
        "./csv/search-worst.csv", "./images/search-worst-log.png", 
        ".-", True)

    # Generate Graphs excluding BST

    generate_plot(
        "./csv/insert-worst.csv", "./images/insert-worst-filtered.png", 
        ".", False, ["BST"])
    generate_plot(
        "./csv/insert-worst.csv", "./images/insert-worst-log-filtered.png", 
        ".", True, ["BST"])
    generate_plot(
        "./csv/search-worst.csv", "./images/search-worst-filtered.png", 
        ".-", False, ["BST"])

    generate_plot(
        "./csv/search-worst.csv", "./images/search-worst-log-filtered.png", 
        ".-", True, ["BST"])
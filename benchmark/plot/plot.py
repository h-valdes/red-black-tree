import os
import shutil
import pandas as pd
import matplotlib.pyplot as plt

def clean_directory(directory):    
    if os.path.exists(directory):
        shutil.rmtree(directory)
    os.makedirs(directory)

def generate_plot(filename, output, plot_style=".", has_logy=False):
    csv = pd.read_csv(filename, header=None)
    csv.columns = ["name", "nodes", "avg_case", "worst_case"]
    avg_time = csv.pivot(index="nodes", columns="name", values="avg_case")

    fig = avg_time.plot(style=plot_style, logy=has_logy).get_figure()
    fig.savefig(output)

if __name__ == "__main__":
    clean_directory("./images")
    
    # Average case
    generate_plot("insert-avg.csv", "./images/insert-avg.png", ".", False)
    generate_plot("insert-avg.csv", "./images/insert-avg-log.png", ".", True)
    generate_plot("search-avg.csv", "./images/search-avg.png", ".-", False)
    generate_plot("search-avg.csv", "./images/search-avg-log.png", ".-", True)
    
    # Worst case
    # generate_plot("insert-worst.csv", "./images/insert-worst.png", ".", False)
    # generate_plot("insert-worst.csv", "./images/insert-worst-log.png", ".", True)
    # generate_plot("search-worst.csv", "./images/search-worst.png", ".-", False)
    # generate_plot("search-worst.csv", "./images/search-worst-log.png", ".-", True)

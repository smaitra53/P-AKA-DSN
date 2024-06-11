import pandas as pd
import matplotlib.pyplot as plt

df1 = pd.read_csv('data/gsc-fall-gautn.log.4t.512m', header=None)
df2 = pd.read_csv('data/gsc-fall-gautn.log.10t.512m', header=None)
df3 = pd.read_csv('data/gsc-fall-gautn.log.50t.8g', header=None)
df4 = pd.read_csv('data/gsc-fall-gautn.log.0t.0m', header=None)

# Create a figure with two subplots
fig, axes = plt.subplots(nrows=2, ncols=1)

# Plot the functional latency from the three dataframes
axes[0].boxplot([df1[0], df2[0], df3[0], df4[0]], widths=0.1)
axes[0].set_ylabel('Functional Latency (us)')
axes[0].set_xticklabels([])
axes[0].grid(True)

# Plot the total latency from the three dataframes
axes[1].boxplot([df1[1], df2[1], df3[1], df4[1]], widths=0.1)
axes[1].set_ylabel('Total Latency (us)')
axes[1].set_xticklabels(['Thread=4\nEnclave Size=512M', 'Thread=10\nEnclave Size=512M', 'Thread=50\nEnclave Size=8G', 'Non-SGX'])
axes[1].grid(True)

# Adjust the subplots' layout
plt.tight_layout()

# Show the plot
plt.show()
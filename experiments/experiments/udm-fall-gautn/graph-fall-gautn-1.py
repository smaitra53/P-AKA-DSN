import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df1 = pd.read_csv('/home/nssl/experiments/udm-fall-gautn/Data/gsc-fall-gautn.log.4t.512m', header=None)
df2 = pd.read_csv('/home/nssl/experiments/udm-fall-gautn/Data/gsc-fall-gautn.log.10t.512m', header=None)
df3 = pd.read_csv('/home/nssl/experiments/udm-fall-gautn/Data/gsc-fall-gautn.log.50t.8g', header=None)
df4 = pd.read_csv('/home/nssl/experiments/udm-fall-gautn/Data/gsc-fall-gautn.log.0t.0m', header=None)
df = pd.read_csv('/home/nssl/experiments/udm-fall-gautn/Data/data.csv', header=None)

# Create a figure with two subplots
fig, axes = plt.subplots(2, 2, figsize=(8, 6))

# Set the font size
sns.set(font_scale=1.2)

# Plot the functional latency box plot on the first subplot
sns.boxplot(data=[df1[0], df2[0], df3[0], df4[0]], ax=axes[0,0], width=0.1)
axes[0,0].set_ylabel('Functional Latency (us)')
axes[0,0].set_xticklabels([])
axes[0,0].grid(True)

# Plot the total latency box plot on the second subplot
sns.boxplot(data=[df1[1], df2[1], df3[1], df4[1]], ax=axes[1,0], width=0.1)
axes[1,0].set_ylabel('Total Latency (us)')
axes[1,0].set_xticklabels(['Thread=4\nEnclave Size=512M', 'Thread=10\nEnclave Size=512M', 'Thread=50\nEnclave Size=8G', 'Non-SGX'])
axes[1,0].grid(True)

# Plot the functional latency box plot on the first subplot
sns.boxplot(data=[df[0]], ax=axes[0,1], width=0.1, color='skyblue')
axes[0,1].set_ylabel('Enclave Load Time (us)')
axes[0,1].set_xticklabels([])
axes[0,1].grid(True)

# Plot the total latency box plot on the second subplot
sns.boxplot(data=[df[1]], ax=axes[1,1], width=0.1, color='grey')
axes[1,1].set_ylabel('Module Response Latency (us) [first run]')
axes[1,1].set_xticklabels([])
axes[1,1].grid(True)

# Adjust the subplots' layout
plt.tight_layout()

# Show the plot
plt.show()

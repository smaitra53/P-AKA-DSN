import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df1 = pd.read_csv('data/gsc-fall-gautn.log.4t.512m', header=None)
df2 = pd.read_csv('data/gsc-fall-gautn.log.10t.512m', header=None)
df3 = pd.read_csv('data/gsc-fall-gautn.log.50t.8g', header=None)
df4 = pd.read_csv('data/gsc-fall-gautn.log.0t.0m', header=None)
df = pd.read_csv('data/enc_load-udm_1st_run-fall_gautn.csv', header=None)

# Create a figure with two subplots
fig, axes = plt.subplots(2, 1, figsize=(14,9))
# Set the font size
sns.set(font_scale=1.2, palette="pastel")
# Plot the functional latency box plot on the first subplot
sns.boxplot(data=[df1[0], df2[0], df3[0], df4[0]], ax=axes[0], width=0.5)
axes[0].set_ylabel('Functional Latency (us)',fontsize=20)
axes[0].set_xticklabels([])

axes[0].grid(True)
axes[0].set_ylim([45, 85])

# Plot the total latency box plot on the second subplot
sns.boxplot(data=[df1[1], df2[1], df3[1], df4[1]], ax=axes[1], width=0.5)
axes[1].set_ylabel('Total Latency (us)',fontsize=20)
axes[1].set_xticklabels(['Thread=4\nEnclave Size=512M', 'Thread=10\nEnclave Size=512M', 'Thread=50\nEnclave Size=8G', 'Non-SGX'],size=18)
axes[1].grid(True)
axes[1].set_ylim([65, 195])

for ax in axes:
    ax.tick_params(axis='y', labelsize=18)
# Adjust the subplots' layout
# plt.tight_layout()
plt.subplots_adjust(hspace=0.05)
# Show the plot
plt.show()
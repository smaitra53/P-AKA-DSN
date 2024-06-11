import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv('data/udm-vnf-res', header=None)

# Create a figure with two subplots
fig, (ax1, ax2) = plt.subplots(1, 2)

# Set the font size
sns.set(font_scale=1.2)

# Plot the total latency box plot on the second subplot
sns.boxplot(data=[df[0]], ax=ax1, width=0.2, color='skyblue')
ax1.set_ylabel('External UDM Module Response Latency (us)', fontsize=12)
ax1.set_xticklabels(['Initial run'], fontsize=12)
ax1.grid(True)

# Plot the total latency box plot on the second subplot
sns.boxplot(data=[df[1]], ax=ax2, width=0.2, color='grey')
ax2.set_ylabel('')
ax2.set_xticklabels(['Subsequent runs'],fontsize=12)
ax2.grid(True)
# Adjust the subplots' layout
plt.tight_layout()

# Show the plot
plt.show()
# import pandas as pd
# import matplotlib.pyplot as plt
# import seaborn as sns

# df = pd.read_csv('data/ausf-vanilla.csv', header=None, names=['Functional', 'Total'])

# # Create a figure with two subplots
# fig, (ax1, ax2) = plt.subplots(2, 1)

# # Set the font size
# sns.set(font_scale=1.2)

# # Plot the total latency box plot on the second subplot
# sns.boxplot(data=[df[0]], ax=ax1, width=0.2, color='skyblue')
# ax1.set_ylabel('External AUSF Module Response Latency (us)', fontsize=12)
# ax1.set_xticklabels(['Functional'], fontsize=12)
# ax1.grid(True)

# # Plot the total latency box plot on the second subplot
# sns.boxplot(data=[df[1]], ax=ax2, width=0.2, color='grey')
# ax2.set_ylabel('')
# ax2.set_xticklabels(['Total'],fontsize=12)
# ax2.grid(True)
# # Adjust the subplots' layout
# plt.tight_layout()

# # Show the plot
# plt.show()

import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

dataframe = pd.read_csv("data/ausf-vanilla.csv")
df = pd.DataFrame(data=dataframe, columns=["Functional", "Total"])

# sns.set(style='whitegrid')
sns.set_theme(style="ticks", palette="pastel")
boxplot = sns.boxplot(x="variable", y="value", data=pd.melt(df), width=0.2)
boxplot.set_xlabel("Conditions", fontsize=14)
boxplot.set_ylabel("Values", fontsize=14)
plt.show()
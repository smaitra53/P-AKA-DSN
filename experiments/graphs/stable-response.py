import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

stable_resp = pd.read_csv('/home/nssl/graphs/data/stable-response')

sns.set(font_scale=1.6,style='ticks', palette="pastel")

plt.figure(figsize=(14,9))
stable = sns.boxplot(x=stable_resp['module'], y=stable_resp['time'],
            hue=stable_resp['Isolation'], palette=["b", "g"], width=0.5, 
            linewidth=1, fliersize=2, hue_order=['Container','SGX'])

stable.set_ylabel('Stable Response Latency (us)', fontsize=30)
stable.set_xlabel('External Module', fontsize=30)


stable.set_ylim([200, 1600])

plt.xticks(fontsize=28)
plt.yticks(fontsize=28)

# Adjust the subplots' layout
# plt.tight_layout()


# Show the plot
plt.show()
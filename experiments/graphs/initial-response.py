import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

init_resp = pd.read_csv('/home/nssl/graphs/data/initial-response')

sns.set(font_scale=1.6,style='ticks', palette="pastel")

plt.figure(figsize=(14,9))
init = sns.boxplot(x=init_resp['module'], y=init_resp['time'],
            width=0.2, linewidth=1, fliersize=3)

init.set_ylabel('Initial Response Latency (ms)', fontsize=30)
init.set_xlabel('External Module', fontsize=30)

init.set_ylim([22, 23.6])

# Adjust the subplots' layout
# plt.tight_layout()

plt.xticks(fontsize=28)
plt.yticks(fontsize=28)
# Show the plot
plt.show()
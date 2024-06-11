import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

init_resp = pd.read_csv('/home/nssl/graphs/data/initial-response')
stable_resp = pd.read_csv('/home/nssl/graphs/data/stable-response')

sns.set(font_scale=1.2,style='ticks', palette="pastel")

fig, (ax1, ax2) = plt.subplots(1, 2)

stable = sns.boxplot(x=stable_resp['module'], y=stable_resp['time'],
            hue=stable_resp['Isolation'], palette=["b", "g"], width=0.5, 
            linewidth=1, fliersize=3, hue_order=['Container','SGX'], ax=ax1)

init = sns.boxplot(x=init_resp['module'], y=init_resp['time'],
            width=0.2, linewidth=1, fliersize=3, ax=ax2)

stable.set_ylabel('Stable Response Latency (us)', fontsize=16)
stable.set_xlabel('External Module', fontsize=16)

init.set_ylabel('Initial Response Latency (ms)', fontsize=16)
init.set_xlabel('External Module', fontsize=16)

stable.set_ylim([200, 1600])
init.set_ylim([22, 23.6])

# Adjust the subplots' layout
plt.tight_layout()

# Show the plot
plt.show()  
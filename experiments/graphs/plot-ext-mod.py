import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

func_df = pd.read_csv('/home/nssl/graphs/data/functional-latency')

tot_df = pd.read_csv('/home/nssl/graphs/data/total-latency')

sns.set(font_scale=1.2,style='ticks', palette="pastel")
# sns.set_theme(style="ticks", palette="pastel")

fig, (ax1, ax2) = plt.subplots(1, 2)

func = sns.boxplot(x=func_df['External Module'], y=func_df['Functional Latency (us)'],
            hue=func_df['Isolation'], palette=["b", "g"], width=0.7, linewidth=1, 
            fliersize=3, hue_order=['Container','SGX'], ax=ax1)

tot = sns.boxplot(x=tot_df['External Module'], y=tot_df['Total Latency (us)'],
            hue=tot_df['Isolation'], palette=["b", "g"], width=0.7  , linewidth=1,
            fliersize=3, hue_order=['Container','SGX'], ax=ax2)


func.set_ylabel('Functional Latency (us)', fontsize=16)
func.set_xlabel('External Module', fontsize=16)

tot.set_ylabel('Total Latency (us)', fontsize=16)
tot.set_xlabel('External Module', fontsize=16)

func.set_ylim([20, 70])
tot.set_ylim([38, 180])

# Adjust the subplots' layout
plt.tight_layout()

# Show the plot
plt.show()  
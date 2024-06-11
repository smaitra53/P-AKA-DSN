import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

enc_ld = pd.read_csv('/home/nssl/graphs/data/enclave-load-times/enclave-load-times')

sns.set_theme(style="ticks", palette="pastel")
plt.figure(figsize=(14,9))
enc_ld_time = sns.boxplot(x=enc_ld['External Module'], y=enc_ld['Enclave Load Time (mins)'],
            width=0.5, linewidth=1, fliersize=3)

enc_ld_time.set_ylabel('Enclave Load Time (mins)', fontsize=30)
enc_ld_time.set_xlabel('External Module', fontsize=30)

plt.xticks(fontsize=28)
plt.yticks(fontsize=28)
# Adjust the subplots' layout
# plt.tight_layout()

# Show the plot
plt.show()
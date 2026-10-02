import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

mat    = ["Polietilen", "Melanin", "Aluminyum"]
notron = [1224, 2829, 5163]
gama   = [1048, 2354, 13069]

x = np.arange(len(mat)); w = 0.35
fig, ax = plt.subplots(figsize=(7.5,5.5))
ax.bar(x - w/2, notron, w, label="Notron", color="#4a7c9e")
ax.bar(x + w/2, gama,   w, label="Gama",   color="#c77c3c")

for i,(n,g) in enumerate(zip(notron,gama)):
    ax.text(i-w/2, n*1.05, str(n), ha="center", fontsize=9)
    ax.text(i+w/2, g*1.05, str(g), ha="center", fontsize=9)

ax.set_xticks(x); ax.set_xticklabels(mat)
ax.set_ylabel("Fantoma giren parcacik sayisi")
ax.set_title("Ikincil radyasyon (15 g/cm$^2$, 100 MeV proton, $10^5$ olay)")
ax.legend(loc="upper left"); ax.grid(axis="y", alpha=0.3)
ax.set_ylim(0, 15000)
plt.tight_layout()
plt.savefig("/home/beyza/melashield/grafik2_ikincil.png", dpi=200)
print("Kaydedildi: grafik2_ikincil.png")

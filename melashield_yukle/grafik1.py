import pandas as pd
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

df = pd.read_csv("/home/beyza/melashield/tarama_sonuclari.csv")

# Tum dozlari nanoGy'ye cevir
def nGy(satir):
    d = float(satir["doz"])
    return d/1000.0 if satir["doz_birim"].strip() == "picoGy" else d

df["doz_nGy"] = df.apply(nGy, axis=1)

isim = {"melanin": "Melanin", "aluminium": "Aluminyum", "polyeth": "Polietilen"}
renk = {"melanin": "#8B4513", "aluminium": "#708090", "polyeth": "#1f77b4"}

plt.figure(figsize=(7,5))
for mat in ["polyeth", "melanin", "aluminium"]:
    alt = df[df["malzeme"] == mat].sort_values("alansal_g_cm2")
    plt.plot(alt["alansal_g_cm2"], alt["doz_nGy"],
             marker="o", label=isim[mat], color=renk[mat])

plt.yscale("log")
plt.xlabel("Kalkan alansal yogunlugu (g/cm$^2$)")
plt.ylabel("Fantom dozu (nGy)")
plt.title("100 MeV proton, 30 cm su fantomu")
plt.legend()
plt.grid(True, which="both", alpha=0.3)
plt.tight_layout()
plt.savefig("/home/beyza/melashield/grafik1_doz.png", dpi=200)
print("Kaydedildi: grafik1_doz.png")

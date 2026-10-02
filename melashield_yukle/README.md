# MelaShield

Melaninin uzay radyasyonuna karşı kalkan malzemesi olarak Geant4 ile incelenmesi.

**Beyza Nur Süslü** — Marmara Üniversitesi, 2026

## Amaç
Melaninin proton kalkanlama performansını, uzay aracı tasarımında gerçek kısıt olan kütle açısından alüminyum ve polietilenle karşılaştırmak.

## Yöntem
- Geant4 v11.2.2 (örnek B1 tabanlı)
- Melanin: C %52,45 · H %3,40 · N %7,88 · O %36,27 (kütlece), 1,5 g/cm3 — Ito (1986)
- Geometri: 40x40 cm kalkan levhası + 30 cm su fantomu, vakum ortam
- Kaynak: 100 MeV proton, 10^5 olay
- Karşılaştırma eşit alansal yoğunlukta (g/cm2)

## Sonuçlar
15 g/cm2 kalkanda fantom dozu (nGy):
| Malzeme | Doz | Nötron | Gama |
|---|---|---|---|
| Polietilen | 0,041 | 1224 | 1048 |
| Melanin | 0,082 | 2829 | 2354 |
| Alüminyum | 0,174 | 5163 | 13069 |

Melanin alüminyumdan 2,1 kat az doz geçirir ve 5,6 kat az gama üretir. Polietilen her ölçütte en iyi.

## Dosyalar
- `src/`, `include/` — Geant4 kodu
- `tarama.sh` — otomatik koşu betiği
- `grafik1.py`, `grafik2.py` — grafik üretimi
- `tarama_sonuclari.csv` — ham veri

## Kaynaklar
- Ito S. (1986) Biochim Biophys Acta 883:155-161
- Agostinelli S. ve ark. (2003) Geant4,
- Agostinelli S. ve ark. (2003) Geant4, NIM A 506:250-303
- NIST PSTAR

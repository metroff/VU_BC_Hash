# Hash funkcijų palyginimas
## Turinys
- [Užduotis](#užduotis)
- [Programos paleidimas](#programos-paleidimas)
- [Testavimas](#testavimas)
  - [Spartos analizė lyginant po vieną eilutę](#line-by-line-benchmark)
  - [Spartos analizė lyginant visą failą](#whole-file-benchmark)
  - [Atsparumo "kolizijai" testas](#collision-test)
  - [Maišos skirtingumo testas](#difference-test)
- [Apibendrinimas](#apibendrinimas)
  - [Bendra rezultatų lentelė](#bendra-rezultatų-lentelė)
  
## Užduotis

Atlikti lyginamąją analizę naudojant sukurtus hash generatorius. Visos panaudotos hash funckijos buvo sujungtos į vieną programą.

---

## Programos paleidimas
Programa paleidžiama iš komandinės eilutės naudojant `./main`:
```shell
./main
```
---

## Testavimas
### Line by line benchmark
Šis metodas skirtas palyginti maišos funkcijų greitaveiką, maišant `konstitucija.txt' failą po vieną eilutę.

Testas atliktas 5000 kartų.

| Github username | Line by line hashing average time (ms) | Points |
| :---: | :---: | :---: |
| [metroff](https://github.com/metroff/VU_BC_Hash) | 0.000081 | 1 |
| [swoogie](https://github.com/swoogie/hashProject) | 0.00011 | 2 |
| [rendertom](https://github.com/rendertom/VU-Blockchain-Task-1-Hash) | 0.000163 | 3 |
| [Vabasou](https://github.com/Vabasou/blockChainTask1) | 0.000164 | 4 |
| [MantasM2001](https://github.com/MantasM2001/VU-hash-function) | 0.001065 | 5 |
| [domas404](https://github.com/domas404/blockchain) | 0.001445 | 6 |
| [Miautawn](https://github.com/Miautawn/VU-blockchain) | 0.002513 | 7 |
| [EimantasV](https://github.com/EimantasV/Hash) | 0.006275 | 8 |
| [IvoskaJ](https://github.com/IvoskaJ/BlockChainPratybos) | 0.006323 | 9 |
| [OvidijusV](https://github.com/OvidijusV/Bloku-grandiniu-technologijos) | 0.007854 | 10 |

### Whole file benchmark

Šis metodas skirtas palyginti maišos funkcijų greitaveiką, maišant visą `konstitucija.txt' failą iš karto.

Testas atliktas 5000 kartų.

| Github username | Whole file hashing average time (ms) | Points |
| :---: | :---: | :---: |
| [rendertom](https://github.com/rendertom/VU-Blockchain-Task-1-Hash) | 0.062473 | 1 |
| [swoogie](https://github.com/swoogie/hashProject) | 0.063311 | 2 |
| [Vabasou](https://github.com/Vabasou/blockChainTask1) | 0.081967 | 3 |
| [metroff](https://github.com/metroff/VU_BC_Hash) | 0.085529 | 4 |
| [MantasM2001](https://github.com/MantasM2001/VU-hash-function) | 0.231015 | 5 |
| [OvidijusV](https://github.com/OvidijusV/Bloku-grandiniu-technologijos) | 0.248274 | 6 |
| [domas404](https://github.com/domas404/blockchain) | 4.862543 | 7 |
| [IvoskaJ](https://github.com/IvoskaJ/BlockChainPratybos) | 6.409149 | 8 |
| [Miautawn](https://github.com/Miautawn/VU-blockchain) | 8.994385 | 9 |
| [EimantasV](https://github.com/EimantasV/Hash) | 30.588713 | 10 |

### Collision test
Šis metodas skirtas palyginti ar dviejų skirtingų argumentų "hash'ai" nesutampa. Tam yra sugeneruojama 100000 atsitiktinių simbolių eilučių porų, kurios susideda iš skirtingo ilgio porų (10, 100, 500, 1000), pvz. (asdfg, hijkl).
| Github username | Collision count | Points |
| :---: | :---: | :---: |
| [metroff](https://github.com/metroff/VU_BC_Hash) | 0 | 1 |
| [rendertom](https://github.com/rendertom/VU-Blockchain-Task-1-Hash) | 0 | 1 |
| [Miautawn](https://github.com/Miautawn/VU-blockchain) | 0 | 1 |
| [IvoskaJ](https://github.com/IvoskaJ/BlockChainPratybos) | 0 | 1 |
| [OvidijusV](https://github.com/OvidijusV/Bloku-grandiniu-technologijos) | 0 | 1 |
| [swoogie](https://github.com/swoogie/hashProject) | 0 | 1 |
| [Vabasou](https://github.com/Vabasou/blockChainTask1) | 0 | 1 |
| [MantasM2001](https://github.com/MantasM2001/VU-hash-function) | 0 | 1 |
| [EimantasV](https://github.com/EimantasV/Hash) | 0 | 1 |
| [domas404](https://github.com/domas404/blockchain) | 11 | 2 |


### Difference test
Šis metodas skirtas palyginti maišos funkcijos išvesties skirtingumą bitų ir hex'ų lygmenyje. Tam yra sugeneruojama 100000 simbolių eilučių porų, kurios skiriasi vienu simboliu ir susideda iš skirtingo ilgio porų (10, 100, 500, 1000), pvz. (asdfg, bsdfg).

Jei hex skirtumas didelis, tai ir bit skirtumas didelis (Jei bit'ų ir hex'ų lygmenyje 1-os vietos tai + 2 taškai, tačiau jei vieta paskutinė tai + 20 tašku). Tam, kad vertinimas būtų tikslesnis vidurkiai buvo sudėti.

| Github username | Avg Hex Difference | Avg Bit Difference | Sum of averages | Points |
| :---: | :---: | :---: | :---: | :---: |
| [domas404](https://github.com/domas404/blockchain) | 94.721688 | 50.81327 | 145.534958 | 1 |
| [Vabasou](https://github.com/Vabasou/blockChainTask1) | 93.90025 | 50.553867 | 144.454117 | 2 |
| [swoogie](https://github.com/swoogie/hashProject) | 94.345078 | 50.064105 | 144.409183 | 3 |
| [MantasM2001](https://github.com/MantasM2001/VU-hash-function) | 93.747172 | 50.006973 | 143.754145 | 4 |
| [rendertom](https://github.com/rendertom/VU-Blockchain-Task-1-Hash) | 92.795469 | 49.370609 | 142.166078 | 5 |
| [Miautawn](https://github.com/Miautawn/VU-blockchain) | 91.124078 | 48.270559 | 139.394637 | 6 |
| [OvidijusV](https://github.com/OvidijusV/Bloku-grandiniu-technologijos) | 89.865234 | 44.377859 | 134.243093 | 7 |
| [metroff](https://github.com/metroff/VU_BC_Hash) | 89.008734 | 43.627711 | 132.636445 | 8 |
| [EimantasV](https://github.com/EimantasV/Hash) | 86.533203 | 42.518301 | 129.051504 | 9 |
| [IvoskaJ](https://github.com/IvoskaJ/BlockChainPratybos) | 48.292234 | 32.415266 | 80.7075 | 10 |

## Apibendrinimas
Vertiniama sudėjus visų etapų taškus pagal mažiausią taškų kiekį (kuo mažiau tuo geriau).

| Github username | Sum of points | Overall place |
| :---: | :---: | :---: |
| [swoogie](https://github.com/swoogie/hashProject) | 8 | 1 |
| [Vabasou](https://github.com/Vabasou/blockChainTask1) | 10 | 2 |
| [rendertom](https://github.com/rendertom/VU-Blockchain-Task-1-Hash) | 10 | 2 |
| [metroff](https://github.com/metroff/VU_BC_Hash) | 14 | 3 |
| [MantasM2001](https://github.com/MantasM2001/VU-hash-function) | 15 | 4 |
| [domas404](https://github.com/domas404/blockchain) | 16 | 5 |
| [Miautawn](https://github.com/Miautawn/VU-blockchain) | 23 | 6 |
| [OvidijusV](https://github.com/OvidijusV/Bloku-grandiniu-technologijos) | 24 | 7 |
| [EimantasV](https://github.com/EimantasV/Hash) | 28 | 8 |
| [IvoskaJ](https://github.com/IvoskaJ/BlockChainPratybos) | 28 | 8 |

Pirma vietą užėmė [swoogie](https://github.com/swoogie/hashProject) algoritmas. Greičiausias buvo [metroff](https://github.com/metroff/VU_BC_Hash) (hash'uojant eilutėmis) ir [rendertom](https://github.com/rendertom/VU-Blockchain-Task-1-Hash) (hash'uojant visą failą) algoritmai. Didžiausiu skirtingumu pasižymėjo [domas404](https://github.com/domas404/blockchain) algoritmas.

### Bendra rezultatų lentelė
| Github username | Line by line hashing average time (ms) | Whole file hashing average time (ms) | Collision count | Avg Hex Difference | Avg Bit Difference |
| :---: | :---: | :---: | :---: | :---: | :---: |
| [metroff](https://github.com/metroff/VU_BC_Hash) | 0.000081 | 0.085529 | 0 | 89.008734 | 43.627711 |
| [rendertom](https://github.com/rendertom/VU-Blockchain-Task-1-Hash) | 0.000163 | 0.062473 | 0 | 92.795469 | 49.370609 |
| [Miautawn](https://github.com/Miautawn/VU-blockchain) | 0.002513 | 8.994385 | 0 | 91.124078 | 48.270559 |
| [domas404](https://github.com/domas404/blockchain) | 0.001445 | 4.862543 | 11 | 94.721688 | 50.81327 |
| [IvoskaJ](https://github.com/IvoskaJ/BlockChainPratybos) | 0.006323 | 6.409149 | 0 | 48.292234 | 32.415266 |
| [OvidijusV](https://github.com/OvidijusV/Bloku-grandiniu-technologijos) | 0.007854 | 0.248274 | 0 | 89.865234 | 44.377859 |
| [swoogie](https://github.com/swoogie/hashProject) | 0.00011 | 0.063311 | 0 | 94.345078 | 50.064105 |
| [Vabasou](https://github.com/Vabasou/blockChainTask1) | 0.000164 | 0.081967 | 0 | 93.90025 | 50.553867 |
| [MantasM2001](https://github.com/MantasM2001/VU-hash-function) | 0.001065 | 0.231015 | 0 | 93.747172 | 50.006973 |
| [EimantasV](https://github.com/EimantasV/Hash) | 0.006275 | 30.588713 | 0 | 86.533203 | 42.518301 |

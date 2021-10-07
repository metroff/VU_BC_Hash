# `myHash` Hash funkcijos generatoriaus kūrimas
### Palyginimas su kitų studentų generatoriais [čia.](https://github.com/metroff/VU_BC_Hash/tree/comparison)
---

## Turinys
- [Užduotis](#užduotis)
- [Algoritmas](#algoritmas)
- [Programos paleidimas](#programos-paleidimas)
- [Testavimas](#testavimas)
  - [Maišos algoritmo tikrinimas](#hash-algorithm-test)
  - [Spartos analizė maišant po vieną eilutę](#benchmark-line-by-line-hashing)
  - [Spartos analizė lyginant su kitais algoritmais](#benchmark-with-md5-sha1-sha256)
  - [Atsparumo "kolizijai" testas](#collision-test)
  - [Maišos skirtingumo testas](#difference-test)
- [Išvados](#išvados)
## Užduotis
Sukurkite maišos funkciją (hash), kuri atitiktų šiuos reikalavimus:
1. Maišos funkcijos įėjimas gali būti bet kokio dydžio simbolių eilutė.
2. Maišos funkcijos išėjimas visuomet yra to paties, fiksuoto, dydžio rezultatas.
3. Maišos funkcija yra deterministinė, t. y., tam pačiam įvedimui išvedimas visuomet yra tas pats.
4. Maišos funkcijos reikšmė bet kokiai input'o reikšmei yra apskaičiuojamas greitai - efektyviai.
5. Iš hash funkcijos rezultato praktiškai neįmanoma atgaminti pradinio įvedimo.
6. Maišos funkcija yra atspari "kolizijai" (praktiškai neįmanoma surasti tokių dviejų skirtingų argumentų, kad jiems gautume tą patį hash'ą).
7. Bent minimaliai pakeitus įvedimą, maišos funkcijos rezultatas-kodas turi skirtis iš esmės, t.y., tenkinamas taip vadinamas lavinos efektas (angl. Avalanche effect).
---

## Algoritmas
Algoritmo pseudo-kodas
```
FUNCTION myHash(input: string) : string {
    output <- ""                        
    hexes <- [8]                        // initialize integer array with 8 elements

    length <- input.length              // initialize length with input length

    num <- 1153
    sum <- num

    FOR i = 0 TO length                 // "randomize" sum and num variables 
        sum <- num BITWISE_OR (int(input[i]) MOD num)
        num <- num LEFT_ROTATE 5 + int(input[i]) - num

    FOR i = 1 TO sum MOD 100            // mix up intial array values
        hexes[i%8] = hexes[i%8] RIGHT_ROTATE 16
    
    FOR i = 0 TO 8                      // more mixups to reduce collisions and for avalanche
        hexes[i] <- hexes[i] BITWISE_XOR (NOT hexes[7-i]) * num
        hexes[7-i] <- hexes[7-i] BITWISE_OR (NOT hexes[i]) * sum
    }
    
    FOR i = 0 TO 8 
        output <- output + TO_HEX(hexes[i])

    return output;
}
```
---

## Programos paleidimas
Programa paleidžiama iš komandinės eilutės naudojant `./main` ir papildomus argumentus, pvz.:
```shell
./main <input_text>     -- hash'o skaičiavimas įvestam tekstui
./main -f <filepath>    -- hash'o skaičiavimas išoriniam failui
./main -test            -- testų paleidimui
```
### Rankinis teksto įvedimas
Paleidus programą `./main`, vietoje `<input_text>` reikia įrašyti norimą tekstą. Jeigu tekstas sudarytas iš kelių žodžių reikia naudoti kabutes.
```shell
> ./main "Hello world!"
HASH: ccffdacf9ebeffbf51efebdf9f7ddfd72fdc953646a6de84047da52c6a60180d
```
### Išorinio failo nudojimas
Paleidus programą `./main`, vietoje `<filepath>` reikia įrašyti kelią (path) iki failo.
```shell
> ./main ./data/a.txt
HASH: 0566fbfdb3e56efbfd6ed2d7ed9954271cd52e0b44975aeae5a9974845dfd8ca
```
---

## Testavimas
Paleidus programą `./main` su vėliavėle `-test` reikia pasirinkti vieną iš galimų testų.
```shell
> ./main -test
1: Hash output length, deterministic algorithm test
2: Benchmark line by line hashing (MyHash)
3: Benchmark line by line hashing (MyHash, md5, sha1, sha256)
4: Benchmark whole file hashing (MyHash, md5, sha1, sha256)
5: MyHash collision test
6: MyHash output difference in bits and hex test
```
### Hash algorithm test
Šis testas tikrina 1-3 punktus([Užduotis](#užduotis)). Testo metu tikrinimui naudojami:
- Tuščias failas (`empty.txt`).
- Du failai sudaryti tik iš vieno, tačiau skirtingo, simbolio (`a.txt`, `b.txt`).
- Du failai sudaryti iš daug (10000) atsitiktinai sugeneruotų simbolių (`10000-1.txt`, `10000-2.txt`).
- Du failai sudaryti iš daug (10001) simbolių, bet skirtųsi vienas nuo kito tik vienu simboliu (`10000-a.txt`, `10000-b.txt`).

Šio metodo pagalba įsitikinama, kad nepriklausomai nuo įvesties ilgio, išvestis visada bus 64 simbolių hex reikšmė, o kiekvieno failo hash'as visada yra tas pats. Taip pat galima pamatyti, kad pakeitus vieną simbolį maišos funkcijos rezultatas (hash) visiškai pasikeičia.
```shell
Select: 1
-------
Running: Hash output length, deterministic algorithm test
-------

data/empty.txt HASH: ffedfaffff95f4ffffcffe7ff77f77ff0205011604079908376002a838850300
data/a.txt HASH: febfedeefd47f1cafdb8d7ecf88fff8b63562f778055f9bb00c067fdcb9d2b91
data/b.txt HASH: a8f9d7b72cf565ffbf7cc7fff7e3f3ff79adc2ab291d29ca5e5651287b1511e2
data/10000-1.txt HASH: faca7e3df7fcf7fbd33bdefff19bedc79bb7b3c3dfd7ddb85b83aa6817d0bb90
data/10000-2.txt HASH: f76abbe7cf36ef7dfade7f55fdfdfefb5bcce68a5921bc7003c70fec0d6706e5
data/10000-a.txt HASH: fdfed7eef7defcbe6f6fb53c5af7efbbcea362474a4472091525b61823af3251
data/10000-b.txt HASH: dfdfaf6efeffdfbebfb9e2fc7ee5ef3b8b32e3a778e8f5f9552d2ef821a366c9

Length of hash function output is always the same!
Hash function is deterministic!
```

### Benchmark line by line hashing
Šis metodas skirtas maišos spartai ištirti, maišant `konstitucija.txt' failą po vieną eilutę.
```shell
Select: 2
-------
Running: Benchmark line by line hashing (MyHash)
Input file: data/konstitucija.txt
Number of iterations: 5000
-------

MyHash total time: 0.000357 s.
MyHash average time per run: 0.000071 ms.
```
### Benchmark with MD5, SHA1, SHA256
Šis metodas skirtas palyginti `myHash` maišos funkcijos greitaveiką su `MD5`, `SHA1`, `SHA256`, maišant `konstitucija.txt' failą po vieną eilutę.
```shell
Select: 3
-------
Running: Benchmark line by line hashing (MyHash, md5, sha1, sha256)
Input file: data/konstitucija.txt
Number of iterations: 5000
-------

MyHash total: 0.000382 s., average: 0.000076 ms.
md5 total: 0.001406 s., average: 0.000281 ms.
sha1 total: 0.001419 s., average: 0.000284 ms.
sha256 total: 0.002761 s., average: 0.000552 ms.
```
Taip pat galima palyginti `myHash` maišos funkcijos greitaveiką su `MD5`, `SHA1`, `SHA256`, maišant visą `konstitucija.txt' failą iš karto.
```shell
Select: 4
-------
Running: Benchmark whole file hashing (MyHash, md5, sha1, sha256)
Input file: data/konstitucija.txt
Number of iterations: 5000
-------

MyHash total: 0.463400 s., average: 0.092680 ms.
md5 total: 0.618884 s., average: 0.123777 ms.
sha1 total: 1.226125 s., average: 0.245225 ms.
sha256 total: 1.505921 s., average: 0.301184 ms.
```
### Collision test
Šis metodas skirtas palyginti ar dviejų skirtingų argumentų "hash'ai" nesutampa. Tam yra sugeneruojama 100000 atsitiktinių simbolių eilučių porų, kurios susideda iš skirtingo ilgio porų (10, 100, 500, 1000), pvz. (asdfg, hijkl).
```shell
Select: 5
-------
Running: MyHash collision test
-------

MyHash colision count: 0
```
### Difference test
Šis metodas skirtas palyginti maišos funkcijos išvesties skirtingumą bitų ir hex'ų lygmenyje. Tam yra sugeneruojama 100000 simbolių eilučių porų, kurios skiriasi vienu simboliu ir susideda iš skirtingo ilgio porų (10, 100, 500, 1000), pvz. (asdfg, bsdfg).
```shell
Select: 6
-------
Running: MyHash output difference in bits and hex test
-------

Hex max difference: hex: 100.00 %, bit:  57.42 %
Hex avg difference: hex:  89.00 %, bit:  43.62 %
Hex min difference: hex:  46.88 %, bit:  22.27 %
```
---
## Išvados
Maišos funkcija atitinka visus reikalavimus nurodytus [užduotyje](#užduotis).

Paduodant bet kokio ilgio simbolių eilutę yra sugeneruojama vienoda 64 simbolių hex išvestis. Tai matoma [čia](#hash-algorithm-test).

Maišos funkcija yra deterministinė, tos pačios įvesties "hash'as" visą laiką yra tas pats.

Maišos funkcija yra gana greita ir efektyvi. Maišant failo `konstitucija.txt` turinį po vieną eilutę, vidutinis maišymo laikas 0.00007ms. (Testo rezultatus galima pamatyti [čia](#benchmark-line-by-line-hashing)). Lyginant funkciją su kitais algoritmais (`md5`, `sha1`, `sha256`), sukurta maišos funkcija `myHash` yra greitesnė (nuo 1,3 iki 2,5 karto) testuotais atvejais (Testo rezultatus galima pamatyti [čia](#benchmark-with-md5-sha1-sha256)).

Maišos funkcijos `myHash` atsparumas kolizijai yra labai didelis. Iš 100000 skirtingų simbolių eilučių porų nėra nė vienos kurių "hash'ai" sutaptų (Testo rezultatus galima pamatyti [čia](#collision-test)).

Maišos funkcijos rezultatas pakeitus įvedimą vienų simboliu (pvz.: iš 'hello world' į 'heloo world') iš esmės pasikeičia. Algoritmas tenkina lavinos efekto reikalavimus (tai galima matyt [čia](#hash-algorithm-test)). Taip pat atlikus [išvesties skirtingumo testą](#difference-test) yra matoma, kad vidutinis dviejų įvesčių, kurios skiriasi vienu simboliu, "hash'ų" simbolių hex skirtingumas yra 89 procentai.
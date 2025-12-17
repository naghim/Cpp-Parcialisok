# Botnet command & control szerver

Egy kiberbiztonsági cég gyakornokaként megkértek, hogy készíts egy szimulált **botnet command & control (C&C) szervert** C++ nyelven.  
A szerver fertőzött gépeket ("zombi" PC-ket) tart nyilván, parancsokat küld nekik, és képes koordinált támadásokat (pl. DDoS) indítani.

### Adatok

Az adatokat olvasd be a `zombies.txt` állományból. A fájl szerkezete a következő:

Minden sor egy új zombi gépet jelöl. A sorok szóközökkel vagy tabulátorral vannak elválasztva.  
Formátum:

```text
IP_cím ország CPU_százalék típus extra_adat
```

Például:

```text
185.23.11.45    Romania     67    Windows    10
94.156.2.89     Ukraine     92    Linux      true
178.128.45.201  Russia      34    Windows    11
5.199.200.11    Hungary     88    Linux      false
212.77.1.33     Poland      55    Windows    10
```

A `típus` mező alapján kell eldönteni, hogy Windows vagy Linux zombi objektum jön létre, és az `extra_adat` mező jelentése ehhez igazodik.

### Alap- és származtatott osztályok

Hozz létre egy `Zombie` nevű **absztrakt** osztályt, amely minden zombi közös tulajdonságait és függvényeit.

Származtass belőle **két** konkrét osztályt:

1. `WindowsZombie`
   Extra adattag: verzió (pl. "10", "11")

2. `LinuxZombie`
   Extra adattag: root jogunk van-e (true/false)

Kiíráskor minden esetben írd ki az extra adatot is!

### A szerver osztály

Készíts egy `C2Server` osztályt, amely a zombikat tárolja és irányítja. Kezdetben a gépek adatait a `zombies.txt` állományból olvassuk be. Lásd lentebb, miket tud a szerver csinálni.

### Parancsszkript feldolgozása

A program egy második állományt is beolvas, `commands.txt` néven.
Ez a fájl soronként olyan szöveges parancsokat tartalmaz, amelyeket a `C2Server` egymás után végrehajt. A parancsok mindig egy szóból állnak, némelyiknek pedig van paramétere is.

Például:

```text
PRINT_STATUS
DDOS 1.2.3.4
PRINT_OFFLINE
DELETE_OFFLINE
PRINT_STATUS
```

Támogatott parancsok:

- `PRINT_STATUS` – az összes zombi adatait kiírja
- `PRINT_ONLINE` - kiírja az online zombik adatait
- `PRINT_OFFLINE` - kiírja az offline zombik adatait
- `SET_CPU <IP> <CPU_PERCENTAGE>` – módosítja a CPU terhelést az adott IP című gépnek
  - ha nem létezik ilyen IP című gép, dobjon kivételt
- `GET_LINUX` – csak a Linux alapú zombikat listáját téríti vissza
- `GET_WINDOWS` – csak a Windows OS-es zombik listáját téríti vissza
- `DDOS <IP>` – szimulált támadást indít a megadott IP cím ellen csak az online zombik segítségével:
  - ha a CPU terheltség > 90% → túlterhelődött → offline, máskülönben online-nak számít
  - DDoS közben a gépek CPU terhelése felmegy 45%-kal. Vigyázzunk, hogy a CPU terhelése nem mehet 100% felé.
- `DELETE_OFFLINE` - törli az offline zombikat

### Példa main.cpp teszeléshez

```cpp
int main()
{
    C2Server server;

    // Parancsok feldolgozása
    server.processCommands("commands.txt");

    return 0;
}

```

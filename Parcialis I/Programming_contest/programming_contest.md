# Programozói verseny

Ebben a feladatban egy **programozói verseny rendszerét** kell modellezned két osztály segítségével:

- `Task`, ami egy versenyfeladatot ír le,
- `Contest`, ami egy teljes versenyt modellez, amely több feladatot tartalmaz.

---

## `Task` osztály

A `Task` osztály egyetlen versenyfeladatot ír le. Minden feladatról a következő adatokat kell tárolni:

- azonosító (ID), ami automatikusan és inkrementálisan generálódik
- név, azaz a feladat neve, pl. "Legrövidebb utak"
- kategóriák (több is lehet), pl. "feszítőfa", "dinamikus programozás", stb.
- nehézség (1–10 közötti szám)
- pontszám, amit a feladat ér (pl. 100 pont)

A `Task` osztály feladatai:

- Az **ID** automatikusan generálódik minden új feladathoz.
- Legyen **copy constructor és assignment operator**, hogy a feladatok másolhatók legyenek.
- Két `Task` akkor tekinthető **azonosnak**, ha ugyanaz az ID-juk.
- Biztosítsunk módot arra, hogy a **nehézségi szintet kategorizálni** is tudjuk a pontszám szerint. Azaz szükségünk lesz egy olyan függvényre, ami a szint szöveges leírását visszatéríti:
  - pl. "_könnyű_", ha a nehézségi foka 1-3 között van, "_közepes_", ha 4-7, és "_nehéz_", ha 8-10.
- A `<<` operátorral lehessen szépen **kiírni** a feladatot, a következő sablon szerint, a feladatok között hagyjunk egy-egy új sort elválasztóként:

  ```
  [ID: <id>] <feladat_neve>
  Kategoria: <kategoria_1>, <kategoria_2>
  Nehézség: <szam> (<nehezseg_kategoria>) | Pont: <pontszam>
  ```

  egy konkrét példa:

  ```
  [ID: 1] Legrovidebb utak
  Kategoria: algoritmus, feszitofa
  Nehézség: 7 (közepes) | Pont: 100
  ```

## A `Contest` osztály

A `Contest` osztály a versenyt modellezi, amely több `Task`-ot tartalmaz.

A `Contest` osztály képes kell legyen a következőekre:

- Új feladat **hozzáadása**:

  - Egy új `Task` objektumot lehet a versenyhez adni
  - Ha már létezik azonos ID-jú feladat, kivételt dob.

- Feladat **törlése ID alapján**:

  - Ha nincs ilyen feladat, szintén kivétel dobódik.

- **Keresés kategória alapján**, ami visszaadja az adott kategóriába tartozó feladatokat.

- **Átlagos nehézség** kiszámítása: a versenyben szereplő feladatok átlagos nehézségét.

- **Összpontszám** kiszámítása.

- Legnehezebb feladat **keresése**:

  - Visszaad egy legmagasabb nehézségű feladatot.
  - Ha több van, akkor ezek közül bármelyiket visszatérítheti.

- **Rendezés** pontszám szerint: növekvő sorrendbe rendezi a feladatokat a pontszámuk alapján.

- Készíts **másoló konstruktort és értékadó operátort** (`operator=`), hogy egy verseny másolható legyen.

- Verseny **kiírása**: a `<<` operátor segítségével lehessen a verseny összes feladatát kiírni.

## main.cpp teszteléshez

```cpp
#include <iostream>
#include "Task.h"
#include "Contest.h"


int main()
{
	Contest c("ECN 2025");

	Task t1("Pizza", "dinamikus programozas, algoritmus", 7, 65);
	Task t2("Szamjegyek osszege", "algoritmus", 1, 10);
	Task t3("Legrovidebb utak", "algoritmus, feszitofa", 8, 80);
	Task t4("Graf bejaras", "algoritmus", 8, 80);
	Task t5("Leghosszabb kozos szekvencia", "greedy", 4, 50);

	c.addTask(t1);
	c.addTask(t2);
	c.addTask(t3);
	c.addTask(t4);
	c.addTask(t5);

	std::cout << c;

	std::cout << "--------------------------\n";
	std::cout << "Legnehezebb feladat:\n"
			  << c.getHardestTask() << "\n";

	std::cout << "--------------------------\n";
	std::cout << "Atlagos nehezseg: " << c.averageDifficulty() << "\n\n";
	std::cout << "--------------------------\n";
	std::cout << "Osszpontszám: " << c.totalPoints() << "\n\n";

	std::cout << "--------------------------\n";
	std::cout << "Algoritmus kategoria feladatai:\n";
	auto algoTasks = c.searchByCategory("algoritmus");
	for (const auto &t : algoTasks)
		std::cout << t << "\n";

	std::cout << "--------------------------\n";
	std::cout << "Feladatok rendezese pontszám szerint\n";
	c.sortByPoints();
	std::cout << c << "\n";

	std::cout << "--------------------------\n";
	std::cout << "Feladat torlese (ID=2)\n";
	c.removeTask(2);
	std::cout << c << "\n";

	std::cout << "Nem letezo feladat torlese\n";
	try
	{
		c.removeTask(10);
	}
	catch (const std::exception &e)
	{
		std::cout << "Hiba elkapva: " << e.what() << "\n\n";
	}

	std::cout << "--------------------------\n";
	std::cout << "Verseny masolasa...\n";
	Contest copied = c;
	std::cout << "Masolat tartalma:\n"
			  << copied << "\n";

	return 0;
}

```

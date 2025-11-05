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
#include "Contest.h"
#include <algorithm>
#include <stdexcept>

Contest::Contest(const std::string &name) : name(name) {}

Contest::Contest(const Contest &other) : name(other.name), tasks(other.tasks) {}

Contest &Contest::operator=(const Contest &other)
{
	if (this != &other)
	{
		name = other.name;
		tasks = other.tasks;
	}
	return *this;
}

void Contest::addTask(const Task &task)
{
	for (const auto &t : tasks)
	{
		// a Task osztályban definiált == operátor alapján ellenőrizzük az egyedi ID-t
		// a vagy két feladat akkor egyenlő, ha azonos az ID-jük
		if (t == task)
		{
			throw std::runtime_error("Mar letezik ilyen ID-ju feladat");
		}
	}
	tasks.push_back(task);
}

void Contest::removeTask(int id)
{
	auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task &t)
						   { return t.getId() == id; });
	if (it == tasks.end())
	{
		throw std::runtime_error("Nem talalhato feladat ezzel az ID-val");
	}
	tasks.erase(it);
}

std::vector<Task> Contest::searchByCategory(const std::string &category) const
{
	std::vector<Task> result;
	for (const auto &t : tasks)
	{
		if (t.getCategory().find(category) != std::string::npos)
		{
			result.push_back(t);
		}
	}
	return result;
}

// átlagszámítás, tehát float vagy double visszatérési típus szükséges
double Contest::averageDifficulty() const
{
	if (tasks.empty())
		return 0.0;
	double sum = 0.0;
	for (const auto &t : tasks)
	{
		sum += t.getDifficulty();
	}
	return sum / tasks.size();
}

int Contest::totalPoints() const
{
	int sum = 0;
	for (const auto &t : tasks)
	{
		sum += t.getPoints();
	}
	return sum;
}

Task Contest::getHardestTask() const
{
	if (tasks.empty())
	{
		throw std::runtime_error("Nincs egy feladat se bevezetve a versenyen");
	}
	return *std::max_element(tasks.begin(), tasks.end(), [](const Task &a, const Task &b)
							 { return a.getDifficulty() < b.getDifficulty(); });
}

void Contest::sortByPoints()
{
	std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b)
			  { return a.getPoints() < b.getPoints(); });
}

std::ostream &operator<<(std::ostream &os, const Contest &contest)
{
	os << contest.name << "\n";
	for (const auto &t : contest.tasks)
	{
		os << t << "\n";
	}
	return os;
}
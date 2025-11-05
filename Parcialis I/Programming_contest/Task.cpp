#include "Task.h"
#include <stdexcept>

int Task::nextId = 0;

Task::Task(const std::string &name, const std::string &category, int difficulty, int points)
	: id(++nextId), name(name), category(category), difficulty(difficulty), points(points)
{
	if (difficulty < 1 || difficulty > 10)
	{
		throw std::invalid_argument("A nehezsegnek 1 es 10 kozott kell lennie");
	}
	if (points < 0)
	{
		throw std::invalid_argument("A pontszam nem lehet negativ");
	}
}

// feladatot másolunk, nem kell új id-t generálni, sem növelni a nextId-t
Task::Task(const Task &other)
	: id(other.id), name(other.name), category(other.category), difficulty(other.difficulty), points(other.points) {}

// feladatot másolunk, nem kell új id-t generálni, sem növelni a nextId-t
Task &Task::operator=(const Task &other)
{
	if (this != &other)
	{
		id = other.id;
		name = other.name;
		category = other.category;
		difficulty = other.difficulty;
		points = other.points;
	}
	return *this;
}

bool Task::operator==(const Task &other) const
{
	return id == other.id;
}

std::string Task::getDifficultyCategory() const
{
	if (difficulty >= 1 && difficulty <= 3)
		return "konnyu";
	else if (difficulty >= 4 && difficulty <= 7)
		return "kozepes";
	else
		return "nehez";
}

std::ostream &operator<<(std::ostream &os, const Task &task)
{
	os << "[ID: " << task.id << "] " << task.name << "\n";
	os << "Kategoria: " << task.category << "\n";
	os << "Nehézség: " << task.difficulty << " (" << task.getDifficultyCategory() << ") | Pont: " << task.points << "\n";
	return os;
}
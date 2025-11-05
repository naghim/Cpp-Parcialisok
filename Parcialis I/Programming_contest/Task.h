#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>

class Task
{
private:
	static int nextId;
	int id;
	std::string name;
	std::string category;
	int difficulty;
	int points;

public:
	Task(const std::string &name, const std::string &category, int difficulty, int points);
	Task(const Task &other);

	Task &operator=(const Task &other);
	bool operator==(const Task &other) const;

	std::string getDifficultyCategory() const;
	int getId() const { return id; }
	std::string getName() const { return name; }
	std::string getCategory() const { return category; }
	int getDifficulty() const { return difficulty; }
	int getPoints() const { return points; }

	friend std::ostream &operator<<(std::ostream &os, const Task &task);
};

#endif // TASK_H
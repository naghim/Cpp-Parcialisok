#ifndef CONTEST_H
#define CONTEST_H

#include <string>
#include <vector>
#include <iostream>
#include "Task.h"

class Contest
{
private:
    std::string name;
    std::vector<Task> tasks;

public:
    Contest(const std::string &name);
    Contest(const Contest &other);
    Contest &operator=(const Contest &other);
    void addTask(const Task &task);
    void removeTask(int id);
    std::vector<Task> searchByCategory(const std::string &category) const;
    double averageDifficulty() const;
    int totalPoints() const;
    Task getHardestTask() const;
    void sortByPoints();
    friend std::ostream &operator<<(std::ostream &os, const Contest &contest);
};

#endif // CONTEST_H
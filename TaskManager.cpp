#include "TaskManager.h"

using std::cout;
using std::endl;

void TaskManager::assignTask(const string &personName, const Task &task) {
    Task toAdd = task;
    toAdd.setId(newTaskId);
    newTaskId++;
    for (int i = 0; i < numOfPeople; ++i) {
        if (people[i].getName() == personName) {
            people[i].assignTask(toAdd);
            return;
        }
    }
    if (numOfPeople != MAX_PERSONS) {
        Person personToAdd(personName);
        personToAdd.assignTask(toAdd);
        numOfPeople++;
        people[numOfPeople - 1] = personToAdd;
    } else {
        throw std::runtime_error("Task Manager Maxed Out");
    }
}

void TaskManager::completeTask(const string &personName) {
    for (int i = 0; i < numOfPeople; ++i) {
        if (people[i].getName() == personName) {
            people[i].completeTask();
            return;
        }
    }
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if (priority < 0) {
        return;
    }
    for (int i = 0; i < numOfPeople; ++i) {
        SortedList<Task> currList = people[i].getTasks();
        SortedList<Task> newList = currList.apply([&priority, &type](const Task& task){
            if (type == task.getType()){
                string prevDescription = task.getDescription();
                int updatedPriority = task.getPriority()+priority;
                Task updatedTask = Task(updatedPriority, type,prevDescription);
                updatedTask.setId(task.getId());
                return updatedTask;
            } else {
                return Task(task);
            }
        }
        );
        people[i].setTasks(newList);
    }
}

void TaskManager::printAllEmployees() const {
    for (int i = 0; i < numOfPeople; ++i) {
        cout << this->people[i] << endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> listOfAllTasks = this->allManagerTasksSorted();
    SortedList<Task> filteredTasks = listOfAllTasks.filter(isFromType(type));
    for (const Task& currTask : filteredTasks) {
        cout << currTask << endl;
    }
}

void TaskManager::printAllTasks() const {
    SortedList<Task> listOfAllTasks = this->allManagerTasksSorted();
    for (const Task& currTask : listOfAllTasks) {
        cout << currTask << endl;
    }
}

//--------------- Helper Functions -----------------------------

SortedList<Task> TaskManager::allManagerTasksSorted() const{
    SortedList<Task> listOfAllTasks;
    for (const Person& currPerson : people) {
        for (const Task& currTask : currPerson.getTasks()) {
            listOfAllTasks.insert(currTask);
        }
    }
    return listOfAllTasks;
}
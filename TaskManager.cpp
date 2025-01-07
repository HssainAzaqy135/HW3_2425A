#include "TaskManager.h"

void TaskManager::assignTask(const string &personName, const Task &task) {
    for (int i = 0; i < numOfPeople; ++i) {
        if (people[i].getName() == personName) {
            Task toAdd = task;
            toAdd.setId(newTaskId);
            newTaskId++;
            people[i].assignTask(toAdd);
            return;
        }
    }
    if (numOfPeople != MAX_PERSONS) {
        Person personToAdd(personName);
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
            if(type == task.getType()){
                string prevDescription = task.getDescription();
                int updatedPriority = task.getPriority()+priority;
                Task updatedTask = Task(updatedPriority, type,prevDescription);
                return updatedTask;
            } else {
                return Task(task);
            }
        }
        );
        people[i].setTasks(newList);
    }
}


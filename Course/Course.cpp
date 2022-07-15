
#include "Course.hpp"

static ll count = 0;

Course::Course(std::set<TimeWindow, TWComparator> time_windows, std::string name){
    this->time_windows = time_windows;
    this->name = name;
    this->id = this->generateId();
}

Course::Course(const Course& other){
    this->time_windows = other.time_windows;
    this->name = other.name;
    this->id = other.id;
    count++;
}

Course::~Course(){
    count--;
}

ll Course::generateId(){
    count++;
    return count;
}

ll Course::getId(){
    return this->id;
}

std::set<TimeWindow, TWComparator> Course::getTimes(){
    return this->time_windows;
}

std::string Course::getName(){
    return this->name;
}

void Course::addTimeWindow(TimeWindow timeWindow){
    this->time_windows.insert(timeWindow);
}

void Course::removeTimeWindow(TimeWindow timeWindow){
    this->time_windows.erase(timeWindow);
}
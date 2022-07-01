
#ifndef COURSE_H
#define COURSE_H
#define ll long long

#include "../TimeWindow/TimeWindow.hpp"
#include <string>
#include <vector>

class Course {

private:
    ll id;
    std::string name;
    std::set<TimeWindow, TWComparator> time_windows;

public:
    Course(std::set<TimeWindow> time_windows, std::string name, int id);
    std::set<TimeWindow, TWComparator> getTimes();
    std::string getName();
    int getId();
    void addTimeWindow(TimeWindow time_window);
    void removeTimeWindow(TimeWindow time_window);
};



#endif
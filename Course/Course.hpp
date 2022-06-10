
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
    std::vector<TimeWindow> time_windows;

public:
    Course(std::vector<TimeWindow> time_windows, std::string name, int id);
    std::vector<TimeWindow> getTimes();
    std::string getName();
    int getId();
    void addTimeWindow(TimeWindow time_window);
    void removeTimeWindow(TimeWindow time_window);
};



#endif
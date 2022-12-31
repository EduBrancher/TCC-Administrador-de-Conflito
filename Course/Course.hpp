
#ifndef COURSE_H
#define COURSE_H
#define ll long long

#include "../TimeWindow/TimeWindow.hpp"
#include <string>
#include <vector>
#include <set>



class Course {

private:
    ll id;
    std::string name;
    std::set<TimeWindow, TWComparator> time_windows;
    static ll count;

public:
    Course(std::set<TimeWindow, TWComparator> time_windows, std::string name);
    Course(const Course& other);
    ~Course();
    std::set<TimeWindow, TWComparator> getTimes();
    std::string getName() const;
    ll generateId();
    ll getId() const;
    void addTimeWindow(TimeWindow time_window);
    void removeTimeWindow(TimeWindow time_window);
    std::string to_string();
};

struct CourseComparator{
    bool operator () (const Course left, const Course right) const{
        return left.getId() < right.getId();
    }
};

#endif
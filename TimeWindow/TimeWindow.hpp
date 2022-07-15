
#ifndef TIMEWINDOW_H
#define TIMEWINDOW_H

#include <string>
#include <map>
#include <chrono>
#define ll long long

class TimeWindow {

private:
    int start_hour;
    int end_hour;
    int week_day;
    ll id;
    ll generateId() const;
    static ll count;

public:
    TimeWindow(int start_hour, int end_hour, std::string weekday, ll id);
    TimeWindow(const TimeWindow& other);
    ~TimeWindow();
    int getStartingHour() const;
    ll getId() const;
    int getEndingHour() const;
    int getWeekday() const;
    int getDuration() const;
    std::string toString() const;
    bool clashes(TimeWindow other) const;
    //maybe move this implementation to the .cpp?
    bool operator == (const TimeWindow other) const{
        return (this->getId() == other.getId()); 
    }; 
};

struct TWComparator {
    bool operator() (TimeWindow lhs, TimeWindow rhs) const {
        return lhs.getId() < rhs.getId();
    }
};

#endif
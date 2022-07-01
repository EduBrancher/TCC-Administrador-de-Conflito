
#ifndef TIMEWINDOW_H
#define TIMEWINDOW_H

#include <string>
#include <map>
#include <chrono>



const std::map<std::string, int> Weekday{
    {"Monday", 0}, {"Tuesday", 1}, {"Wednesday", 2}, {"Thursday", 3},
    {"Friday", 4}, {"Saturday", 5}, {"Sunday", 6} 
};

class TimeWindow {

private:
    int start_hour;
    int end_hour;
    int week_day;
    ll id;
    
public:
    TimeWindow(int start_hour, int end_hour, string weekday, ll id);
    int getStartingHour() const;
    ll getId() const;
    int getEndingHour() const;
    int getWeekday() const;
    TimeWindow getDuration() const;
    std::string toString();
    //maybe move this implementation to the .cpp?
    bool operator == (const TimeWindow other){
        return (this->getId() == other.getId()); 
    }; 
};

//maybe move this to the .cpp file later - it looks improper here as it is actual implementation
//although since this is an "auxiliary definition" for this class maybe it should stay here
struct TWComparator {
    bool operator() (TimeWindow lhs, TimeWindow rhs) const {
        return lhs.getId() < rhs.getId();
    }
};

#endif

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
    
public:
    TimeWindow(int start_hour, int end_hour, string weekday);
    int getStartingHour();
    int getEndingHour();
    int getWeekday();
    TimeWindow getDuration();
    std::string toString();
};


#endif

#ifndef TIMEWINDOW_H
#define TIMEWINDOW_H

#include <string>
#include <chrono>

class TimeWindow {

private:
    int start_hour;
    int end_hour;
    std::chrono::weekday week_day;
    
public:
    TimeWindow(int start_hour, int end_hour, std::set<string> weekdays);
    int getStartingHour();
    int getEndingHour();
    std::chrono::weekday getWeekday();
    TimeWindow getDuration();
    std::string toString();
};


#endif
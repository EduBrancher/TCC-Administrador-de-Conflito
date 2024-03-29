
#ifndef TIMEWINDOW_HPP
#define TIMEWINDOW_HPP

#include <string>
#include <map>
#include <chrono>
#define ll long long

extern std::map< std::string, int > Weekday;
extern std::map< int, std::string > invWeekday;

class TimeWindow {

private:
    int start_hour;
    int end_hour;
    int week_day;
    ll id;
    ll generateId() const;
    static ll count;

public:
    TimeWindow(int start_hour, int end_hour, std::string weekday);
    TimeWindow(const TimeWindow& other);
    TimeWindow();
    ~TimeWindow();
    int getStartingHour() const;
    ll getId() const;
    int getEndingHour() const;
    int getWeekday() const;
    int getDuration() const;
    std::string to_string() const;
    bool clashes(TimeWindow other) const;
    bool equalTo(TimeWindow other) const;
    //maybe move this implementation to the .cpp?
    bool operator == (const TimeWindow other) const{
        return (this->getId() == other.getId()); 
    }; 
};

struct TWComparator {
    bool operator() (const TimeWindow lhs, const TimeWindow rhs) const {
        return lhs.getId() != rhs.getId();
    } 
};

struct TWComparator2 {
    bool operator() (const TimeWindow lhs, const TimeWindow rhs) const {
        if (lhs.getWeekday() == rhs.getWeekday()){
            if (lhs.getStartingHour() == rhs.getStartingHour()){
                return (lhs.getEndingHour() < rhs.getEndingHour());
            }
            else{
                return lhs.getStartingHour() < rhs.getStartingHour();
            }
        }
        return (lhs.getWeekday() < rhs.getWeekday());
    }
};

#endif
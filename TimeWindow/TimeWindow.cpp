#include <string>
#include <map>
#include <chrono>
#include <algorithm>
#include "TimeWindow.hpp"

ll TimeWindow::count = 0;

std::map< std::string, int > Weekday{
    {"monday", 0}, {"tuesday", 1}, {"wednesday", 2}, {"thursday", 3},
    {"friday", 4}, {"saturday", 5}, {"sunday", 6} 
};

std::map< int, std::string > invWeekday{
    {0, "monday"}, {1, "tuesday"}, {2, "wednesday"}, {3, "thursday"},
    {4, "friday"}, {5, "saturday"}, {6, "sunday"} 
};

TimeWindow::TimeWindow(int start_hour, int end_hour, std::string weekday, ll id){
    this->start_hour = start_hour;
    this->end_hour = end_hour;
    std::transform(weekday.begin(), weekday.end(), weekday.begin(), ::tolower);
    int week_day = Weekday["sunday"];
    this->week_day = week_day;
    this->id = this->generateId();
}

TimeWindow::TimeWindow(const TimeWindow& other){
    this->start_hour = other.start_hour;
    this->end_hour = other.end_hour;
    this->week_day = other.week_day;
    this->id = other.id;
    //this is only required because of the count!
    //what would happen without this: whenever we pass an object by value,
    //it would be deleted at the end of it's lifecycle. Then, our destructor
    //will decrement count. This would generate a mistake when assigning an ID
    //to a new object, as the count is suddenly lower owing to the deletion of
    //the copy. Therefore, we have to increment count when passing by value.
    //Since pass by value calls the copy constructor, we have to generate one
    //by hand, as the compiler-generated copy constructor will not increment count.
    count++;
}

TimeWindow::~TimeWindow(){
    count--;
}

ll TimeWindow::generateId() const{
    count++;
    return count;
}

int TimeWindow::getStartingHour() const{
    return this->start_hour;
}

int TimeWindow::getEndingHour() const{
    return this->end_hour;
}
int TimeWindow::getWeekday() const{
    return this->week_day;
}
int TimeWindow::getDuration() const{
    return this->end_hour - this->start_hour;
}

bool TimeWindow::clashes(TimeWindow other) const{
    if (this->getWeekday() != other.getWeekday()){
        return false;
    }
    if (this->getEndingHour() <= other.getStartingHour() || 
        this->getStartingHour() >= other.getEndingHour()){
        return false;
    }
    return true;
}

std::string TimeWindow::toString() const{
    std::string ans;
    ans = "TimeWindow of id " + std::to_string(this->getId());
    ans = ans + " starts at " + std::to_string(this->getStartingHour());
    ans = ans + " and ends at " + std::to_string(this->getEndingHour());
    ans = ans + " on " + invWeekday[this->getWeekday()];
    ans = ans + " with duration of " + std::to_string(this->getDuration()) + ".\n";
    return ans;
}

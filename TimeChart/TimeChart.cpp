#include "TimeChart.hpp"

using namespace std;

set<Student> students;
TimeChart timeChart(students);

TimeChart::TimeChart(set<Student> students){
    this->students = students;
}

set<Student> TimeChart::getStudents(){
    return this->students;
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 24; j++){
            this->chart[i][j] = set<Course>();
        }
    }
}

void TimeChart::setCourseAtWindow(Course course, TimeWindow timeWindow){
    int weekday = timeWindow.getWeekday();
    int startingHour = timeWindow.getStartingHour();
    int endingHour = timeWindow.getEndingHour();
    for (int i = startingHour; i <= endingHour; i++){
        this->chart[weekday][i].insert(course);
    }
}

set<Course> TimeChart::getCoursesAtWindow(TimeWindow timeWindow){
    set<Course> coursesAtWindow;
    int weekday = timeWindow.getWeekday();
    int startingHour = timeWindow.getStartingHour();
    int endingHour = timeWindow.getEndingHour();
    for (int i = startingHour; i <= endingHour; i++){
        for (auto course : this->chart[weekday][i]){
            coursesAtWindow.insert(course);
        }
    }
    return coursesAtWindow;
}

void TimeChart::swapCourses(Course firstCourse, TimeWindow firstWindow, 
    Course secondCourse, TimeWindow secondWindow){
        //fix courses
        firstCourse.removeTimeWindow(firstWindow);
        firstCourse.addTimeWindow(secondWindow);
        secondCourse.addTimeWindow(firstWindow);
        secondCourse.removeTimeWindow(secondWindow);
        //fix chart at first timewindow
        int weekday = firstWindow.getWeekday();
        int startingHour = firstWindow.getStartingHour();
        int endingHour = firstWindow.getEndingHour();
        for (int i = startingHour; i <= endingHour; i++){
            this->chart[weekday][i].erase(firstCourse);
            this->chart[weekday][i].insert(secondCourse);
        }
        //fix chart at second timewindow
        int weekday = secondWindow.getWeekday();
        int startingHour = secondWindow.getStartingHour();
        int endingHour = secondWindow.getEndingHour();
        for (int i = startingHour; i <= endingHour; i++){
            this->chart[weekday][i].erase(secondCourse);
            this->chart[weekday][i].insert(firstCourse);
        }
        

    }
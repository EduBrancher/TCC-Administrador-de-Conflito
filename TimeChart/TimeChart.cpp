#include "TimeChart.hpp"

using namespace std;

set<Student> students;
TimeChart timeChart(students);

TimeChart::TimeChart(set<Student> students){
    this->students = students;
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 24; j++){
            this->chart[i][j] = set<Course>();
        }
    }
}

set<Student> TimeChart::getStudents(){
    return this->students;
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
//for a given time window, check how many students have conflicts by being 
//alumni of a pair of disciplines that are taught in that window.
int TimeChart::findConflicts(std::set<Student> students, TimeWindow timeWindow){
    int conflicts = 0;

    for (auto student : students){
        std::set<TimeWindow, TWComparator> studentWindows;
        std::set<Course> studentCourses = student.getCourses();

        for (auto course : studentCourses){
            std::set<TimeWindow, TWComparator> courseWindows = course.getTimes();

            for (auto window : courseWindows){
                std::set<TimeWindow, TWComparator>::iterator it = studentWindows.find(window);

                if (it != studentWindows.end()){ //TimeWindow is already present in the set
                    conflicts++;
                    break;
                }
                else{
                    studentWindows.insert(window); //add this window to set if not there
                } 
            }
        }
    }
    return conflicts;
}
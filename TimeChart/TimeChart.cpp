#include "TimeChart.hpp"

using namespace std;

set<Student, StudentComparator> students;
TimeChart timeChart(students);

TimeChart::TimeChart(set<Student, StudentComparator> students){
    this->students = students;
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 24; j++){
            this->chart[i][j] = set<Course, CourseComparator>();
        }
    }
}

set<Student, StudentComparator> TimeChart::getStudents(){
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

void TimeChart::removeCourseAtWindow(Course course, TimeWindow timeWindow){
    int weekday = timeWindow.getWeekday();
    int startingHour = timeWindow.getStartingHour();
    int endingHour = timeWindow.getEndingHour();
    for (int i = startingHour; i <= endingHour; i++){
        this->chart[weekday][i].erase(course);
    }
}

set<Course, CourseComparator> TimeChart::getCoursesAtWindow(TimeWindow timeWindow){
    set<Course, CourseComparator> coursesAtWindow;
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
//Check how many conflicts there are by gathering all the time windows of a given student,
//then checking how many of these time windows overlap. Repeat this for all students. 
int TimeChart::findConflicts(std::set<Student> students){
    int conflicts = 0;

    for (auto student : students){
        std::set<TimeWindow, TWComparator> studentWindows;
        std::set<Course, CourseComparator> studentCourses = student.getCourses();

        for (auto course : studentCourses){
            std::set<TimeWindow, TWComparator> courseWindows = course.getTimes();

            for (auto window : courseWindows){
                studentWindows.insert(window);
            }
        }

        for (auto window : studentWindows){
            for (auto window2 : studentWindows){
                if (window.getId() == window2.getId()) continue;
                if (window.clashes(window2)){
                    conflicts++;
                }
            }
        }
    }
    return conflicts;
}
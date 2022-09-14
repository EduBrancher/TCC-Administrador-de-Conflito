#include "TimeChart.hpp"
#include <iostream>

using namespace std;

TimeChart::TimeChart(){
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 24; j++){
            this->chart[i][j] = set<Course, CourseComparator>();
        }
    }
}

TimeChart::TimeChart(set<Student, StudentComparator> students){
    this->students = students;
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 24; j++){
            this->chart[i][j] = set<Course, CourseComparator>();
        }
    }
}

void TimeChart::addCourse(Course& course){
    set<TimeWindow, TWComparator> courseWindows = course.getTimes();
    for (TimeWindow window : courseWindows){
        this->setCourseAtWindow(course, window);
    }
}

void TimeChart::removeCourse(Course course){
    set<TimeWindow, TWComparator> courseWindows = course.getTimes();
    for (TimeWindow window: courseWindows){
        this->removeCourseAtWindow(course, window);
    }
}

void TimeChart::addStudent(Student& student){
    this->students.insert(student);
}

void TimeChart::removeStudent(Student student){
    this->students.erase(student);
}

set<Student, StudentComparator> TimeChart::getStudents(){
    return this->students;
}

void TimeChart::setCourseAtWindow(Course& course, TimeWindow timeWindow){
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
        weekday = secondWindow.getWeekday();
        startingHour = secondWindow.getStartingHour();
        endingHour = secondWindow.getEndingHour();
        for (int i = startingHour; i <= endingHour; i++){
            this->chart[weekday][i].erase(secondCourse);
            this->chart[weekday][i].insert(firstCourse);
        }
        

    }
//Check how many conflicts there are by gathering all the time windows of a given student,
//then checking how many of these time windows overlap. Repeat this for all students. 
int TimeChart::findConflicts(){
    int conflicts = 0;
    std::set<Student, StudentComparator> students = this->students;

    for (auto student : students){
        std::set<TimeWindow, TWComparator> studentWindows;
        std::set<Course, CourseComparator> studentCourses = student.getCourses();

        for (auto course : studentCourses){
            std::set<TimeWindow, TWComparator> courseWindows = course.getTimes();

            for (auto window : courseWindows){
                studentWindows.insert(window);
            }
        }

        for (std::set<TimeWindow, TWComparator>::iterator it = studentWindows.begin(); 
             it != studentWindows.end(); ++it){
            for (std::set<TimeWindow, TWComparator>::iterator it2 = std::next(it);
                 it2 != studentWindows.end(); ++it2){
                //if ((*it).getId() == (*it2).getId()) continue;
                if ((*it).clashes((*it2))){
                    conflicts++;
                }
            }
        }
    }
    return conflicts;
}

void TimeChart::printChart(){
    for (int i = 0; i < 7; i++){
        string weekday = invWeekday[i];
        std::cout << weekday << ":" << endl;
        std::cout << endl;
        for (int j = 0; j < 24; j++){
            if (j / 10 == 0){
                    std::cout << 0;
                }
            std::cout << j << ":" << "00 - " ;
            for (Course course : chart[i][j]){
                std::cout << course.getName() << ", ";
            }
            std::cout << endl;
        }
        std::cout << endl;
    }
}
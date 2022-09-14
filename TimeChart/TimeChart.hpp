

#ifndef TIMECHART_H
#define TIMECHART_H

#include <set>
#include "../Course/Course.hpp"
#include "../Student/Student.hpp"


class TimeChart {

private:
    std::set<Course, CourseComparator> chart[7][24];
    std::set<Student, StudentComparator> students;
public:
    TimeChart(std::set<Student, StudentComparator> students);
    TimeChart();
    void setCourseAtWindow(Course& course, TimeWindow time_window);
    void removeCourseAtWindow(Course course, TimeWindow time_window);
    void addCourse(Course& course);
    void removeCourse(Course course);
    void addStudent(Student& student);
    void removeStudent(Student student);
    std::set<Course, CourseComparator> getCoursesAtWindow(TimeWindow time_window);
    std::set<Student, StudentComparator> getStudents();
    void swapCourses(Course first_course, TimeWindow first_window, 
    Course second_course, TimeWindow second_window);
    int findConflicts();
    void printChart();
};

#endif


#ifndef TIMECHART_H
#define TIMECHART_H

#include <set>
#include "../Course/Course.hpp"
#include "../Student/Student.hpp"


class TimeChart {

private:
    std::set<Course> timechart[24][7];
    std::set<Student> students;
public:
    TimeChart(std::set<Student> students);
    void setCourseAtWindow(Course course, TimeWindow time_window);
    std::set<Course> getCoursesAtWindow(TimeWindow time_window);
    std::set<Student> getStudents();
    void swapCourses(Course first_course, TimeWindow first_window, 
    Course second_course, TimeWindow second_window);
    int findConflicts(std::set<Student> students, TimeWindow time_window);
};

#endif
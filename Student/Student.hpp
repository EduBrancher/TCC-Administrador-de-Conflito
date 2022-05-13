
#ifndef STUDENT_H
#define STUDENT_H

#define ll long long
#include "../Course/Course.hpp"
#include <set>



class Student {

private:
    ll id;
    std::set<Course> desired_courses;

public:
    Student(ll id, std::set<Course> desired_courses);
    std::set<Course> getCourses();
    int getId();
};

#endif
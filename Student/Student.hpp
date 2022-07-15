
#ifndef STUDENT_H
#define STUDENT_H

#define ll long long
#include "../Course/Course.hpp"
#include <set>

struct StudentComparator{
    bool operator()(Student a, Student b) const{
        return a.getId() < b.getId();
    }
};

class Student {

private:
    ll id;
    std::set<Course, CourseComparator> desired_courses;
    ll generateId() const;
    static size_t count;

public:
    Student(std::set<Course, CourseComparator> desired_courses);
    Student(const Student& other);
    ~Student();
    std::set<Course, CourseComparator> getCourses() const;
    ll getId() const;
};

#endif
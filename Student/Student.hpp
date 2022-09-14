
#ifndef STUDENT_H
#define STUDENT_H

#define ll long long
#include "../Course/Course.hpp"
#include <set>



class Student {

private:
    ll id;
    std::set<Course, CourseComparator> desired_courses;
    ll generateId() const;
    static ll count;

public:
    Student(std::set<Course, CourseComparator> desired_courses);
    Student(const Student& other);
    ~Student();
    std::set<Course, CourseComparator> getCourses() const;
    ll getId() const;
    std::string to_string() const;
};

struct StudentComparator{
    bool operator()(Student a, Student b) const{
        return a.getId() < b.getId();
    }
};

#endif
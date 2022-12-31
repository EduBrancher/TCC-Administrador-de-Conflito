
#ifndef STUDENT_H
#define STUDENT_H

#define ll long long
#include "../Course/Course.hpp"
#include <set>



class Student {

private:
    ll id;
    std::set<Course, CourseComparator> desired_courses;
    ll NUSP;
    ll generateId() const;
    static ll count;

public:
    Student(std::set<Course, CourseComparator> desired_courses);
    Student(std::set<Course, CourseComparator> desired_courses, ll NUSP);
    Student(const Student& other);
    ~Student();
    std::set<Course, CourseComparator> getCourses() const;
    ll getId() const;
    ll getNUSP() const;
    std::string to_string() const;
};

struct StudentComparator{
    bool operator()(const Student a, const Student b) const{
        return a.getId() < b.getId();
    }
};

#endif
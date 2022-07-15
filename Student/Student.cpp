

#include "Student.hpp"

ll static count = 0;

ll Student::generateId() const{
    count++;
    return count;
}

Student::Student(std::set<Course, CourseComparator> desired_courses){
    this->desired_courses = desired_courses;
    this->id = generateId();
}

Student::Student(const Student& other){
    this->desired_courses = other.desired_courses;
    this->id = other.id;
    count++;
}

Student::~Student(){
    count--;
}

std::set<Course, CourseComparator>Student::getCourses() const{
    return this->desired_courses;
}

ll Student::getId() const{
    return this->id;
}
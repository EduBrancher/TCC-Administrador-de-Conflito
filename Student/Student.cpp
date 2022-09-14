

#include "Student.hpp"

ll Student::count = 0;

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

std::string Student::to_string() const{
    std::string ans;
    ans = "Student of id " + std::to_string(this->getId());
    ans = ans + " with courses: \n";
    for (Course course : this->desired_courses){
        ans = ans + course.getName() + "\n";
    }
    return ans;
}
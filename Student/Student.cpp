

#include "Student.hpp"


ll Student::count = 0;

ll Student::generateId() const{
    count++;
    return count;
}

Student::Student(std::set<Course, CourseComparator> desired_courses){
    this->desired_courses = desired_courses;
    this->id = generateId();
    this->NUSP = -1;
}

Student::Student(std::set<Course, CourseComparator> desired_courses, ll NUSP){
    this->NUSP = NUSP;
    this->desired_courses = desired_courses;
    this->id = generateId();
}

Student::Student(const Student& other){
    this->desired_courses = other.desired_courses;
    this->id = other.id;
    this->NUSP = other.NUSP;
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

ll Student::getNUSP() const{
    return this->NUSP;
}


std::string Student::to_string() const{

    std::string ans;
    ans = "Student " + std::to_string(this->NUSP);
    ans = ans + " with courses: \n";
    for (Course course : this->desired_courses){
        ans = ans + course.getName() + "\n";
    }
    return ans;
}
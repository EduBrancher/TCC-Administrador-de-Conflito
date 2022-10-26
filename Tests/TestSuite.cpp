#include <bits/stdc++.h>
#include "../TimeWindow/TimeWindow.hpp"
#include "../TimeChart/TimeChart.hpp"
#include "../Terminal/Terminal.cpp"

using namespace std;

int passed = 0;
int failed = 0;


//Test 1: Check if a TimeWindow can be constructed
string TestTWConstructor(){
    string err;
    TimeWindow tw = TimeWindow(16, 17, "monday");
    int ret;
    string retstr;
    if ((ret = tw.getStartingHour()) != 16){
        failed++;
        return "Starting hour expected 16 on test 1, got " + to_string(ret);
    }
    if ((ret = tw.getEndingHour()) != 17){
        failed++;
        return "Ending hour expected 17 on test 1, got " + to_string(ret);
    }
    if (!((retstr = invWeekday[tw.getWeekday()]) == "monday")){
        failed++;
        return "week day expected monday on test 1, got " + retstr;
    }
    if ((ret = tw.getId()) != 1){
        failed++;
        return "Id expected 1 on test 1, got " + to_string(ret);
    }
    if ((ret = tw.getDuration()) != 1){
        failed++;
        return "Duration expected 1 on test 1, got " + to_string(ret);
    }
    passed++;
    return "";
}

//Test 2: Check if the automated ID generation solution for TimeWindows
//        adequately keeps track of living TimeWindows
string TestAutomatedIDGenerationTW(){
    string retstr;
    int ret;
    int ret2;
    for (int i = 0; i < 1; i++){
        //dummy loop creates local scope
        TimeWindow local1 = TimeWindow(10, 11, "monday");
        TimeWindow local2 = TimeWindow(12, 13, "tuesday");
        ret = local1.getId();
        ret2 = local2.getId();
        if (ret != 1){
            failed++;
            return "local1 ID expected 1 on test 2, got " + to_string(ret);
        }
        if (ret2 != 2){
            failed++;
            return "local2 ID expected 2 on test 2, got " + to_string(ret2);
        }
    }
    //dummy loop is ended, local1 and local2 should have been destroyed.
    TimeWindow tw = TimeWindow(14, 15, "wednesday");
    ret = tw.getId();
    if (ret != 1){
        failed++;
        return "tw ID expected 1 on test 2, got " + to_string(ret);
    }
    passed++;
    return "";
}

//Test 3: Tests if passing a TimeWindow as value to a function correctly updates
//id count
string TestIDAfterPassByValue(){
    string retstr;
    int ret;
    TimeWindow tw = TimeWindow(13, 14, "tuesday");
    ret = tw.getId();
    if (ret != 1){
        failed++;
        return "tw ID expected 1 on test 3, got " + to_string(ret);
    }
    ret = [](TimeWindow timewindow) {
        int ret;
        TimeWindow local = TimeWindow(12, 14, "friday");
        ret = local.getId();
        return ret;
    }(tw);
    if (ret != 3){
        failed++;
        return "tw ID expected to have reached 3, got " + to_string(ret);
    }
    passed++;
    return "";
}

//Test 4: Verify if the TimeWindow::clashes() method works correctly
string TestTimeWindowClash(){
    bool ret;
    string retstr;
    TimeWindow clashing1 = TimeWindow(12, 14, "monday");
    TimeWindow clashing2 = TimeWindow(12, 14, "monday");
    TimeWindow notclashingday = TimeWindow(12, 14, "tuesday");
    TimeWindow notclashingtime = TimeWindow(16, 18, "monday");
    ret = clashing1.clashes(clashing2);
    if (ret == false){
        failed++;
        return "Expected clashing true on test 4, got false";
    }
    ret = clashing2.clashes(clashing1);
    if (ret == false){
        failed++;
        return "Expected commutative behaviour on test 4, got false";
    }
    ret = clashing1.clashes(notclashingday);
    if (ret == true){
        failed++;
        return "Expected clashing false due to day on test 4, got true";
    }
    ret = clashing2.clashes(notclashingtime);
    if (ret == true){
        failed++;
        return "Expected clashing false due to time on test 4, got true";
    }
    passed++;
    return "";
}

//Test 5: Check if a Course can be set at a given time in the TimeChart and retrieved
string TestSetGetCourseToTimeChart(){
    set<Student, StudentComparator> students;
    TimeChart timeChart = TimeChart(students);
    set<TimeWindow, TWComparator> twSet;
    TimeWindow tw = TimeWindow(14, 16, "monday");
    twSet.insert(tw);
    Course course = Course(twSet, "MAC110");
    timeChart.setCourseAtWindow(course, tw);
    set<Course, CourseComparator> coursesAtWindow = timeChart.getCoursesAtWindow(tw);
    Course course1 = *(coursesAtWindow.begin());
    int ret;
    string retstr;
    ret = course1.getId();
    if (ret != 1){
        failed++;
        return "Expected Course ID 1 in test 5, got " + to_string(ret);
    }
    set<TimeWindow, TWComparator> retwindows = course1.getTimes();
    TimeWindow retwindow = *(retwindows.begin());
    ret = retwindow.getId();
    if (ret != 1){
        failed++;
        return "Expected TimeWindow ID 1 in test 5, got " + to_string(ret);
    }
    ret = retwindow.getStartingHour();
    if (ret != 14){
        failed++;
        return "Expected TimeWindow starting hour 14 in test 5, got " + to_string(ret);
    }
    ret = retwindow.getEndingHour();
    if (ret != 16){
        failed++;
        return "Expected TimeWindow starting hour 16 in test 5, got " + to_string(ret);
    }
    retstr = invWeekday[retwindow.getWeekday()];
    if (retstr != "monday"){
        failed++;
        return "Expected TimeWindow weekday to be monday, got " + retstr; 
    }
    passed++;
    return "";
}

string TestFindConflicts(){
string retstr;
    int ret;

    TimeWindow monday1 = TimeWindow(8, 10, "monday");
    TimeWindow monday2 = TimeWindow(10, 12, "monday");
    TimeWindow monday3 = TimeWindow(14, 16, "monday");
    TimeWindow monday4 = TimeWindow(16, 18, "monday");
    TimeWindow tue1 = TimeWindow(8, 10, "tuesday");
    TimeWindow tue2 = TimeWindow(10, 12, "tuesday");
    TimeWindow tue3 = TimeWindow(14, 16, "tuesday");
    TimeWindow tue4 = TimeWindow(16, 18, "tuesday");
    TimeWindow talk1 = TimeWindow(14, 15, "tuesday");
    TimeWindow ptWindow = TimeWindow(14, 17, "tuesday");
    TimeWindow wed1 = TimeWindow(8, 10, "wednesday");
    TimeWindow wed2 = TimeWindow(10, 12, "wednesday");
    TimeWindow wed3 = TimeWindow(14, 16, "wednesday");
    TimeWindow wed4 = TimeWindow(16, 18, "wednesday");
    TimeWindow thur1 = TimeWindow(8, 10, "thursday");
    TimeWindow thur2 = TimeWindow(10, 12, "thursday");
    TimeWindow thur3 = TimeWindow(14, 16, "thursday");
    TimeWindow thur4 = TimeWindow(16, 18, "thursday");
    TimeWindow talk2 = TimeWindow(14, 15, "thursday");
    TimeWindow fri1 = TimeWindow(8, 10, "friday");
    TimeWindow fri2 = TimeWindow(10, 12, "friday");
    //Monday:    08-10: MAC110, MAC0323, MAE0329, MAC0317
    //           10-12: MAC105, MAC0236, MAC0425
    //           14-16: MAT02453, MAE0221, MAC0219, MAC0444
    //           16-18: MAC0218

    //Tuesday:   08-10: MAC0329, MAC0210, MAT0236
    //           10-12: MAT0112, MAC0422 
    //           14-16: MAC0350, MAC0101,FLC0474, MAC0209, MAC0426, MAC0318
    //           16-18: FLC0474, MAC0318

    //Wednesday: 08-10: MAT02453, MAC0236, MAC0444
    //           10-12: MAC110, MAC0323, MAC0317
    //           14-16: MAE0221, MAE0329, MAC0219
    //           16-18: MAC0218

    //Thursday:  08-10: MAT0112, MAC0422, MAC0210, MAC0426
    //           10-12: MAC0329, MAT0236
    //           14-16: MAC0350, MAC0102
    //           16-18: MAC0105, MAC0209, MAC0425
    
    //Friday:    08-10: MAE0221, 
    //           10-12: MAT02453
    set<TimeWindow, TWComparator> MAC0110Times;//
    MAC0110Times.insert(monday1);
    MAC0110Times.insert(wed2);
    set<TimeWindow, TWComparator> MAC0105Times;//
    MAC0105Times.insert(monday2);
    MAC0105Times.insert(thur4);
    set<TimeWindow, TWComparator> MAC0329Times;//
    MAC0329Times.insert(tue1);
    MAC0329Times.insert(tue2);
    set<TimeWindow, TWComparator> MAC0210Times;//
    MAC0210Times.insert(tue1);
    MAC0210Times.insert(thur1);
    set<TimeWindow, TWComparator> MAC0323Times;//
    MAC0323Times.insert(monday1);
    MAC0323Times.insert(wed2);
    set<TimeWindow, TWComparator> MAC0236Times;//
    MAC0236Times.insert(monday2);
    MAC0236Times.insert(wed1);
    set<TimeWindow, TWComparator> MAC0422Times;//
    MAC0422Times.insert(tue2);
    MAC0422Times.insert(thur1);
    set<TimeWindow, TWComparator> MAT0112Times;//
    MAT0112Times.insert(tue2);
    MAT0112Times.insert(thur1);
    set<TimeWindow, TWComparator> MAE0221Times;//
    MAE0221Times.insert(monday3);
    MAE0221Times.insert(wed3);
    MAE0221Times.insert(fri1);
    set<TimeWindow, TWComparator> MAT02453Times;//
    MAT02453Times.insert(monday3);
    MAT02453Times.insert(wed1);
    MAT02453Times.insert(fri2);
    set<TimeWindow, TWComparator> MAC0350Times;//
    MAC0350Times.insert(tue3);
    MAC0350Times.insert(thur3);
    set<TimeWindow, TWComparator> MAC0101Times;//
    MAC0101Times.insert(talk1);
    set<TimeWindow, TWComparator> MAC0102Times;//
    MAC0101Times.insert(talk2);
    set<TimeWindow, TWComparator> MAC0209Times;//
    MAC0209Times.insert(tue3);
    MAC0209Times.insert(thur4);
    set<TimeWindow, TWComparator> FLC0474Times;//
    FLC0474Times.insert(ptWindow);
    set<TimeWindow, TWComparator> MAE0329Times;//
    MAE0329Times.insert(monday1);
    MAE0329Times.insert(wed3);
    set<TimeWindow, TWComparator> MAC0218Times;//
    MAC0218Times.insert(monday4);
    MAC0218Times.insert(wed4);
    set<TimeWindow, TWComparator> MAC0219Times;//
    MAC0219Times.insert(monday3);
    MAC0219Times.insert(wed3);
    set<TimeWindow, TWComparator> MAC0426Times;//
    MAC0426Times.insert(tue3);
    MAC0426Times.insert(thur1);
    set<TimeWindow, TWComparator> MAT0236Times;//
    MAT0236Times.insert(tue1);
    MAT0236Times.insert(thur2);
    set<TimeWindow, TWComparator> MAC0425Times;//
    MAC0425Times.insert(monday2);
    MAC0425Times.insert(thur4);
    set<TimeWindow, TWComparator> MAC0444Times;//
    MAC0444Times.insert(monday3);
    MAC0444Times.insert(wed1);
    set<TimeWindow, TWComparator> MAC0317Times;//
    MAC0317Times.insert(monday1);
    MAC0317Times.insert(wed2);
    set<TimeWindow, TWComparator> MAC0318Times;//
    MAC0318Times.insert(tue3);
    MAC0318Times.insert(tue4);

    Course MAC0110 = Course(MAC0110Times, "MAC0110");
    Course MAC0105 = Course(MAC0105Times, "MAC0105");
    Course MAC0329 = Course(MAC0329Times, "MAC0329");
    Course MAC0210 = Course(MAC0210Times, "MAC0210");
    Course MAC0323 = Course(MAC0323Times, "MAC0323");
    Course MAC0236 = Course(MAC0236Times, "MAC0236");
    Course MAC0422 = Course(MAC0422Times, "MAC0422");
    Course MAT0112 = Course(MAT0112Times, "MAC0112");
    Course MAE0221 = Course(MAE0221Times, "MAE0221");
    Course MAC0350 = Course(MAC0350Times, "MAC0350");
    Course MAC0101 = Course(MAC0101Times, "MAC0101");
    Course MAC0209 = Course(MAC0209Times, "MAC0209");
    Course FLC0474 = Course(FLC0474Times, "FLC0474");
    Course MAE0329 = Course(MAE0329Times, "MAE0329");
    Course MAC0218 = Course(MAC0218Times, "MAC0218");
    Course MAC0219 = Course(MAC0219Times, "MAC0219");
    Course MAC0426 = Course(MAC0426Times, "MAC0426");
    Course MAT0236 = Course(MAT0236Times, "MAT0236");
    Course MAC0425 = Course(MAC0425Times, "MAC0425");
    Course MAC0444 = Course(MAC0444Times, "MAC0444");
    Course MAC0317 = Course(MAC0317Times, "MAC0317");
    Course MAC0318 = Course(MAC0318Times, "MAC0318");
    Course MAC0102 = Course(MAC0102Times, "MAC0102");
    Course MAT02453 = Course(MAT02453Times, "MAT02453");

    set<Course, CourseComparator> juniorCourses;
    juniorCourses.insert(MAC0110);
    juniorCourses.insert(MAC0105);
    juniorCourses.insert(MAT0112);
    juniorCourses.insert(MAC0329);
    juniorCourses.insert(MAT02453);
    juniorCourses.insert(MAC0101);
    Student Junior = Student(juniorCourses);
    set<Student, StudentComparator> students;
    students.insert(Junior);
    TimeChart JuniorChart = TimeChart(students);
    
    ret = JuniorChart.findConflicts();
    if (ret != 0){
        failed++;
        return "Expected 0 conflicts in test 6, got " + to_string(ret);
    }
    
    set<Course, CourseComparator> ambitiousJuniorCourses = set<Course, CourseComparator>(juniorCourses);
    ambitiousJuniorCourses.insert(FLC0474);
    Student AmbitiousJunior = Student(ambitiousJuniorCourses);
    students.insert(AmbitiousJunior);
    TimeChart ExpandedJuniorChart = TimeChart(students);

    ret = ExpandedJuniorChart.findConflicts();
    if (ret != 1){
        failed++;
        return "Expected 1 conflicts in test 6, got " + to_string(ret);
    }

    set<Course, CourseComparator> seniorCourses = set<Course, CourseComparator>();
    seniorCourses.insert(MAC0102);
    seniorCourses.insert(MAC0209);
    seniorCourses.insert(MAC0210);
    seniorCourses.insert(MAC0323);
    seniorCourses.insert(MAT0236);
    seniorCourses.insert(MAE0221);
    Student Senior = Student(seniorCourses);
    students.insert(Senior);
    TimeChart SeniorChart = TimeChart(students);

    ret = SeniorChart.findConflicts();
    if (ret != 1){
        failed++;
        return "Expected 1 conflict after adding senior in test 6, got " + to_string(ret);
    }

    passed++;
    return "";
}

void testPrintChart(){
    TimeWindow monday1 = TimeWindow(8, 10, "monday");
    TimeWindow monday2 = TimeWindow(10, 12, "monday");
    TimeWindow monday3 = TimeWindow(14, 16, "monday");
    TimeWindow monday4 = TimeWindow(16, 18, "monday");
    TimeWindow tue1 = TimeWindow(8, 10, "tuesday");
    TimeWindow tue2 = TimeWindow(10, 12, "tuesday");
    TimeWindow tue3 = TimeWindow(14, 16, "tuesday");
    TimeWindow tue4 = TimeWindow(16, 18, "tuesday");
    TimeWindow talk1 = TimeWindow(14, 15, "tuesday");
    TimeWindow ptWindow = TimeWindow(14, 17, "tuesday");
    TimeWindow wed1 = TimeWindow(8, 10, "wednesday");
    TimeWindow wed2 = TimeWindow(10, 12, "wednesday");
    TimeWindow wed3 = TimeWindow(14, 16, "wednesday");
    TimeWindow wed4 = TimeWindow(16, 18, "wednesday");
    TimeWindow thur1 = TimeWindow(8, 10, "thursday");
    TimeWindow thur2 = TimeWindow(10, 12, "thursday");
    TimeWindow thur3 = TimeWindow(14, 16, "thursday");
    TimeWindow thur4 = TimeWindow(16, 18, "thursday");
    TimeWindow talk2 = TimeWindow(14, 15, "thursday");
    TimeWindow fri1 = TimeWindow(8, 10, "friday");
    TimeWindow fri2 = TimeWindow(10, 12, "friday");
    //Monday:    08-10: MAC110, MAC0323, MAE0329, MAC0317
    //           10-12: MAC105, MAC0236, MAC0425
    //           14-16: MAT02453, MAE0221, MAC0219, MAC0444
    //           16-18: MAC0218

    //Tuesday:   08-10: MAC0329, MAC0210, MAT0236
    //           10-12: MAT0112, MAC0422 
    //           14-16: MAC0350, MAC0101,FLC0474, MAC0209, MAC0426, MAC0318
    //           16-18: FLC0474, MAC0318

    //Wednesday: 08-10: MAT02453, MAC0236, MAC0444
    //           10-12: MAC110, MAC0323, MAC0317
    //           14-16: MAE0221, MAE0329, MAC0219
    //           16-18: MAC0218

    //Thursday:  08-10: MAT0112, MAC0422, MAC0210, MAC0426
    //           10-12: MAC0329, MAT0236
    //           14-16: MAC0350, MAC0102
    //           16-18: MAC0105, MAC0209, MAC0425
    
    //Friday:    08-10: MAE0221, 
    //           10-12: MAT02453
    set<TimeWindow, TWComparator> MAC0110Times;//
    MAC0110Times.insert(monday1);
    MAC0110Times.insert(wed2);
    set<TimeWindow, TWComparator> MAC0105Times;//
    MAC0105Times.insert(monday2);
    MAC0105Times.insert(thur4);
    set<TimeWindow, TWComparator> MAC0329Times;//
    MAC0329Times.insert(tue1);
    MAC0329Times.insert(tue2);
    set<TimeWindow, TWComparator> MAC0210Times;//
    MAC0210Times.insert(tue1);
    MAC0210Times.insert(thur1);
    set<TimeWindow, TWComparator> MAC0323Times;//
    MAC0323Times.insert(monday1);
    MAC0323Times.insert(wed2);
    set<TimeWindow, TWComparator> MAC0236Times;//
    MAC0236Times.insert(monday2);
    MAC0236Times.insert(wed1);
    set<TimeWindow, TWComparator> MAC0422Times;//
    MAC0422Times.insert(tue2);
    MAC0422Times.insert(thur1);
    set<TimeWindow, TWComparator> MAT0112Times;//
    MAT0112Times.insert(tue2);
    MAT0112Times.insert(thur1);
    set<TimeWindow, TWComparator> MAE0221Times;//
    MAE0221Times.insert(monday3);
    MAE0221Times.insert(wed3);
    MAE0221Times.insert(fri1);
    set<TimeWindow, TWComparator> MAT02453Times;//
    MAT02453Times.insert(monday3);
    MAT02453Times.insert(wed1);
    MAT02453Times.insert(fri2);
    set<TimeWindow, TWComparator> MAC0350Times;//
    MAC0350Times.insert(tue3);
    MAC0350Times.insert(thur3);
    set<TimeWindow, TWComparator> MAC0101Times;//
    MAC0101Times.insert(talk1);
    set<TimeWindow, TWComparator> MAC0102Times;//
    MAC0101Times.insert(talk2);
    set<TimeWindow, TWComparator> MAC0209Times;//
    MAC0209Times.insert(tue3);
    MAC0209Times.insert(thur4);
    set<TimeWindow, TWComparator> FLC0474Times;//
    FLC0474Times.insert(ptWindow);
    set<TimeWindow, TWComparator> MAE0329Times;//
    MAE0329Times.insert(monday1);
    MAE0329Times.insert(wed3);
    set<TimeWindow, TWComparator> MAC0218Times;//
    MAC0218Times.insert(monday4);
    MAC0218Times.insert(wed4);
    set<TimeWindow, TWComparator> MAC0219Times;//
    MAC0219Times.insert(monday3);
    MAC0219Times.insert(wed3);
    set<TimeWindow, TWComparator> MAC0426Times;//
    MAC0426Times.insert(tue3);
    MAC0426Times.insert(thur1);
    set<TimeWindow, TWComparator> MAT0236Times;//
    MAT0236Times.insert(tue1);
    MAT0236Times.insert(thur2);
    set<TimeWindow, TWComparator> MAC0425Times;//
    MAC0425Times.insert(monday2);
    MAC0425Times.insert(thur4);
    set<TimeWindow, TWComparator> MAC0444Times;//
    MAC0444Times.insert(monday3);
    MAC0444Times.insert(wed1);
    set<TimeWindow, TWComparator> MAC0317Times;//
    MAC0317Times.insert(monday1);
    MAC0317Times.insert(wed2);
    set<TimeWindow, TWComparator> MAC0318Times;//
    MAC0318Times.insert(tue3);
    MAC0318Times.insert(tue4);

    Course MAC0110 = Course(MAC0110Times, "MAC0110");
    Course MAC0105 = Course(MAC0105Times, "MAC0105");
    Course MAC0329 = Course(MAC0329Times, "MAC0329");
    Course MAC0210 = Course(MAC0210Times, "MAC0210");
    Course MAC0323 = Course(MAC0323Times, "MAC0323");
    Course MAC0236 = Course(MAC0236Times, "MAC0236");
    Course MAC0422 = Course(MAC0422Times, "MAC0422");
    Course MAT0112 = Course(MAT0112Times, "MAC0112");
    Course MAE0221 = Course(MAE0221Times, "MAE0221");
    Course MAC0350 = Course(MAC0350Times, "MAC0350");
    Course MAC0101 = Course(MAC0101Times, "MAC0101");
    Course MAC0209 = Course(MAC0209Times, "MAC0209");
    Course FLC0474 = Course(FLC0474Times, "FLC0474");
    Course MAE0329 = Course(MAE0329Times, "MAE0329");
    Course MAC0218 = Course(MAC0218Times, "MAC0218");
    Course MAC0219 = Course(MAC0219Times, "MAC0219");
    Course MAC0426 = Course(MAC0426Times, "MAC0426");
    Course MAT0236 = Course(MAT0236Times, "MAT0236");
    Course MAC0425 = Course(MAC0425Times, "MAC0425");
    Course MAC0444 = Course(MAC0444Times, "MAC0444");
    Course MAC0317 = Course(MAC0317Times, "MAC0317");
    Course MAC0318 = Course(MAC0318Times, "MAC0318");
    Course MAC0102 = Course(MAC0102Times, "MAC0102");
    Course MAT02453 = Course(MAT02453Times, "MAT02453");

    TimeChart printChart;
    printChart.addCourse(MAC0110);
    printChart.addCourse(MAC0105);
    printChart.addCourse(MAC0210);
    printChart.addCourse(MAC0323);
    printChart.addCourse(MAC0236);
    printChart.addCourse(MAC0422);
    printChart.addCourse(MAT0112);
    printChart.addCourse(MAE0221);
    printChart.addCourse(MAC0350);
    printChart.addCourse(MAC0101);
    printChart.addCourse(MAC0209);
    printChart.addCourse(FLC0474);
    printChart.addCourse(MAE0329);
    printChart.addCourse(MAC0218);
    printChart.addCourse(MAC0219);
    printChart.addCourse(MAC0426);
    printChart.addCourse(MAT0236);
    printChart.addCourse(MAC0425);
    printChart.addCourse(MAC0444);
    printChart.addCourse(MAC0317);
    printChart.addCourse(MAC0318);
    printChart.addCourse(MAC0102);
    printChart.addCourse(MAT02453);

    printChart.printChart();
}

Course* findCourseById(ll id, const set<Course, CourseComparator>& const courses){
    for (Course course : courses){
        if (course.getId() == id){
            return &course;
        }
    }
    return NULL;
}

Course* findCourseByName(string name, const set<Course, CourseComparator>& const courses){
    for (Course course : courses){
        if (course.getName() == name){
            return &course;
        }
    }
    return NULL;
}

Student* findStudentById(ll id, const set<Student, StudentComparator>& const students){
    for (Student student : students){
        if (student.getId() == id){
            return &student;
        }
    }
    return NULL;
}

Student* findStudentbyNUSP(ll NUSP, const set<Student, StudentComparator>& const students){
    for (Student student : students){
        if (student.getNUSP() == NUSP){
            return &student;
        }
    }
    return NULL;
}

Student* findStudent(string studentIdentifier, const set<Student, StudentComparator>& const students){
    Student* student;
    ll NUSP = stol(studentIdentifier);

    student = findStudentbyNUSP(NUSP, students);
    if (student != NULL){
        return student;
    }
    student = findStudentById(NUSP, students);
    if (student != NULL){
        return student;
    }
    cout << "Student not found with supplied identifier " << studentIdentifier << "." << endl;
    return NULL;
}

Course* findCourse(string courseIdentifier, const set<Course, CourseComparator>& const courses){
    Course* course;
    course = findCourseByName(courseIdentifier, courses);
    if (course != NULL){
        return course;
    }
    ll Id = stol(courseIdentifier);
    course = findCourseById(Id, courses);
    if (course != NULL){
        return course;
    }
    cout << "Course not found with supplied identifier " << courseIdentifier << "." << endl;
    return NULL;
}


int main(){
    vector<string> errors;
    string res;

    res = TestTWConstructor();
    if (res != ""){
        errors.push_back(res);
    }
    res = TestAutomatedIDGenerationTW();
    if (res != ""){
        errors.push_back(res);
    }
    res = TestIDAfterPassByValue();
    if (res != ""){
        errors.push_back(res);
    }
    res = TestTimeWindowClash();
    if (res != ""){
        errors.push_back(res);
    }
    res = TestSetGetCourseToTimeChart();
    if (res != ""){
        errors.push_back(res);
    }
    res = TestFindConflicts();
    if (res != ""){
        errors.push_back(res);
    }
    testPrintChart();

    for (int i = 0; i < errors.size(); i++){
        cout << i + 1 << ". " << errors[i] << endl;
    }

    cout << "Passing tests: " << passed << endl;
    cout << "Failing tests: " << failed << endl;

    cout << "Starting interactive mode..." << endl;

    set<Course, CourseComparator> registeredCourses;
    set<Student, StudentComparator> registeredStudents;
    TimeChart timechart;

    

    string input;
    vector<string> splitInp;
    while (true){
        cout << ">>> ";
        cin >> input;
        input = lowerCase(input);
        cout << endl;
        splitInp = splitInput(input);
        if (splitInp[0] == "exit" || splitInp[0] == "quit"){
            cout << "Exiting program." << endl;
            exit(0);
        }
        else if (splitInp[0] == "show"){
            if (splitInp[1] == "courses"){
                for (Course course : registeredCourses){
                    cout << course.to_string();
                }
            }
            else if (splitInp[1] == "students"){
                for (Student student : registeredStudents){
                    cout << student.to_string();
                }
            }
        }
        else if (splitInp[0] == "add"){
            if (splitInp.size() < 2){
                cout << "Wrong number of arguments for add operation." << endl;
            }
            else if (splitInp[1] == "student"){
                set<Course, CourseComparator> desired_courses;
                for (int i = 2; i < splitInp.size(); i++){
                    string courseName = splitInp[i];
                    Course* course = findCourseByName(courseName, registeredCourses);
                    if (course == NULL){
                        cout << "Course not found, aborting add student" << endl;
                    }
                    else{
                        desired_courses.insert(*course);
                    }
                }
                registeredStudents.insert(Student(desired_courses));
            }
            else if (splitInp[1] == "course"){
                if (splitInp.size() < 3){
                    cout << "Wrong number of arguments for add course operation, expected at least 3. type help for details." << endl;
                }
                else{
                    string courseName = splitInp[2];
                    set<TimeWindow, TWComparator> timeWindows;
                    int i = 3;
                    while (i < splitInp.size()){
                        string weekDay = splitInp[i];
                        int start_time;
                        int end_time;
                        int window_OK = 0;
                        i++;
                        if (Weekday.count(weekDay)){
                            if (i >= splitInp.size() || i + 1 >= splitInp.size()){
                                cout << "Missing timewindow for " << weekDay << " class. Aborting. Use help for details." << endl; 
                            }
                            else{
                                start_time = stol(splitInp[i]);
                                i++;
                                end_time = stol(splitInp[i]);
                                window_OK = 1;
                            }
                            i++;
                        }
                        else{
                            cout << "day of week mistyped, aborting. Use help for details." << endl;
                        }

                        if (window_OK){
                            TimeWindow timeWindow = TimeWindow(start_time, end_time, weekDay);
                            timeWindows.insert(timeWindow);
                        }
                    }
                    registeredCourses.insert(Course(timeWindows, courseName));
                }
            }
        }
        else if (splitInp[0] == "unregister"){
            if (splitInp[1] == "student"){
                //remove student from registeredStudents
                Student* student = NULL;
                if (splitInp.size() < 3){
                    cout << "Incorrect number of arguments for unregister students, NUSP or ID missing. Use help for details." << endl;
                }
                string studentIdentifier = splitInp[2];
                student = findStudent(studentIdentifier, registeredStudents);
                if (student != NULL){
                    registeredStudents.erase(*student);
                }
            }
            else if (splitInp[1] == "course"){
                int course_found = 0;
                Course* course;
                if (splitInp.size() < 3){
                    cout << "Incorrect number of arguments for unregister course, course name or id missing." << endl;
                }
                else{
                    string name = splitInp[2];
                    course = findCourseByName(name, registeredCourses);
                    if (course == NULL){
                        int id = stol(splitInp[2]);
                        course = findCourseById(id, registeredCourses);
                        if (course == NULL){
                            cout << "Course not found, wrong name or id given." << endl;
                        }
                        else{
                            course_found = 1;
                        }
                    }
                    else{
                        course_found = 1;
                    }
                }
                if (course_found){
                    registeredCourses.erase(*course);
                    for (Student student : registeredStudents){
                        student.getCourses().erase(*course);
                    }
                }
            }
        }
        else if (splitInp[0] == "set"){
            if (splitInp[1] == "student"){
                //set course to student
                int studentFound = 0;
                int courseFound = 0;
                Student* student;
                Course* course;
                if (splitInp.size() < 4){
                    cout << "Wrong number of arguments for set student, missing student identifier and course identifier" << endl;
                }
                else{
                    int studentIdentifier = stol(splitInp[3]);
                    string courseName = splitInp[4];
                    student = findStudentbyNUSP(studentIdentifier, registeredStudents);
                    if (student == NULL){
                        student = findStudentById(studentIdentifier, registeredStudents);
                        if (student == NULL){
                            cout << "Student could not be found with provided identifier." << endl;
                        }
                        else{
                            studentFound = 1;
                        }
                    }
                    else{
                        studentFound = 1;
                    }
                    course = findCourseByName(courseName, registeredCourses);
                    if (course == NULL){
                        course = findCourseById(stol(courseName), registeredCourses);
                        if (course == NULL){
                            cout << "Course could not be found with provided identifier." << endl;
                        }
                        else{
                            courseFound = 1;
                        }
                    }
                    else{
                        courseFound = 1;
                    }
                }
                if(studentFound && courseFound){
                    student->getCourses().insert(*course);
                }
            }
            else if (splitInp[1] == "course"){
                //set time to course
                int courseFound = 0;
                Course* course;
                int startingTime;
                int endingTime;
                string weekday;
                if (splitInp.size() < 6){
                    cout << "Wrong number of arguments for setting timewindow to course." << endl;
                }
                else{
                    string courseIdentifier = splitInp[2];
                    weekday = splitInp[3];
                    startingTime = stol(splitInp[4]);
                    endingTime = stol(splitInp[5]);
                    course = findCourseByName(courseIdentifier, registeredCourses);
                    if (course == NULL){
                        course = findCourseById(stol(courseIdentifier), registeredCourses);
                        if (course == NULL){
                            cout << "Could not find course with provided identifier " << courseIdentifier << "." << endl; 
                        }
                        else{
                            courseFound = 1;
                        }
                    }
                    else{
                        courseFound = 1;
                    }
                }
                if (courseFound){
                    TimeWindow tw = TimeWindow(startingTime, endingTime, weekday);
                    course->addTimeWindow(tw);
                }
            }
        }
        else if (splitInp[0] == "remove"){
            if (splitInp[1] == "student"){
                //remove course from student
            }
            else if (splitInp[1] == "course"){
                //remove time from course
            }
        }
        else if (splitInp[0] == "swap"){
            //swap two windows between courses
        }
        else if (splitInp[0] == "conflicts"){
            //find and display all conflicts
        }
        else if (splitInp[0] == "save"){
            //persist current chart with a given name
        }
        else if (splitInp[0] == "load"){
            //load a given chart by name
        }
        else if (splitInp[0] == "update"){
            //update chart with new courses and students.
        }
        else if (splitInp[0] == "help"){
            //display available commands and syntax
        }
    }
}
#include <bits/stdc++.h>
#include "../TimeWindow/TimeWindow.hpp"
#include "../TimeChart/TimeChart.hpp"

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

    for (int i = 0; i < errors.size(); i++){
        cout << i + 1 << ". " << errors[i] << endl;
    }

    cout << "Passing tests: " << passed << endl;
    cout << "Failing tests: " << failed << endl;

    
}
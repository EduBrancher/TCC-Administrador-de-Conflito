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

    for (int i = 0; i < errors.size(); i++){
        cout << i + 1 << ". " << errors[i] << endl;
    }

    cout << "Passing tests: " << passed << endl;
    cout << "Failing tests: " << failed << endl;

    
}
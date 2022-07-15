#include <bits/stdc++.h>
#include "../TimeChart/TimeChart.hpp"

using namespace std;


int main(){
    map < string, int > Weekday { 
    {"monday", 0}, {"tuesday", 1}, {"wednesday", 2}, {"thursday", 3},
    {"friday", 4}, {"saturday", 5}, {"sunday", 6}  };

    cout << Weekday["monday"] << endl;
}
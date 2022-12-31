#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

string lowerCase(string str){
    for (int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

vector<string> splitInput(string input){
    //input = lowerCase(input);
    vector<string> parsedInput;
    int wordStart = 0;
    int wordEnd = 0;
    int inputLength = input.length();
    string word;
    while (wordStart < inputLength){
        if (input[wordEnd] == ' '){
            word = input.substr(wordStart, wordEnd - wordStart);
            parsedInput.push_back(word);
            wordStart = wordEnd + 1;
        }
        wordEnd++;
    }
    return parsedInput;
}

string cutSeparator(string input, char separator){
    //input = lowerCase(input);
    vector<string> parsedInput;
    int wordStart = 0;
    int wordEnd = 0;
    int inputLength = input.length();
    string word;
    while (wordStart < inputLength){
        if (input[wordEnd] == separator){
            word = input.substr(wordStart, wordEnd - wordStart);
            parsedInput.push_back(word);
            wordStart = wordEnd + 1;
        }
        wordEnd++;
    }
    string retval;
    for (string str : parsedInput){
        retval = retval + str;
    }
    return retval;
}

template<typename T>
void printArr(vector<T> inputvector){
    for (int i = 0; i < inputvector.size(); i++){
        cout << inputvector[i] << "." << endl;
    }
}

vector<string> tokenizeLine(string line, char separator){
    //line = lowerCase(line);
    //breaks a string into tokens according to a given separator
    //returns array of tokens
    vector<string> tokenizedLine;
    string token = "";
    for (int head = 0; head < line.length(); head++){
        if (line[head] == separator){
            tokenizedLine.push_back(token);
            token = "";
            continue;
        }
        token = token + line[head];
    }
    tokenizedLine.push_back(token);
    return tokenizedLine;
}

vector<pair<string, vector<string>>> readFile(string filename){
    //reads a symbol table from a .csv file.
    ifstream file;
    file.open(filename);
    string studentIdentifier;
    string line;
    vector<string> courses;
    vector<string> tokenizedLine;
    vector<pair<string, vector<string>>> returnValue;
    if (file.is_open()){
        getline(file, line);
        while (getline(file, line)){
            line = lowerCase(line);
            tokenizedLine = tokenizeLine(line, ',');
            studentIdentifier = cutSeparator(tokenizedLine[1], '"');
            courses = tokenizeLine(cutSeparator(tokenizedLine[2], '"'), ';');
            pair<string, vector<string>> returnPair(studentIdentifier, courses);
            returnValue.push_back(returnPair);
        }
    }
    /*for (auto student : returnValue){
        cout << student.first << endl;
        for (auto course : student.second){
            cout << course << " ";
        }
        cout << endl;
    }*/
    file.close();
    return returnValue;
}

vector<pair<string, vector<string>>> readTimes(string filename){
    //reads times from a .txt file.
    ifstream file;
    file.open(filename);
    string line;
    vector<pair<string, vector<string>>> returnValue;
    if (file.is_open()){
        while(getline(file, line)){
            string courseIdentifier;
            vector<string> times;
            vector<string> tokenizedLine;
            line = lowerCase(line);
            tokenizedLine = tokenizeLine(line, ' ');
            for (int i = 1; i < tokenizedLine.size(); i++){
                times.push_back(tokenizedLine[i]);
            }
            courseIdentifier = tokenizedLine[0];
            pair<string, vector<string>> retPair = pair(courseIdentifier, times);
            returnValue.push_back(retPair);
        }
    }
    /*for (auto course : returnValue){
        cout << course.first << endl;
        for (auto time : course.second){
            cout << time << " ";
        }
        cout << endl;
    }*/
    file.close();
    return returnValue;
}

void writeFile(string filename){
    //writes a symbol table to a .csv file.
}



/*int main(){
    string test1 = "We think in generalities but live in details";
    string test2 = "";
    string test3 = " ";
    string test4 = "banana";

    vector<string> result = splitInput(test1);
    printArr(result);
    result = splitInput(test2);
    printArr(result);
    result = splitInput(test3);
    printArr(result);
    result = splitInput(test4);
    printArr(result);
    cout << lowerCase("BANANA REPUBLIC") << endl;
    vector<string> splitinp = splitInput("show courses");
    for (string word : splitinp){
        cout << word << endl;
    }
    vector<pair<string, vector<string>>> students = readFile("forms.csv");
    vector<pair<string, vector<string>>> courses = readTimes("times.txt");
    for (auto element : students){
        cout << element.first << endl;
        for (auto secondelement : element.second){
            cout << secondelement << " ";
        }
        cout << endl;
    }
    for (auto element : courses){
        cout << element.first << endl;
        for (auto secondelement : element.second){
            cout << secondelement << " ";
        }
        cout << endl;
    }
}*/
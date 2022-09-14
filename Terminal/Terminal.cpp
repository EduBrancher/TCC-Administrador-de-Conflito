#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> splitInput(string input){
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

template<typename T>
void printArr(vector<T> inputvector){
    for (int i = 0; i < inputvector.size(); i++){
        cout << inputvector[i] << "." << endl;
    }
}

string lowerCase(string str){
    for (int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

int main(){
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
}
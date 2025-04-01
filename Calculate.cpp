/*
:)
    Made by Lucas Thompson on Github.
    https://github.com/lthomp079/JosephGPA
    Copyright 2025 Lucas B. Thompson under the Apache 2.0 License
*/


#include <iostream>
#include <vector>
#include <cctype>
#include <iomanip>
using namespace std;
bool isString(string str) {
    int periodCount = 0;
    int numCount = 0;
    for (int p=0; p < str.length(); p++) {
        char i = str[p];
        if (i == '.') {
            periodCount++;
            continue;
        }
        if (!isdigit(i)) {
            cout << "error at if 2\n";
            return false;
        }
        else 
            numCount++;
        
        if (periodCount > 1) {
            cout << "error at period count\n";
            exit(4);
        }
    }
    if (numCount == 0) {
        cout << "No numbers\n";
        exit(5);
    }
    return true;
}
void letterValue(double& grade, float& gpa, string& letter) {
    //A 93 - 100
    if (grade < 115 && grade >= 92.5) {
        gpa = 4.0;
        letter = "A";
        return;
    }
    //A- 90 - 92
    if (grade < 92.5 && grade >= 89.5) {
        gpa = 3.7;
        letter = "A-";
        return;
    }
    //B+ 87 - 89
    if (grade < 89.5 && grade >= 86.5) {
        gpa = 3.3;
        letter = "B+";
        return;
    }
    //B 83 - 86
    if (grade < 86.5 && grade >= 82.5) {
        gpa = 3.0;
        letter = "B";
        return;
    }
    //B- 80 - 82
    if (grade < 82.5 && grade >= 79.5) {
        gpa = 2.7;
        letter = "B-";
        return;
    }
    //C+ 77 - 79
    if (grade < 79.5 && grade >= 76.5) {
        gpa = 2.3;
        letter = "C+";
        return;
    }
    //C 73 - 76
    if (grade < 76.5 && grade >= 72.5) {
        gpa = 2;
        letter = "C";
        return;
    }
    //C- 70 - 72
    if (grade < 72.5 && grade >= 69.5) {
        gpa = 1.7;
        letter = "C-";
        return;
    }
    //D+ 67 - 69
    if (grade < 69.5 && grade >= 66.5) {
        gpa = 1.3;
        letter = "D+";
        return;
    }
    //D 63 - 66
    if (grade < 66.5 && grade >= 62.5) {
        gpa = 1;
        letter = "D";
        return;
    }
    //D- 60 - 62 N/A
    //F >60
    if (grade < 62.5) {
        gpa = 0;
        letter = "F";
        return;
    }
}
int main(int argc, char* argv[]) {
    double average, averagegpa;
    vector <double> grades;
    if (argc < 2){
        string input;
        cout << "Enter your grade, type stop when done.\n";
        while (input != "stop") {
            cin >> input;
            if (input == "stop") {
                cout << "stopped\n";
                break;
            }
            else if (isString(input) == false) {
                cout << "Bad string\n";
                return 1; //ERROR 1 NO NON NUMERICAL ENTRIES
            }
            if (stod(input) > 115) {
                cout << "Your number cannot be higher than 115!";
                return 3; //NO NUMBERS GREATER THAN 115 ERROR 3
            }
            grades.push_back(stod(input));
        }  
    }
    else {
        for (int i = 1; i != argc; i++) {
            grades.push_back(stod(argv[i]));
            if (isString(argv[i]) == false) {
                cout << "Bad string\n";
                return 1; //ERROR 1 NO NON NUMERICAL ENTRIES
            }
            if (stod(argv[i]) > 115) {
                cout << "Your number cannot be higher than 115!";
                return 3; //NO NUMBERS GREATER THAN 115 ERROR 3
            }
        }
    }
    if (grades.size() == 0) {
        cout << "You have no elements\n";
        return 2; // ERROR 2 NO ELEMENTS, ONLY STOP
    }
    cout << fixed << setprecision(1);
    float gpa;
    double grade = grades[0];
    string letter;
    letterValue(grade, gpa, letter);
    if (grades.size() == 1) {
        cout << "You only entered " << grades[0] << "%, worth " << gpa << " gpa, and " << letter << " letter grade\n";
        return 0;
    }
    cout << "You entered: \n\t" << grades[0] << "%, worth " << gpa << " gpa, and " << letter << " letter grade\n";
    average += grades[0];
    averagegpa += gpa;
    for (int i = 1; i < grades.size(); i++) {
        grade = grades[i];
        letterValue(grade, gpa, letter);
        cout << "\t" << grades[i] << "%, worth " << gpa << " gpa, and " << letter << " letter grade\n";
        average += grades[i];
        averagegpa += gpa;
    }
    average /= grades.size();
    averagegpa /= grades.size();
    cout << fixed << setprecision(2);
    cout << "Average grade is " << average << "%\n";
    cout << "And average GPA is " << averagegpa << " \n";
}

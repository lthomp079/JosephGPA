/*
    Made by Lucas Thompson on Github.
    https://github.com/lthomp079/JosephGPA
    Copyright 2025 Lucas B. Thompson under the Apache 2.0 License
*/


#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <stdio.h>

int main() {
while (true) {
    //Temporary string for copying line by line
    std::string temp;
    //Making the variables for string comparisons
    std::string Spython, Scpp, Sindex, Sgitpython, Sgitcpp, Sgitindex;
    //Updating latest files from github
    system("git clone https://github.com/lthomp079/JosephGPA");
    //Opening files in the website folder
    std::ifstream python("gpa/app.py");
    std::ifstream cpp("gpa/Calculate.cpp");
    std::ifstream index("gpa/templates/index.html");
    //Opening files in the folder ported from github
    std::ifstream gitpython("JosephGPA/app.py");
    std::ifstream gitcpp("JosephGPA/Calculate.cpp");
    std::ifstream gitindex("JosephGPA/templates/index.html");
    //app.py
    //First, it saves the whole python file from github, and local to strings.
    while (!python.eof()) {
        std::getline(python, temp);
        temp += "\n";
        Spython.append(temp);
    }
    while (!gitpython.eof()) {
        std::getline(gitpython, temp);
        temp += "\n";
        Sgitpython.append(temp);
    }
    //Second, it will compare those strings.
    if (Spython != Sgitpython) {
        system("mv JosephGPA/app.py gpa/app.py");
        std::cout << "Updated app.py from Github\n";
    }
    else
        std::cout << "App.py is up to date!\n";
    //Now the process is repeated for Calculate.cpp
    //Save to strings
    while (!cpp.eof()) {
        std::getline(cpp, temp);
        temp += "\n";
        Scpp.append(temp);
    }
    while (!gitcpp.eof()) {
        std::getline(gitcpp, temp);
        temp += "\n";
        Sgitcpp.append(temp);
    }
    //it will compare those strings.
    if (Scpp != Sgitcpp) {
        system("mv JosephGPA/Calculate.cpp gpa/Calculate.cpp");
        std::cout << "Updated Calculate.cpp from Github\n";
        system("cd gpa && g++ Calculate.cpp -o test");
        std::cout << "Attempted to recompile.\n";
    }
    else
        std::cout << "Calculate.cpp is up to date!\n";
    //index.html
    while (!index.eof()) {
        std::getline(index, temp);
        temp += "\n";
        Sindex.append(temp);
    }
    while (!gitindex.eof()) {
        std::getline(gitindex, temp);
        temp += "\n";
        Sgitindex.append(temp);
    }
    //it will compare those strings.
    if (Sindex != Sgitindex) {
        system("mv JosephGPA/templates/index.html gpa/templates/index.html");
        std::cout << "Updated index.html from Github\n";
    }
    else
        std::cout << "Index.html is up to date!\n";
    system("rm -rf JosephGPA");

    //Starting countdown to update again.
    std::this_thread::sleep_for (std::chrono::hours(1));
}
}

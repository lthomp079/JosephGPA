#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

void ReplaceOrNot(std::vector<std::string> files) {
    for (auto i : files) {
        std::string command = "cmp ~/gpa/" + i + " ~/josephgpa/" + i;
        int test = system(command.c_str());
        if (test != 0) {
            std::cout << command << " came back as DIFFERENT!\nFiles will be upated accordingly.";
            command = "cp ~/josephgpa/" + i + " ~/gpa/" + i;
            system(command.c_str());
        }
    }  
}

int main() {
    std::cout << "Enter files to update/check:\n";
    std::string input;
    std::vector<std::string> files;
    while (input != "stop") {
        std::cin >> input;
        files.push_back(input);
    }
    files.pop_back();
    while (true) {
    system("curl josephgpa.site && rm -rf josephgpa && git clone https://github.com/lthomp079/josephgpa");
    ReplaceOrNot(files);
    if (system("g++ gpa/Calculate.cpp -o Calculate.exe") == 0) 
        std::cout << "Compilation succesful\n";
    else
        std::cout << "Compilation failed\n";
    std::this_thread::sleep_for(std::chrono::hours(1));
}
}

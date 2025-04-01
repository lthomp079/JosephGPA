//Made by Lucas Thompson

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

int main() {
	system("cp Calculate.cpp ../Calculate.cpp");
	system("git pull origin main");
	if (system("cmp Calculate.cpp ../Calculate.cpp") != 0)
		system("g++ Calculate.cpp -o Calculate.exe");
	std::this_thread::sleep_for(std::chrono::seconds(10));
}


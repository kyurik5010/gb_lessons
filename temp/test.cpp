#include <iostream>
#include <string>

//using namespace std;

int main(){
	std::string name;
	std::string reply = "poopsy";
	std::cout << "Enter you full name: ";
	std::getline(reply, name);	
	std::cout << name << std::endl;
	return 0; 
}

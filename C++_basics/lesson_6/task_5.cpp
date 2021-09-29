//
// Задание 5 к дз по 6-му уроку
// 18/09/2021.
//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char *argv[]){
    if(argc != 3){
        cout << "incorrect parameters\n";
        return 1;
    }
    cout << "text - " << argv[1] << endl << "word - " << argv[2] << endl;

    string word = argv[2];
    ifstream text(argv[1]);

    if(text.is_open()) {
        string buf;
        while (!text.eof()){
            getline(text, buf);
            if(buf.find(argv[2]) != string::npos) {
                cout << "\nword '" << argv[2] << "' found in line: \n..." << buf << "...\n\n";
                text.close();
                return 0;
            }
            else
                continue;
        }
        cout << "word '" << argv[2] << "' was not found in file '" << argv[1] << "'\n";
        text.close();
        return 0;
    }
    else
        cout << "Could not open file '" << argv[1] << "'\n";
    return 1;
}
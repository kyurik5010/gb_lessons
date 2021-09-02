#include <iostream> 
using namespace std; 

void task1() 
{ 
    bool a_0 = false; 
    short int a_1 = 3; // max out
    char a_2 = 'k';
    int a = 2500000000; // check max value
    signed int b = -1; // max out
    unsigned int c = 2; // same
    float d = 3.7f; 
    double e = 3.7874539874;
    long f = 2500000000;// check max value
    long long g = 1;// max out


} 
int main() 
{ 
    enum objects{ 
        inputCross, // [x]
        inputZero,  // [o]
        emptySpace, // [ ]
    }; 
    
    
    
    struct gameSet
    { 
        bool gameActive  : 1; // true false для цикла while
        //char field[3][4]{ {'[ ]','[ ]','[ ]'} , {'[ ]','[ ]','[ ]'} , {'[ ]','[ ]','[ ]'} };
        struct playField
        {   
            char a[4]{ '[ ]','[ ]','[ ]' };
            char b[4]{ '[ ]','[ ]','[ ]' };
            char c[4]{ '[ ]','[ ]','[ ]' };
        } fld;
        char player1[30];
        char player2[30];
        char player1Vict[20]; 
        char player2Vict[20]; 
        char draw[10]; 
    } game; 
   
    
    cout << "everything seems to be fine\n";
    cout << "size of enum - " << sizeof(objects) << endl; 
    cout << "size of playField - " << sizeof(game.fld) << endl;
    cout << "size of gameSet - " << sizeof(game) << endl;
    cout << "A - " << game.fld.a << endl;
    cout << "B - " << game.fld.b << endl;
    cout << "C - " << game.fld.c << endl;
    return 0; 
}
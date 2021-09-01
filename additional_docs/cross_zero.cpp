#include <iostream>
using namespace std;

int main()
{
    enum objects{
        inputCross,
        inputZero,
        emptySpace,
    };
    
    struct gameSet{
        struct playField{
            char a[4]{' ',' ',' ',0};
            char b[4]{' ',' ',' ',0};
            char c[4]{' ',' ',' ',0};
        };
        char player1[30]{0};
        char player2[30]{0};
        char player1Vict[40]{0};
        char player2Vict[40]{0};
        char draw[40]{0};
    };
    
    /*int i,k;
    char arr[3][4]= {{'_','_','_'},{'_','_','_'},{'_','_','_'}};
    for(i=0;i<=2;i++)
    {
        for(k=0;k<=2;k++)
        {
        cout<< arr[i][k] << "|";
        }
        cout<<endl;
    }*/
    
    cout << "everything seems to be fine\n";
    cout << "size of structure - " << sizeof(gameSet) << endl;
    cout << "size of enum - " << sizeof(objects) << endl;
    return 0;
}

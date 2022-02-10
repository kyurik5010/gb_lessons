#include <iostream>
#include <string>

void LessonTask(int &&x){
    std::cout << std::endl;
    for (int i = 0; i < 80; ++i)
        std::cout << '_';
    std::cout << "/ ЗАДАНИЕ " << x << " ";
    std::cout << std::endl;
}

//____________________________________________________________________________________________________________/ЗАДАНИЕ 1
template <typename T>
T Div(T x, T y){
    if(!y)
        throw 0;
    return (x / y);
}

void task1() {
    LessonTask(1);
    int x = 5;
    int y = 0;
    try
    {
        std::cout << x << "/" << y << " = " << Div(x,y) << std::endl;
    }
    catch(int f)
    {
        std::cerr << "\nException: division by zero";
    }
}

//____________________________________________________________________________________________________________/ЗАДАНИЕ 2
class Ex{
    float x;
public:
    explicit Ex(float num): x(num) {}
};

class Bar{
    float y;
public:
    Bar(){ y = 0; }
    void set(float a) {
        if( (y + a) > 100 )
            throw Ex(y*a);
        y = a;
    }
};

void task2() {
    LessonTask(2);
    Bar bar;
    int n;
    try
    {
        do{
            std::cout << "\nProvide a number: ";
            std::cin >> n;
            bar.set(n);
        }while(n != 0);
    }
    catch(Ex &ex)
    {
        std::cerr << "\nException: caught on n = " << n;
    }
}

//____________________________________________________________________________________________________________/ЗАДАНИЕ 3

class OffTheField : public std::exception{
    std::string m_error = "\nWARNING : Robot is off grid! Turn back!\n";
public:
    const char* GetError() { return m_error.c_str(); }
};

class IllegalCommand : public std::exception{
    std::string m_error = "WARNING : Invalid key pressed! Try another one: ";
public:
    const char* GetError() { return m_error.c_str(); }
};

class Robot{
    char grid[10][10];
    enum icons{ EMPTY = ' ', ACTOR = '@', EXIT = '#', };
    struct Coords{ int x; int y; }current;
    bool IsExit = false;
public:
    Robot(){}

    void Init(){
        for(int i=0;i<10;++i){
            for(int j=0;j<10;++j)
                grid[i][j] = EMPTY;
        }
        grid[9][9] = EXIT;
        SetActorPosition(5,5);
    }

    void DrawGrid(){
        for(int i=0;i<10;++i){
            for(int j=0;j<10;++j)
                std::cout << "[" << grid[i][j] << "]";
            std::cout<<"\n";
        }
        std::cout << "\nSelect direction [w][a][s][d] and press 'Enter': ";
    }

    void Refresh(){
        for (int i = 0; i < 10; ++i) {
            std::cout << "\n";
        }
        DrawGrid();
    }

    void SetActorPosition(int x, int y){
        if(x>9 || x<0 || y>9 || y<0)
            throw OffTheField();

        else if(x==9 && y==9)
            IsExit = true;
        grid[current.x][current.y] = EMPTY;
        current.x = x;
        current.y = y;
        grid[x][y] = ACTOR;
        Refresh();
    }

    void Move(char& direction){
        try{
            switch(direction){
                case 'w': SetActorPosition(current.x-1, current.y); break;
                case 's': SetActorPosition(current.x+1, current.y); break;
                case 'd': SetActorPosition(current.x, current.y+1); break;
                case 'a': SetActorPosition(current.x, current.y-1); break;
                default : throw IllegalCommand();
            }
        }
        catch(OffTheField& err)
        {
            std::cerr << err.GetError();
            std::cout << "\nSelect direction [w][a][s][d] and press 'Enter': ";
        }
        catch(IllegalCommand& err)
        {
            std::cerr << err.GetError();
        }
    }
    bool IsExiting() { return IsExit; }

};



int main()
{
    task1();

    task2();

    Robot rob;
    rob.Init();
    char direction;
    while (!rob.IsExiting()){
        std::cin >> direction;
        rob.Move(direction);
    }
    return 0;


}
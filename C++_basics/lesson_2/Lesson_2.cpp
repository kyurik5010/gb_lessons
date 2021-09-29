#include <iostream> 
using namespace std; 

void task1() 
{ 
    bool a = false;
    
    char b = 'k';
    uint8_t b_1 = 255;

    short int c = 65000; 
    int16_t c_1  = 65000;
    
    int d = 2140000000; 
    int32_t d_1 = 2140000000;
    
    unsigned int e = 4290000000;
    uint32_t e_1 = 4290000000;
    
    long f = 2140000000;
    
    long long g = 9200000000000000000;
    int64_t g_1 = 9200000000000000000;

    unsigned long long h = 18000000000000000000;
    uint64_t h_1 = 18000000000000000000;
    
    float i = 3.0000007f; 
    double j = 3.000000000000015;
}

void task2()
{
   enum objects
   { 
        inputCross, // [x]
        inputZero,  // [o]
        emptySpace, // [ ] опционально, в будущей программе использовать пока не планирую
   }; 
}


void task3()
{
  char grid[3][10] = {{"[ ][ ][ ]"}, {"[ ][ ][ ]"}, {"[ ][ ][ ]"}};
  cout << grid[0] <<"\n"<< grid[1] <<"\n"<< grid[2] <<"\n";

  // еще вариант на основе идей Dachi Gog и Moss:
  //char grid2[] = {"  1  2  3\nA[ ][ ][ ]\nB[ ][ ][ ]\nC[ ][ ][ ]\n"}; 
  //cout << grid2 << "\n\n"; // красиво выводится и
  //дает возможность в работать с одномерныммассивом вместо двумерного

}


int task4()
{

  struct gameSet
  {
    
    struct sPlayer
    {
      char playerName[10];
      char playerVict[20];
    } player;
    
    char gameState[20];
    
    uint16_t is_active  : 1; // флаг для основного цикла программы
    uint16_t is_turn : 1; // флаг для смены хода и отрисовки сетки
    uint16_t is_win : 1; //флаг для проверки условий победы игрока
    uint16_t is_full : 1; //флаг для проверки заполнения сетки
    uint16_t is_end : 1; // флаг для прерывания работы программы
    uint16_t is_restart : 1;//флаг для перезапуска программы
  } game; 

  cout << "What is your name? - ";
  cin >> game.player.playerName;
  cout << endl << "The game is starting " << game.player.playerName << endl;
  task3();
  return 0;
}

int main(){// Задание 5 не выполнено

    struct MyVariant
    {
        union MyData
        {
            char a;
            int b;
            float c;
        } dat;
// пытался добиться нужного эффекта логическими 
// присваиванием результатов логических выражений
// но так и не осилил. Буду признателен если подскажете
// в каком направлении нужно ковыряться и читать
        int isChar : 1; //(dat == dat.a);
        int isInt : 1;  //(dat == dat.b);
        int isFloat : 1;//(dat == dat.c);
    } var;
    
    task4(); 
}

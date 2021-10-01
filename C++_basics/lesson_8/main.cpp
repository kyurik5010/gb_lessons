#include <iostream>
#include <string>
#include <cstdlib>

#ifdef _WIN64
#define CLEAR_SCREEN system("cls")                // макрос очистки экрана для Windows
#else
#define CLEAR_SCREEN system("clear")              // макрос очистки экрана для MacOS
#endif

using namespace std;
//========================================== глобальные переменные =====================================================

enum cell{
    EMPTY = '_',
    CROSS = 'X',
    ZERO = 'O',};

struct coords{
    int x;                                         // указание на индекс материнского массива
    int y;                                         // указание на индекс дочернего массива
}coord;

#pragma pack(push, 1)
struct game{
    const size_t size = 3;
    char **pfield = new char* [size];
    char ai = ZERO;                                 // функцией side_pick() будет присвоен CROSS или останется ZERO
    char player = ZERO;                             // то же самое для ИИ
    uint16_t turn : 1;                              // флаг для очередности ходов
    uint16_t is_running : 1;                        // флаг для основного цикла
}gm;
#pragma pack(pop)
//========================================== первичные функции =========================================================

void init_field(){ // первичная инициализация поля - вызывается из init_game()

    for(int i = 0; i < gm.size; i++)
    {
        for(int k=0; k<gm.size; k++)
            gm.pfield[i][k] = EMPTY;
    }
}                            // инициализация массива

void draw_field(){

    CLEAR_SCREEN;
    cout << endl << "   1  2  3  y" << endl;
    for(int i = 0; i < gm.size; i++){
        cout << i+1 << " ";
        for(int k=0; k<gm.size; k++)
            cout << "[" << gm.pfield[i][k] << "]";
        cout << endl;
    }
    cout << "x\n\n";
}                            // отрисовка игрового поля

void side_pick(){                                  //определяет кто чем играет
    int counter = 0;
    for(int i=0;i<3;i++)
    {
        int x = rand();
        if (x % 2 == 0)
            counter += 1;
    }
    if (counter >= 2){
        gm.player = CROSS;                        // игрок с CROSS ходит первым
        gm.turn = 1;
    }                                             // смена значения битового флага
    else{
        gm.ai = CROSS;
        gm.turn = 0;
    }

    cout << "gm.player " << gm.player << endl;
    cout << "gm.ai     " << gm.ai << endl;
}                             // варнинг на ранд

void init_game()
{
    for (int i=0; i<gm.size; i++)                  // выделение памяти под массив
        gm.pfield[i] = new char [gm.size + 1];     // размер дочерних массивов на 1 больше под терминант

    gm.turn = 0;                                   // сброс флага ходов на 0
    gm.is_running = 1;                             // статус игры

    init_field();                                  // первичная инициализация массива
    side_pick();                                   // бросок кубика (кто чем играет)
}                            // инициализация игры

//============================================ игровой процесс =========================================================

inline void chng_turn(){
    gm.turn = !gm.turn;
}                      // смена хода (переключает битовое поле)

void get_coords(){
    int x, y;
    do{
        cout << "Ваш ход!\n\nкоордината Х: ";
        cin >> x;
    }while(x <= 0 || x > 3);
    do{
        cout << "координата Y: ";
        cin >> y;
    }while(y <= 0 || y > 3);

    coord.x = x-1;
    coord.y = y-1;

}                            // получение координат от игрока

int check_empty(){
    int counter = 0;
    for(int i=0; i<3; i++) {
        for (int j = 0; j < 3; j++)
            counter += (gm.pfield[i][j] == EMPTY) ? 1 : 0;
    }
    return (counter > 0) ? 1 : 0;
}                            // проверка наличия пустых клеток

int check_win(){
    for(int i=0, j=0, k=0, win=0, loose=0; i<3; k++, i++, j++){   // счетчик k для того чтобы последовательность
        if (gm.pfield[i][j] == gm.ai){                            // анализировалась полностью и триггер не срабатывал
            win++;                                                // раньше времени
            if(win == 3)
                return 2;}
        if (gm.pfield[i][j] == gm.player){
            loose++;
            if(loose == 3)
                return 1;}
        if (!gm.turn) {
            if (gm.pfield[i][j] == EMPTY) {
                coord.x = i;
                coord.y = j;
            }
            if ( k==2 && ((win == 2 && loose == 0)||(loose == 2 && win == 0)))
                return 0;
        }
    }

    for(int i=0, j=2, k=0, win=0, loose=0; i<3; k++, i++, j--){
        if (gm.pfield[i][j] == gm.ai){
            win++;
            if(win == 3)
                return 2;}
        if (gm.pfield[i][j] == gm.player){
            loose++;
            if(loose == 3)
                return 1;}
        if (!gm.turn) {
            if (gm.pfield[i][j] == EMPTY) {
                coord.x = i;
                coord.y = j;
            }
            if ( k==2 && ((win == 2 && loose == 0)||(loose == 2 && win == 0)))
                return 0;
        }
    }

    // горизонтали
    for(int i=0, j=0, k=0, win=0, loose=0; j<3; k++, j++){
        if (gm.pfield[i][j] == gm.ai){
            win++;
            if(win == 3)
                return 2;}
        if (gm.pfield[i][j] == gm.player){
            loose++;
            if(loose == 3)
                return 1;}
        if (!gm.turn) {
            if (gm.pfield[i][j] == EMPTY) {
                coord.x = i;
                coord.y = j;
            }
            if ( k==2 && ((win == 2 && loose == 0)||(loose == 2 && win == 0)))
                return 0;
        }
    }

    for(int i=1, j=0, k=0, win=0, loose=0; j<3; k++, j++){
        if (gm.pfield[i][j] == gm.ai){
            win++;
            if(win == 3)
                return 2;}
        if (gm.pfield[i][j] == gm.player){
            loose++;
            if(loose == 3)
                return 1;}
        if (!gm.turn) {
            if (gm.pfield[i][j] == EMPTY) {
                coord.x = i;
                coord.y = j;
            }
            if ( k==2 && ((win == 2 && loose == 0)||(loose == 2 && win == 0)))
                return 0;
        }
    }

    for(int i=2, j=0, k=0, win=0, loose=0; j<3; k++, j++){
        if (gm.pfield[i][j] == gm.ai){
            win++;
            if(win == 3)
                return 2;}
        if (gm.pfield[i][j] == gm.player){
            loose++;
            if(loose == 3)
                return 1;}
        if (!gm.turn) {
            if (gm.pfield[i][j] == EMPTY) {
                coord.x = i;
                coord.y = j;
            }
            if ( k==2 && ((win == 2 && loose == 0) || (loose == 2 && win == 0)))
                return 0;
        }
    }

    // вертикали
    for(int i=0, j=0, k=0, win=0, loose=0; i<3; k++, i++){
        if (gm.pfield[i][j] == gm.ai){
            win++;
            if(win == 3)
                return 2;}
        if (gm.pfield[i][j] == gm.player){
            loose++;
            if(loose == 3)
                return 1;}
        if (!gm.turn) {
            if (gm.pfield[i][j] == EMPTY) {
                coord.x = i;
                coord.y = j;
            }
            if ( k==2 && ((win == 2 && loose == 0) || (loose == 2 && win == 0)))
                return 0;
        }
    }

    for(int i=0, j=1, k=0, win=0, loose=0; i<3; k++, i++){
        if (gm.pfield[i][j] == gm.ai){
            win++;
            if(win == 3)
                return 2;}
        if (gm.pfield[i][j] == gm.player){
            loose++;
            if(loose == 3)
                return 1;}
        if (!gm.turn) {
            if (gm.pfield[i][j] == EMPTY) {
                coord.x = i;
                coord.y = j;
            }
            if ( k==2 && ((win == 2 && loose == 0) || (loose == 2 && win == 0)))
                return 0;
        }
    }

    for(int i=0, j=2, k=0, win=0, loose=0; i<3; k++, i++){
        if (gm.pfield[i][j] == gm.ai){
            win++;
            if(win == 3)
                return 2;
        }
        if (gm.pfield[i][j] == gm.player){
            loose++;
            if(loose == 3)
                return 1;
        }
        if (!gm.turn) {
            if (gm.pfield[i][j] == EMPTY) {
                coord.x = i;
                coord.y = j;
            }
            if ( k==2 && ((win == 2 && loose == 0) || (loose == 2 && win == 0)))
                return 0;
        }
    }

    return 0;
}                              // ИИ + проверка условий выигрыша

void move(){
    if(gm.turn)
    {
        get_coords();
        if(gm.pfield[coord.x][coord.y] == EMPTY){
            gm.pfield[coord.x][coord.y] = gm.player;
            }
        else {
            cout << "Это поле уже занято!";
            draw_field();
            move();
        }
    }
    else {
        cout << "\nХод компьютера\n";
        if (gm.pfield[1][1] == EMPTY)
            gm.pfield[1][1] = gm.ai;
        else{
            check_win();
            if(gm.pfield[coord.x][coord.y] == EMPTY)
                gm.pfield[coord.x][coord.y] = gm.ai;
            else
                move();
        }
    }
}                                  // берет координаты от игрока или ии

int check_state(){
    switch(check_win()) {
        case (1):
            draw_field();
            cout << "Player wins!\n";
            return 0;
        case (2):
            draw_field();
            cout << "Computer wins!\n";
            return 0;
        default:
            if(check_empty()){
                cout << "game continues\n";
                return 1;}
            else{
                draw_field();
                cout << "This is a tie!";
                return 0;} // возвращает 1 если есть свободные клетки
    }

}                            // запрос проверок условий окончания игры

void game_loop(){
    do{
        draw_field();
        move();
        gm.is_running = check_state();
        chng_turn();
    }while(gm.is_running);

    CLEAR_SCREEN;
    cout << "\nDo you want to play again? (y/n) ";    // перезапуск игры
    char reply;
    cin >> reply;

    if (reply == 'y'){
        init_field();
        side_pick();
        game_loop();}
}                             //  основной игровой цикл

//================================================= МЭЙН ===============================================================

int main()
{
    srand(time(0));

    init_game();    // инициализирует игру
    game_loop();    // запускает соновной цикл (сделан отдельно для возможности перезапуска игры)

    // освобождение памяти
    for(int i=0; i<gm.size; i++)
    {
        delete[] gm.pfield[i];
    }
    delete[] gm.pfield;
    gm.pfield = nullptr;

    return 0;
}

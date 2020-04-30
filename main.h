#include <windows.h>

#define BLACK        0
#define BLUE         1
#define GREEN        2
#define AQUA         3
#define RED          4
#define PURPLE       5
#define YELLOW       6
#define WHITE        7
#define GRAY         8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTAQUA    11
#define LIGHTRED     12
#define LIGHTPURPLE  13
#define LIGHTYELLOW  14
#define BRIGHTWHITE  15

//Jumps to position x,y in the cmd
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Changes writing color
void textcolor(int text, int background)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(text | background << 4));
}

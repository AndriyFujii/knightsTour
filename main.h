#include <windows.h>

#define SIZE    8
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

//Converts and returns an XY into a position ID (0 to 63)
int xyToPos(int x, int y)
{
    int pos = y * SIZE + x;

    return pos;
}

//Converts and returns an algebraic position into a position ID (0 to 63)
int algebraicToPos(char c, int x)
{
    int auxY[8] = {7, 6, 5, 4, 3, 2, 1, 0};
    int auxX;

    switch(c)
    {
        case 'a':
            auxX = 0;
            break;
        case 'b':
            auxX = 1;
            break;
        case 'c':
            auxX = 2;
            break;
        case 'd':
            auxX = 3;
            break;
        case 'e':
            auxX = 4;
            break;
        case 'f':
            auxX = 5;
            break;
        case 'g':
            auxX = 6;
            break;
        case 'h':
            auxX = 7;
            break;
    }

    return xyToPos(auxX ,auxY[x-1]);
}

//Prints a vector
void showVector(std::vector<int> path)
{
    for(int i = 0; i < path.size(); i++)
        std::cout << path[i] << ' ';
}

//Returns true if the position is in the vector
bool find(std::vector<int> vector, int x)
{
    for(int i = 0; i < vector.size(); i++)
        if(vector[i] == x)
            return true;
    return false;
}

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

//Prints the chessboard
void printBoard()
{
    int count = 0;
    for(int i = 0; i < SIZE; i++)
    {
        std::cout << 8-i << ' ';
        for(int j = 0; j < SIZE; j++)
        {
            if(count % 2 == 0)
                textcolor(BLACK, WHITE);
            else
                textcolor(WHITE, BLACK);

            std::cout << ' ' << ' ' << ' ';
            count++;
        }
        std::cout << '\n';
        count++;
        textcolor(WHITE, BLACK);
    }
    char c = 'a';
    std::cout << ' ';
    for(int i = 0; i < SIZE; i++)
    {
        std::cout << "  " << c;
        c++;
    }
}

void header()
{
    gotoxy(0, 0);
    textcolor(LIGHTYELLOW, BLACK);
    std::cout << "Knight's tour";
    gotoxy(0, 1);
    textcolor(YELLOW, BLACK);
    std::cout << "Engenharia de Computacao - UNIVALI";
    gotoxy(0, 2);
    std::cout << "Graphs";
    gotoxy(0, 3);
    std::cout << "Andriy Fujii Pendloski";

    textcolor(BLACK, WHITE);
    gotoxy(0, 5);
    system("pause");
    textcolor(BRIGHTWHITE, BLACK);
}

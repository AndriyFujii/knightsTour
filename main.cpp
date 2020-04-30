#include <iostream>
#include <stack>
#include "main.h"

using namespace std;

#define TAM 8
#define BLACK        0
#define WHITE        7
#define GRAY         8
#define BRIGHTWHITE  15

struct chessBoard 
{
    int visited, path;
};

struct boardPos
{
    int x, y;
};

void fillBoard(chessBoard board[TAM][TAM])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j].visited = 0;
            board[i][j].path = -1;
        }
    }
}

void showBoards(chessBoard board[TAM][TAM])
{
    int cont = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(cont % 2 == 0)
                textcolor(BLACK, WHITE);
            else
                textcolor(WHITE, BLACK);
            if(board[i][j].visited)
                cout << ' ' << ' ' << ' ';
            else
                cout << ' ' << board[i][j].visited << ' ';
            cont++;
        }
        textcolor(WHITE, BLACK);
        cout << "\t\t";
        for(int j = 0; j < 8; j++)
        {
            if(cont % 2 == 0)
                textcolor(BLACK, WHITE);
            else
                textcolor(WHITE, BLACK);
            if(board[i][j].path < 0)
                cout << ' ' << ' ' << ' ';
            else
                cout << ' ' << board[i][j].path << ' ';
            cont++;
        }
        cout << '\n';
        cont++;
    }
    textcolor(WHITE, BLACK);
}

//Checks whether the move ends up inside or outside the board
bool validMove(int x)
{
    if(x < 0 || x >= TAM)
        return false;
    else
        return true;
}

/*Knight can move eight different directions;
(-1,  2), ( 1,  2)
( 2,  1), ( 2, -1)
(-1, -2), ( 1, -2)
(-2,  1), (-2, -1)
*/
void genMoves(chessBoard board[TAM][TAM], boardPos pos, stack<boardPos> &stackPos)
{
    boardPos newPos;
    int directions[16] = {-1, 2, 1, 2, 2, 1, 2, -1, -1, -2, 1, -2, -2, 1, -2, -1};
    for(int i = 0; i < 8; i++)
    {
        newPos.x = pos.x + directions[2*i];
        newPos.y = pos.y + directions[2*i+1];
        if(validMove(newPos.x) && validMove(newPos.y) && board[newPos.x][newPos.y].visited == 0)
        {
            stackPos.push(newPos);
        }
    }
    /*newPos.x = pos.x - 1;
    newPos.y = pos.y + 2;
    if(validMove(newPos.x) && validMove(newPos.y) && board[newPos.x][newPos.y].visited == 0)
    {
        stackPos.push(newPos);
    }*/
}



void mostraPilha(stack<boardPos> s)
{
    boardPos b;
    while (!s.empty())
    {
        b.x = s.top().x;
        b.y = s.top().y;
        cout << b.x << ' ' << b.y <<'\n';
        s.pop();
    }
}

int main()
{
    chessBoard board[TAM][TAM];
    stack<boardPos> stackPos;
    boardPos pos;
    pos.x = 2;
    pos.y = 3;
    
    fillBoard(board);

    //gotoxy(0, 0);
    //cout << "Chess board" << "\t\t\t\t" << "Knight's path" << '\n';
    //showBoards(board);

    genMoves(board, pos, stackPos);

    mostraPilha(stackPos);

    cout << '\n';
    system("pause");
    return 0;
}
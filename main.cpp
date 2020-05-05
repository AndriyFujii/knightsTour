#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include "main.h"

using namespace std;

#define SIZE 8
#define BLACK        0
#define WHITE        7
#define GRAY         8
#define BRIGHTWHITE  15

int xyToPos(int x, int y)
{
    int pos = y * SIZE + x;

    return pos;
}

//Returns true if the position is in the vector
bool find(vector<int> vector, int x)
{
    for(int i = 0; i < vector.size(); i++)
        if(vector[i] == x)
            return true;
    return false;
}

void showBoard(vector<int> path)
{
    int count = 0;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            int aux = xyToPos(j, i);
            if(count % 2 == 0)
                textcolor(BLACK, WHITE);
            else
                textcolor(WHITE, BLACK);

            if(!find(path, aux))
                cout << ' ' << ' ' << ' ';
            else
            {
                if(aux < 10)
                    cout << ' ' << aux << ' ';
                else
                    cout << ' ' << aux;
            }
            count++;
        }
        cout << '\n';
        //count++;
    }
    textcolor(WHITE, BLACK);
}

//Checks whether the move ends up inside or outside the board
bool validMove(int x)
{
    if(x < 0 || x >= SIZE)
        return false;
    else
        return true;
}

//Generates possible knight moves and returns them in possibleMoves
vector<int> genMoves(vector<int> path, int pos)
{
    int directions[16] = {-1, 2, 1, 2, 2, 1, 2, -1, 1, -2, -1, -2, -2, -1, -2, 1};
    int posX = pos % SIZE;
    int posY = pos / SIZE;

    vector<int> possibleMoves;
    
    for(int i = 0; i < 8; i++)
    {
        int newPosX = posX + directions[2*i];
        int newPosY = posY + directions[2*i+1];

        int newPos = xyToPos(newPosX, newPosY);
        //Checks if X and Y are inside the board, and if it hasn't been visited before
        if(validMove(newPosX) && validMove(newPosY) && !find(path, newPos))
            possibleMoves.push_back(newPos);
    }

    return possibleMoves;
}

//Criar uma função para inserir em ordem no vetor
vector<int> prioritizeMoves(vector<int> path, vector<int> possibleMoves)
{
    stack<int> warnsdorffOrder;
    for(int i = 1; i < 9; i++)
    {
        for(int j = 0; j < possibleMoves.size(); j++)
        {
            vector<int> auxVector;
            auxVector = genMoves(path, possibleMoves[j]);
            if(auxVector.size() == i)
                warnsdorffOrder.push(possibleMoves[j]);
        }
    }

    vector<int> prioritizedVector;
    while(!warnsdorffOrder.empty())
    {
        prioritizedVector.push_back(warnsdorffOrder.top());
        warnsdorffOrder.pop();
    }
    return prioritizedVector;
}


void showPath(vector<int> path)
{
    for(int i = 0; i < path.size(); i++)
        cout << path[i] << ' ';
}


//Pos is the current position, path is the visited nodes
bool knightsTour(int pos, vector<int> &path, int depth = 0)
{
    bool completed;
    path.push_back(pos);
    if(depth < SIZE*SIZE-1)
    {
        completed = false;

        vector<int> possibleMoves;
        possibleMoves = genMoves(path, pos);
        if(possibleMoves.size()>1)
            possibleMoves = prioritizeMoves(path, possibleMoves);

        while(!possibleMoves.empty() && !completed)
        {
            pos = possibleMoves[possibleMoves.size()-1];
            completed = knightsTour(pos, path, depth+1);
            possibleMoves.pop_back();
        }

        if(!completed)
            path.pop_back();
    }
    else
        completed = true;

    return completed;
}

int main()
{
    /*cout << "Chess board" << "\t\t\t\t" << "Knight's path" << '\n';

    gotoxy(0, 1);
    showBoards(board);*/

    vector<int> path;
    knightsTour(1, path);

        
    gotoxy(0, 3);
    showPath(path);

    cout << '\n';
    system("pause");
    return 0;
}
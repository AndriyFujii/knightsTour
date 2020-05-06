#include <iostream>
#include <stack>
#include <vector>
#include "main.h"

using namespace std;

#define SIZE 8
#define BLACK        0
#define WHITE        7
#define GRAY         8
#define BRIGHTWHITE  15

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
    //Possible moves the knight can do in a matrix
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

//Rearanges the order of possibleMoves according to Warnsdorff's rule
vector<int> prioritizeMoves(vector<int> path, vector<int> possibleMoves)
{
    //Since the first move picked is always the last position of possibleMoves, a stack is used
    stack<int> warnsdorffOrder;
    //Stacks the positions with fewest moves first
    for(int i = 1; i < 9; i++)
    {
        for(int j = 0; j < possibleMoves.size(); j++)
        {
            vector<int> auxVector;
            //Saves the moves in the next position
            auxVector = genMoves(path, possibleMoves[j]);
            if(auxVector.size() == i)
                warnsdorffOrder.push(possibleMoves[j]);
        }
    }

    vector<int> prioritizedVector;
    //Since the positions with more moves were pushed last, they'll be inserted first in prioritizedVector
    while(!warnsdorffOrder.empty())
    {
        prioritizedVector.push_back(warnsdorffOrder.top());
        warnsdorffOrder.pop();
    }
    return prioritizedVector;
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
        //If it generated more than one move, reorganize them following Warnsdorff's rule
        if(possibleMoves.size()>1)
            possibleMoves = prioritizeMoves(path, possibleMoves);

        //If it still has moves to try
        while(!possibleMoves.empty() && !completed)
        {
            //Tries the last move in the vector
            pos = possibleMoves[possibleMoves.size()-1];
            completed = knightsTour(pos, path, depth+1);
            //Move branch wasn't successful
            possibleMoves.pop_back();
        }
        if(!completed)
            //
            path.pop_back();
    }
    else
        completed = true;

    return completed;
}

int main()
{
    header();

    bool tryAgain;
    do
    {
        //Prints the chessboard
        system("cls");
        gotoxy(0, 0);
        printBoard();

        gotoxy(0, SIZE+2);
        cout << "Enter the knight's starting position (e.g. a4, d6):\n";

        char posX;
        int posY;
        bool exit;
        //Validates the input
        do
        {
            cin >> posX;
            cin >> posY;
            
            posX = tolower(posX);
            exit = true;
            //Error if it's outside the chessboard range
            if(posY < 1 || posY > 8 || posX < 'a' || posX > 'h')
            {
                system("cls");

                printBoard();
                gotoxy(0, SIZE+2);
                cout << "Invalid position! Try again (e.g. a4, d6):\n";
                exit = false;
            }
        }
        while(!exit);
        
        vector<int> path;
        //Solves the tour while saving it in path
        knightsTour(algebraicToPos(posX, posY), path);
        
        //Prints the knight's movement step by step
        gotoxy(0, 0);
        for(int i = 0; i < SIZE*SIZE; i++)
        {
            int posX = path[i] % SIZE;
            int posY = path[i] / SIZE;

            //If it's a black or a while tile
            if((2+posX*3+posY) % 2 == 0)
                textcolor(BLACK, WHITE);
            else
                textcolor(WHITE, BLACK);
            
            //Calculates where it should print the movement
            gotoxy(3+posX*3, posY);
            cout << i+1;
            
            //Resets the color and moves the cursor down to not interrupt any prints
            textcolor(WHITE, BLACK);
            gotoxy(0, SIZE+6);
            system("pause");
        }
        textcolor(WHITE, BLACK);

        char choice;
        //If the program should run again or close
        do
        {
            gotoxy(0, SIZE+5);
            cout << "Finished! Try again? (Y/N) ";
            cin >> choice;
            choice = tolower(choice);

            exit = false;
            //Only leaves the loop if Y or N are typed
            if(choice == 'y')
            {
                tryAgain = true;
                exit = true;
            }
            else if(choice == 'n')
            {
                tryAgain = false;
                exit = true;
            }
        }
        while(!exit);
    }
    while(tryAgain);
    
    return 0;
}
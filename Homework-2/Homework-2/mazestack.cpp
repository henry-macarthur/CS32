//
//  mazestack.cpp
//  Homework-2
//
//  Created by Henry Macarthur on 1/31/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//
#include <stack>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};



bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    Coord start(sr, sc);
    coordStack.push(start); //load the starting item into the stack
    maze[sr][sc] = '~'; //'~' means i have encountered the index
    
    //printMaze(maze, 10, 10);
    
    while(!coordStack.empty())
    {
        Coord current = coordStack.top();
        coordStack.pop();
        if(current.r() == er && current.c() == ec)
            return true; //Solved the maze;
        
        //Check South
        if(current.r() +1 < nRows && maze[current.r()+1][current.c()] == '.') //&&current.r() + 1 < nRows
        {
            Coord southCell(current.r()+1, current.c());
            coordStack.push(southCell);
            maze[current.r()+1][current.c()] = '~'; //update the cell id
        }
        //Check West
        if(current.c() -1 >= 0 && maze[current.r()][current.c()-1] == '.') //&&current.c() - 1 >= 0
        {
            Coord westCell(current.r(), current.c()-1);
            coordStack.push(westCell);
            maze[current.r()][current.c()-1] = '~'; //update the cell id
        }
        //Check North
        if(current.r() -1 >= 0 && maze[current.r()-1][current.c()] == '.') //&&current.r() - 1 >= 0
        {
            Coord northCell(current.r()-1, current.c());
            coordStack.push(northCell);
            maze[current.r()-1][current.c()] = '~'; //update the cell id
        }
        //Check East
        if(current.c() + 1 < nCols && maze[current.r()][current.c()+1] == '.') //&&current.c() + 1 < nCols
        {
            Coord southCell(current.r(), current.c()+1);
            coordStack.push(southCell);
            maze[current.r()][current.c()+1] = '~'; //update the cell id
        }
    }
    
    
    
    
    return false;
}




int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 3,5, 8,8))
        cerr << "Solvable!" << endl;
    else
        cerr << "Out of luck!" << endl;
    string maze1[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "XXXXXXXXXX",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };

    assert(!pathExists(maze1, 10, 10, 1, 1, 8, 8));
    string maze2[10] = {
        "XXXXXXXXXX",
        "X........X",
        "X.XXXXXX.X",
        "X.X....X.X",
        "X.XXXXXX.X",
        "X.X...XX.X",
        "X...X.XX.X",
        "X.XXXXXX.X",
        "X........X",
        "XXXXXXXXXX"
    };
    assert(pathExists(maze2, 10, 10, 1, 1, 8, 8));
    string maze3[10] = {
        "XXXXXXXXXX",
        "X........X",
        "X.XXXXX..X",
        "XXX......X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };

    assert(pathExists(maze3, 10, 10, 2, 1, 8, 8));
    string maze4[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    string maze5[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.XX.X",
        "XXXXX.X.XX",
        "X......X.X",
        "XXXXXXXXXX"
    };
    assert(!pathExists(maze5, 10, 10, 1, 1, 8, 8));
    string maze6[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXXXXXXX",
        "X.X...X..X",
        "X...XXX..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    assert(!pathExists(maze6, 10, 10, 1, 1, 8, 8));
    string maze7[10] = {
        "XXXXXXXXXX",
        "X.X..X...X",
        "XXXX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    assert(pathExists(maze7, 10, 10, 1, 1, 1, 1));
    
    cerr << "passed all tests" << endl;
}

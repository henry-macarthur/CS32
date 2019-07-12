//
//  maze.cpp
//  Homework-3-1
//
//  Created by Henry Macarthur on 2/7/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if(sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = '~'; //'~' means it has been visited before
    
    if(sr - 1 >= 0 && maze[sr-1][sc] == '.') //north
    {
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
        {
            return true;
        }
    }
    if(sr + 1 < nRows && maze[sr + 1][sc] == '.') //south
    {
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
        {
            return true;
        }
    }
    if(sc - 1 >= 0 && maze[sr][sc-1] == '.') //west
    {
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
        {
            return true;
        }
    }
    if(sc + 1 < nCols && maze[sr][sc+1] == '.') //west
    {
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
        {
            return true;
        }
    }
    
    return false;
    
}
/*
int main()
{
    string maze1[10] = {
        "XXXXXXXXXX",
        "X...X....X",
        "XX.X..XX.X",
        "XX...X...X",
        "X.X.X..XXX",
        "X...X.X.XX",
        "X.X.X....X",
        "XXX.X.XX.X",
        "X...X..X.X",
        "XXXXXXXXXX",
    };
    
    string maze2[10] = {
        "XXXXXXXXXX",
        "X...X....X",
        "XX.X..XX.X",
        "XX...X...X",
        "X.X.X..XXX",
        "X...X.X.XX",
        "X.X.X....X",
        "XXX.X.XXXX",
        "X...X..X.X",
        "XXXXXXXXXX",
    };
    
    string maze3[10] = {
        "XXXXXXXXXX",
        "XXXXXXX..X",
        "XX.......X",
        "X..X....XX",
        "X..X..XXXX",
        "X..XXX.X.X",
        "XX...X...X",
        "X....XX..X",
        "XXX.....XX",
        "XXXXXXXXXX",
    };
    
    string maze4[10] = {
        "XXXXXXXXXX",
        "XXXXXXX..X",
        "XX.....X.X",
        "X..X....XX",
        "X..X..XXXX",
        "X..XXX.X.X",
        "XX...X...X",
        "X....XX..X",
        "XXX.....XX",
        "XXXXXXXXXX",
    };
    
    assert(pathExists(maze1, 10, 10, 1, 3, 8, 8));
    assert(!pathExists(maze2, 10, 10, 1, 3, 8, 8));
    assert(pathExists(maze3, 10, 10, 5, 6, 2, 8));
    assert(!pathExists(maze4, 10, 10, 5, 6, 2, 8));
    cout << "passed " << endl;
 
 /*
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
 */
//}


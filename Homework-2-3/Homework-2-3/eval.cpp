//
//  main.cpp
//  Homework-2-3
//
//  Created by Henry Macarthur on 1/31/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//


//TODOS
//ignore spaces
//instead of only accepting numbers, accept the input list
//Check to make sure we have proper syntax
//checklower
//can true and false values have overlapping items
//can call evaluate if unique and it works
#include "Set.h"
#include <stack>
#include <string>
#include <iostream>
using namespace std;

bool isHigherPrecedence(char l, char r);
//bool evaluatePostFix(const string p);
bool evaluateIfUnique(const string postfix, bool& unique);
bool isProperSyntax(const string input);
string toPostFix(const string in, int& t, int& f, const Set& trueValues, const Set& falseValues, bool& p);
string toNumbers(string postfix, const Set& trueValues, const Set& falseValues);

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    int countT = 0;
    int countF = 0;
    bool proper = true;
    bool i = true;
    postfix = toPostFix(infix, countT, countF, trueValues, falseValues, proper);
    string nums = toNumbers(postfix,trueValues,falseValues);
    evaluateIfUnique(nums, i); //this should check to see if it has proper syntax
    cout << i << endl;

    stack<char> op;
    //cout << postfix << endl;
    if(1==1)
    {
        string nums = toNumbers(postfix,trueValues,falseValues);
        if(countT == 0 || countF == 0)
        {//need to also check to see if the syntax is valid
            //string nums = toNumbers(postfix,trueValues,falseValues);
            bool ev = evaluateIfUnique(nums, i);
            result = ev;

            
            return 0;
        }
        else
        {
            for(int i = 0; i < postfix.size(); i++)
            {
                if(!trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]))
                {
                    return 2;
                }
                
                if(trueValues.contains(postfix[i]) && falseValues.contains(postfix[i]))
                {
                    return 3;
                }
            }
        }
    }
    return 0;
}

bool evaluateIfUnique(string postfix, bool& unique)
{
    stack<char> op;
    cout << postfix << endl;
    for(int i = 0; i < postfix.size(); i++)
    {
        cout << i << " " << op.size() << endl;

        // cout << postfix[i] << endl;
        if(postfix[i] == '0' || postfix[i] == '1') //make this check to see if they are proper letters
        {
            op.push(postfix[i]);
        }
        else //make sure it is a right operator
        {
            if(postfix[i] == '!')
            {
                if(op.size() > 0)
                {
                    char op1 = op.top();
                    op.pop();
                    op.push(op1);
                } else {
                    unique = false;
                }
            }
            else if(op.size() > 1)
            {
                char op2 = op.top();
                op.pop();
                char op1 = op.top();
                op.pop();
                
                if(postfix[i] == '|')
                {
                    int p = (op1 || op2);
                    op.push(p + '0');
                }
                else if(postfix[i] == '&')
                {
                    int p = (op1 && op2);
                    op.push(p + '0');
                }
            } else {
                unique = false;
            }
            

            //if op.size == 1, or 0, bad syntax
        }
    }
    cout << op.size() << endl;
    if(op.size() != 1)
    {
        unique = true;
    }
    //cout << "size " << op.size() << endl;
    if(op.top() == '1') //if op.size != 1, bad syntax
    {
        return true;
    }
    else
    {
        return false;
    }
}

string toNumbers(string postfix, const Set& trueValues, const Set& falseValues)
{
    string toNumbers;
    for(int i = 0; i < postfix.size(); i++)
    {
        if(trueValues.contains(postfix[i]))
            toNumbers +='1';
        else if(falseValues.contains(postfix[i]))
            toNumbers  += '0';
        else
            toNumbers += postfix[i];
    }
    return toNumbers;
}

string toPostFix(const string in, int& t, int& f, const Set& trueValues, const Set& falseValues, bool& isProperSyntax)
{
    string postfix;
    string infix = in;//"0";//"1&!(1|0&1|0)|!!!(0&1&0)";
    stack<char> op;
    
    //bool isProperSyntax = true;
    
    int infixLength = infix.size();
    
    for(int i = 0; i < infixLength; i++)
    {
        char c = infix[i];
        switch (c)
        {
            case '!':
            case '&':
            case '|':
                while(op.size() > 0 && op.top() != '(' && isHigherPrecedence(op.top(), c))
                {
                    char top = op.top();
                    postfix += top;
                    op.pop();
                }
                op.push(c);
                break;
            case '(':
                op.push(c);
                break;
            case ')':
                while( op.size() > 0 && op.top() != '(')
                {
                    char top = op.top();
                    postfix += top;
                    op.pop();
                }
                if(op.size() > 0)
                    op.pop();
                else
                    isProperSyntax = false; //ther is no matching '('
                break;
            default: //case operand -- see if there is a better way to do this
                if(trueValues.contains(c))
                    t++;
                else if(falseValues.contains(c))
                    f++;
                
                if(!islower(c))
                    isProperSyntax = false; //can i assume both sets will have unique values?
                
                postfix += c;
                break;
        }
    }
    while(op.size() > 0)
    {
        char top = op.top();
        postfix += top;
        op.pop();
        
        if(top == '(')
        {
            isProperSyntax = false;
        }
    
    }
   
    cout << postfix << endl;
    return postfix;
}


bool isHigherPrecedence(char l, char r)
{
    switch (l)
    {
        case '!':
            return true;
        case '&':
            if(r == '|' || r == '&')
                return true;
            return false;
        case '|':
            if(r == '|')
                return true;
            return false;
    }
    
    return false;
}


int main()
{
    string trueChars  = "ucla";
    string falseChars = "nsx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);
    
    bool res;
    string post;
    int n = evaluate("u&c&l&a & !(u&s&c)", trues, falses, post, res);
    
}

//
//  main.cpp
//  Homework-3-1
//
//  Created by Henry Macarthur on 2/6/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
class Landmark
{
public:
    Landmark(string input);
    virtual ~Landmark();
    virtual string icon() const = 0;
    string name() const;
    virtual string color() const;
private:
    string m_name;
    
};

Landmark::~Landmark()
{}

Landmark::Landmark(string input)
{
    m_name = input;
}

string Landmark::color() const
{
    return "yellow";
}

string Landmark::name() const
{
    return m_name;
}


class Hotel : public Landmark
{
public:
    Hotel(string input);
    ~Hotel();
    string icon() const;
private:
    string m_name;
};

Hotel::Hotel(string input)
:Landmark(input)
{
    m_name = input;
}

Hotel::~Hotel()
{
    cout << "Destroying the hotel " << m_name << "." << endl;
}


string Hotel::icon() const
{
    return "bed";
}


class Restaurant : public Landmark
{
public:
    Restaurant(string input, int capacity);
    ~Restaurant();
    string icon() const;
private:
    string m_name;
    string m_icon;
    int m_capacity;
};

Restaurant::~Restaurant()
{
    cout << "Destroying the restaurant " << m_name << "." << endl;
}
Restaurant::Restaurant(string input, int capacity)
:Landmark(input)
{
    m_name = input;
    m_capacity = capacity;
    
    if(capacity < 40) // do i default capacity to 0?
    {
        m_icon = "small knife/fork";
    }
    else
    {
        m_icon = "large knife/fork";
    }
}


string Restaurant::icon() const
{
    return m_icon;
}

class Hospital : public Landmark
{
public:
    Hospital(string input);
    ~Hospital();
    string icon() const;
    string color() const;
private:
    string m_name;
};

Hospital::~Hospital()
{
    cout << "Destroying the hospital " << m_name << "." << endl;
}

Hospital::Hospital(string input)
:Landmark(input)
{
    m_name = input;
}


string Hospital::icon() const
{
    return "H";
}

string Hospital::color() const
{
    return "blue";
}

void display(const Landmark* lm)
{
    cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
    << lm->name() << "." << endl;
}


int main()
{
    Landmark* landmarks[4];
    landmarks[0] = new Hotel("Westwood Rest Good");
    // Restaurants have a name and seating capacity.  Restaurants with a
    // capacity under 40 have a small knife/fork icon; those with a capacity
    // 40 or over have a large knife/fork icon.
    landmarks[1] = new Restaurant("Bruin Bite", 30);
    landmarks[2] = new Restaurant("La Morsure de l'Ours", 100);
    landmarks[3] = new Hospital("UCLA Medical Center");
    
    cout << "Here are the landmarks." << endl;
    for (int k = 0; k < 4; k++)
        display(landmarks[k]);
    
    // Clean up the landmarks before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete landmarks[k];
}



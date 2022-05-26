
#include <iostream>
#include <vector>
#include "algoritm.h"
#include <valarray>
#include <algorithm>
using namespace std;
vector <Student> create_students(int size, int size_el)
{   
    vector<int> el;
    for (int i = 0; i < size_el; i++)
    {
        el.push_back(i);
    }

    vector<Student> students;
    for (int i = 0; i < size; i++)
    {
        random_shuffle(el.begin(), el.end());
        vector<int> preor(el.begin(), el.begin() + 4);
        students.push_back(Student(i, rand() % size_el,preor));

    }
    return students;
}

vector <Elective> create_elective(int size)
{
    vector<Elective> electives;
    vector<int> capacity{ 100,25,60,60,15,100,100,100,60,60,30,15,60,60,100,60,60,60,60,60,25,30,25,60,60,90,60,50,50,60,60,30,30,60,50,30,50,60,30,50,50,60,120,60,30,30,50,50,60,60,30,30,25,30,60,15,60,60,50,100,60,50,60,20,15,30,30,100,15,15,15,60,60,75,60,100,60,60,30,15,60,60,90,25,90,60,60,25,60,60,50,60,25,150,50,60,50,30,60,120,30,50,60,100,30,60,50,30,90,60,15,15,15,50,25,25,50,25,30,30,60,60,30,100,240,30,100,100,50,30,15,100,80,40,30,50,50,20,100,25,60,60,60,50,60,30,30,60,50,30,50,60,30,100,60,30,30,50,100,100,120,30,60,60,60,30,90,150,60,100,60,60,50,100,100,120,50,20,60,60,30,60,120,90,90,120,60,25,90,15,90,25,30,25,90,90,100,60,50,50,50,50,60,60,60,60,15,90,15,50,60,60,50,30,61,60,50,120,150,150 };
    for (int i = 0; i < size; i++)
    {
        electives.push_back(Elective(i, capacity[i], rand() % 4));
    }
    return electives;
}

int main()
{   
    vector <Student> students;
    vector<Elective> electives;
    electives = create_elective(220);
    students = create_students(5084,220);
    std::cout << "Hello World!\n";

    
   

}
//5084
//220
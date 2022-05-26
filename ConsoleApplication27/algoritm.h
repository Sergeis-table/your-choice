#pragma once
#include <vector>
class Student;
class Elective;
void student_allocation(std::vector<Elective>, std::vector <Student>, int, int);
void Create_graff(std::vector<Elective>, std::vector <Student>, std::vector<std::vector<float>>&, std::vector<std::vector<int>>&);
void Floyd(std::vector<Elective>, std::vector <Student>);
void Clean_shit(std::vector<Elective>, std::vector <Student>);
int search_student(Elective, int);
int search_prior(Student, int);
bool comp_elective(Student a, Student b);
bool comp_notFullEl(Elective, Elective);
bool comp_student(Student, Student);
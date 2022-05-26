#pragma once
#include <vector>
class Student
{
	int id;
	float performance = 0;
	vector <int> priorites;
	int first_elective_id = -1;
	int second_elective_id = -1;
	bool firstAvailable = false;
	bool secondAvailable = false;
	int current_prior = -1;
	Student(int Id, float Performace, std::vector <int>  Priorites)
		:id(Id), performance(Performace), priorites(Priorites)
	{}
	Student() {}
};

class Elective
{
public:
	unsigned int id = 0;
	unsigned int capacity = 0;
	vector <Student> students;
	vector <Student> resultStudent;
	int reserve = 0;
	int day = 0;

	Elective(int Id, int Capacity, int Day)
		: id(Id), capacity(Capacity), day(Day)
	{}
};
void student_allocation(std::vector<Elective>, std::vector <Student>, int, int);
void Create_graff(std::vector<Elective>, std::vector <Student>, std::vector<std::vector<float>>&, std::vector<std::vector<int>>&);
void Floyd(std::vector<Elective>, std::vector <Student>);
void Clean_shit(std::vector<Elective>, std::vector <Student>);
int search_student(Elective, int);
int search_prior(Student, int);
bool comp_elective(Student a, Student b);
bool comp_notFullEl(Elective, Elective);
bool comp_student(Student, Student);
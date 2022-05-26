#include <iostream>
#include <vector>
#include <algorithm>
#include "algoritm.h"
using namespace std;

#pragma region Побочки
int search_student(Elective a, int id)
{
	for (int i = 0; i < a.resultStudent.size(); i++)
	{
		if (id == a.resultStudent[i].id) return i;
	}
}
// находит приоритет электива
int search_prior(Student a, int id)
{
	for (int i = 0; i < a.priorites.size(); i++)
	{
		if (a.priorites[i] = id) break;
		return i;
	}
}
bool comp_elective(Student a, Student b)
{

	return  a.current_prior == b.current_prior ?
		(a.performance < b.performance) :
		a.current_prior > b.current_prior;
}
bool comp_notFullEl(Elective a, Elective b)
{
	return  (a.capacity - a.resultStudent.size() < b.capacity - b.resultStudent.size());
}
bool comp_student(Student a, Student b)
{

	return a.performance < b.performance;
}
#pragma endregion Функции поиска и компораторы

void student_allocation(vector<Elective> electives, vector <Student> students, int min_capacity = 0, int quota = 0)
{
	for (int i = 0; i < students.size(); i++)
	{
		for (int p = 0; p < students[i].priorites.size(); p++)
		{
			students[i].current_prior = p + 1;
			electives[students[i].priorites[p]].students.push_back(students[i]);
			if (p == 0)
				electives[students[i].priorites[p]].reserve++;
		}
		sort(electives[i].students.begin(), electives[i].students.end(), comp_elective);

	}
	vector <Student> students_copy = students;
	sort(students_copy.begin(), students_copy.end(), comp_student);
	for (int i = 0; i < students_copy.size(); i++)
	{ //впервые пользуюсь ссылками DANGEROUS
		for (int prior = 0; (prior < students_copy[i].priorites.size()) && !(students_copy[i].firstAvailable && students_copy[i].secondAvailable); prior++) // заполняем студентов на элективы, пока есть возможность
		{
			Student& temp_stud = students[students_copy[i].id];
			Elective& temp_el = electives[students_copy[i].priorites[prior]];
			if (temp_el.resultStudent.size() <= temp_el.capacity && temp_el.day != electives[temp_stud.first_elective_id].day)
			{
				if (temp_stud.firstAvailable)
					temp_stud.second_elective_id = students_copy[i].priorites[prior];
				else temp_stud.first_elective_id = students_copy[i].priorites[prior];
				temp_stud.secondAvailable = temp_stud.firstAvailable;
				temp_stud.firstAvailable = true;
				temp_el.resultStudent.push_back(temp_stud);
			}
		}
	}
	vector<Elective> sorted_el = electives;
	sort(sorted_el.begin(), sorted_el.end(), comp_notFullEl); // элективы которые не заполнены наверх

	for (int i = 0; i < students_copy.size(); i++)
	{

		for (int it_el = 0; it_el < electives.size() && !(students_copy[i].firstAvailable && students_copy[i].secondAvailable); it_el++) // заполняем оставшихся студентов на элективы
		{
			Student& temp_stud = students[students_copy[i].id];
			Elective& temp_el = electives[sorted_el[it_el].id];
			if (temp_el.capacity > temp_el.resultStudent.size()) {
				if (!temp_stud.firstAvailable)
				{
					temp_stud.firstAvailable = true;
					temp_stud.first_elective_id = sorted_el[it_el].id;
					temp_el.resultStudent.push_back(temp_stud);
				}
				else if (electives[temp_stud.first_elective_id].day != temp_el.day)
				{
					temp_stud.secondAvailable = true;
					temp_stud.second_elective_id = sorted_el[it_el].id;
					temp_el.resultStudent.push_back(temp_stud);
				}
			}
		}
	}

}
// Вы бы знали как я себя сдерживаю, чтобы не начать писать гениальный код. Никто бы не понял его, даже я. А так хочется подсократить строчки.
// Так хочется for each, но цена ошибки высока.
void Create_graff(vector<Elective> electives, vector <Student> students, vector<vector<float>>& g, vector<vector<int>>& id_g)
{
	vector<vector<float>> graff(electives.size(), vector<float>(electives.size(), INT_MAX)); // надо проверить инцелизацию вектора
	vector<vector<int>> id_graff(electives.size(), vector<int>(electives.size(), 0));
	for (Elective& el : electives)
	{
		for (Student& st : el.resultStudent)
		{
			for (int& prior : st.priorites)
			{
				if ((st.first_elective_id == el.id && electives[prior].day != electives[st.second_elective_id].day) ||
					(st.second_elective_id == el.id && electives[prior].day != electives[st.first_elective_id].day))// pidor check
				{
					if (graff[el.id][prior] > st.performance * (search_prior(st, prior) - search_prior(st, el.id)));
					{
						graff[el.id][prior] = st.performance * (search_prior(st, prior) - search_prior(st, el.id));

						id_graff[el.id][prior] = st.id;
					}
				}
			}
		}
	}
	g = graff;
	id_g = id_graff;
}
void Floyd(vector<Elective> electives, vector <Student> students) {
	vector<vector<vector<pair<int, int>>>> tapki_bratki(electives.size(), vector<vector<pair<int, int>>>(electives.size(), vector<pair<int, int>>(electives.size(), { 0,0 }))); // Тяжёлая игра
	for (int i = 0; i < tapki_bratki.size(); i++)
		for (int i1 = 0; i1 < tapki_bratki.size(); i1++)
			tapki_bratki[i][i1][0] = { i,i1 };
	
	vector<vector<float>> graff;
	vector<vector<int>> id_graff;
	Create_graff(electives, students, graff, id_graff);

	for (int k = 0; k < graff.size(); k++)
		for (int i = 0; i < graff.size(); i++)
			for (int j = 0; j < graff.size(); j++)
			{
				if (graff[i][j] > graff[i][k] + graff[k][j])
				{
					graff[i][j] = graff[i][k] + graff[k][j];
					tapki_bratki[i][j] = tapki_bratki[i][k];
					tapki_bratki[i][j].insert(tapki_bratki[i][j].end(), tapki_bratki[k][j].begin(), tapki_bratki[k][j].end());
					if (i = j && graff[i][j] < 0)  // возможно не оптимальное расположение по времени // начало перестоновки отрицательного цикла
					{
						Student& first = students[id_graff[i][j]];
						int temp = search_student(electives[i], first.id);
						Student& temp_stud = first;
						for (pair<int, int>& trans : tapki_bratki[i][j]) {
							if (&first != &temp_stud) {
								Student& temp_stud2 = students[id_graff[trans.first][trans.second]];
								int menyai = search_student(electives[trans.first], temp_stud2.id);
								electives[trans.first].resultStudent[menyai] = temp_stud;
								// надо переприсвоить айди электива студенту
								temp_stud = temp_stud2;
							}
						}
						// замена первого. Костыль?
						int menyai = search_student(electives[0], first.id);
						electives[0].resultStudent[menyai] = temp_stud;
						Floyd(electives, students);
						return;
					}
				}
			}
}

void Clean_shit(vector<Elective> electives, vector <Student> students) {
	for (Elective& el : electives)
	{
		el.resultStudent = vector <Student>(0); // как-то надо обнулить
	}
	for (Student& st : students)
	{
		if (search_prior(st, st.first_elective_id) == 5)
			st.first_elective_id = -1;
		else electives[st.first_elective_id].resultStudent.push_back(st);
		if (search_prior(st, st.second_elective_id) == 5)
			st.second_elective_id = -1;
		else electives[st.second_elective_id].resultStudent.push_back(st);
	}
}

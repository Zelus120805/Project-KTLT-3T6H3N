#include "Class.h"
void createSchoolYear(listOfSchoolYear& lst)
{
	nodeSchoolYear* newNode = new nodeSchoolYear();
	newNode->nextYear = nullptr;
	std::cout << "Start year and End year: ";
	std::cin >> newNode->y.startYear >> newNode->y.endYear;
	if (lst.head == nullptr)
	{
		lst.head = newNode;
		return;
	}
	nodeSchoolYear* temp = lst.head;
	while (temp->nextYear != nullptr)
	{
		temp = temp->nextYear;
	}
	temp->nextYear = newNode;
}
void add1StudentToClass(Class& myClass)
{
	readFileStudent(myClass.lst, "accountStudent.txt");
	nodeStudent* Student = myClass.lst.head;
	while (Student!= nullptr)
	{
		std::cout << Student->student.account.userName << ",";
		std::cout << Student->student.account.passWord << ",";
		std::cout << Student->student.info.idStudent << ",";
		std::cout << Student->student.info.lastName << ",";
		std::cout << Student->student.info.firstName << ",";
		std::cout << Student->student.info.gender << ",";
		std::cout << Student->student.info.d.year << "," << Student->student.info.d.month << "," << Student->student.info.d.day << ",";
		std::cout << Student->student.info.socialId << "\n";
		Student = Student->next;
	}
}
void createClass(listClass& lst)
{
	nodeClass* newNode = new nodeClass();
	newNode->next = nullptr;
	newNode->myClass.lst.head= nullptr;
	add1StudentToClass(newNode->myClass);
	std::cout << "Nhap ten lop: ";
	std::cin >> newNode->myClass.nameClass;
	if (lst.head == nullptr)
	{
		lst.head = newNode;
		return;
	}
	nodeClass* temp = lst.head;
	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	temp->next= newNode;

}
void operateWithSchoolYear(listOfSchoolYear& lst)
{
	system("cls");

	int section;
	std::cout << "1. Create school year\n";
	std::cout << "2. View and operate with school year\n";
	std::cout << "3. Exit\n";
	while (std::cin >> section)
	{

		if (section == 1)
		{
			createSchoolYear(lst);
			system("cls");
			std::cout << "1. Create school year\n";
			std::cout << "2. View and operate with school year\n";
			std::cout << "3. Exit\n";
		}
		if (section == 2)
		{
			int i=1;
			nodeSchoolYear* temp = lst.head;
			while (temp != nullptr)
			{
				std::cout <<i<<". "<< temp->y.startYear << "-" << temp->y.endYear << "\n";
				temp = temp->nextYear;
				i++;
			}
			std::cout << "Select a school year\n";
			std::cin >> i;
			temp = lst.head;
			nodeSchoolYear* selected = nullptr;
			for (int j = 1; j < i; j++)
			{
				temp = temp->nextYear;
			}
			std::cout<<"Create class for " << temp->y.startYear << "-" << temp->y.endYear << "\n";
			createClass(temp->y.listOfClass);
			system("cls");
			std::cout << "1. Create school year\n";
			std::cout << "2. View and operate with school year\n";
			std::cout << "3. Exit\n";
		}
		if (section == 3)
		{
			system("cls");
			return;
		}
	}
	//std::cout << "";
}
#include "privateUser.h"
void studentRegister(listStudent& lst, const char fileName[])
{
	//Ghi ra file
	nodeStudent* Student = new nodeStudent();
	Student->next = nullptr;
	std::cout << "Username: \n";
	std::cin >> Student->student.account.userName;
	std::cout << "Password: \n";
	std::cin >> Student->student.account.passWord;
	std::cout << "Lastname: \n";
	std::cin >> Student->student.info.lastName;
	std::cout << "Firstname: \n";
	std::cin >> Student->student.info.firstName;
	std::cout << "Gender: \n";
	std::cin >> Student->student.info.gender;
	std::cout << "ID student: \n";
	std::cin >> Student->student.info.idStudent;
	std::cout << "Date of birth (yyyy mm dd): ";
	std::cin >> Student->student.info.d.year >> Student->student.info.d.month >> Student->student.info.d.day;
	std::cout << "Social ID: ";
	std::cin >> Student->student.info.socialId;
	if (lst.head == NULL)
	{
		lst.head = Student;
		return;
	}
	nodeStudent* temp = lst.head;
	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	temp->next = Student;
	std::ofstream accountStudent(fileName);
	if (accountStudent.is_open() == false)
	{
		return;
	}
	
}
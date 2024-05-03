#include "privateUser.h"
void studentRegister(listStudent& lst, const char fileName[])
{
	//Ghi ra file
	nodeStudent* Student = new nodeStudent();
	Student->next = nullptr;
	std::cout << "Username: ";
	std::cin >> Student->student.account.userName;
	std::cout << "Password: ";
	std::cin >> Student->student.account.passWord;
	std::cout << "Lastname: ";
	std::cin >> Student->student.info.lastName;
	std::cin.ignore();
	std::cout << "Firstname: ";
	std::getline( std::cin,Student->student.info.firstName);
	std::cout << "Gender: ";
	std::cin >> Student->student.info.gender;
	std::cout << "ID student: ";
	std::cin >> Student->student.info.idStudent;
	std::cout << "Date of birth (yyyy mm dd): ";
	std::cin >> Student->student.info.d.year >> Student->student.info.d.month >> Student->student.info.d.day;
	std::cout << "Social ID: ";
	std::cin >> Student->student.info.socialId;
	if (isStudentExisted(lst,Student->student.account.userName))
	{
		system("cls");
		std::cout << "Username has existed \n";
		return;
	}
	std::ofstream accountStudent;
	accountStudent.open(fileName, std::ios_base::app);
	if (lst.head == NULL)
	{
		lst.head = Student;
		accountStudent << Student->student.account.userName << ",";
		accountStudent << Student->student.account.passWord << ",";
		accountStudent << Student->student.info.idStudent << ",";
		accountStudent << Student->student.info.lastName << ",";
		accountStudent << Student->student.info.firstName << ",";
		accountStudent << Student->student.info.gender << ",";
		accountStudent << Student->student.info.d.year << "," << Student->student.info.d.month << "," << Student->student.info.d.day << ",";
		accountStudent << Student->student.info.socialId << "\n";
	}
	else
	{
		nodeStudent* temp = lst.head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = Student;
		if (accountStudent.is_open() == false)
		{
			
			return;
		}
		accountStudent << Student->student.account.userName << ",";
		accountStudent << Student->student.account.passWord << ",";
		accountStudent << Student->student.info.idStudent << ",";
		accountStudent << Student->student.info.lastName << ",";
		accountStudent << Student->student.info.firstName << ",";
		accountStudent << Student->student.info.gender << ",";
		accountStudent << Student->student.info.d.year << "," << Student->student.info.d.month << "," << Student->student.info.d.day<< ",";
		accountStudent << Student->student.info.socialId << "\n";
	}
	}
	
void readFileStudent(listStudent& lst, const char fileName[])
{
	std::ifstream accountStudent(fileName);
	if (accountStudent.is_open() == false)
	{
		return;
	}
	string temp;
	accountStudent.seekg(0, std::ios::beg);

	nodeStudent* Student1 = new nodeStudent();
	Student1->next = nullptr;
	getline(accountStudent, temp, ',');
	if (temp == "")
	{
		return;
	}
	Student1->student.account.userName = temp;
	getline(accountStudent, temp, ',');
	Student1->student.account.passWord = temp;
	getline(accountStudent, temp, ',');
	Student1->student.info.idStudent = std::stoi(temp);
	getline(accountStudent, temp, ',');
	Student1->student.info.lastName = temp;
	getline(accountStudent, temp, ',');
	Student1->student.info.firstName = temp;
	getline(accountStudent, temp, ',');
	Student1->student.info.gender = temp;
	getline(accountStudent, temp, ',');
	Student1->student.info.d.year = std::stoi(temp);
	getline(accountStudent, temp, ',');
	Student1->student.info.d.month = std::stoi(temp);
	getline(accountStudent, temp, ',');
	Student1->student.info.d.day = std::stoi(temp);
	getline(accountStudent, temp, '\n');
	Student1->student.info.socialId = temp;
	lst.head = Student1;
	nodeStudent* Temp = lst.head;
	while (!accountStudent.eof())
	{
		nodeStudent* Student = new nodeStudent();
		Student->next = nullptr;
		getline(accountStudent, temp, ',');
		if (temp == "")
		{
			delete Student;
			return;
		}
		Student->student.account.userName = temp;
		getline(accountStudent, temp, ',');
		Student->student.account.passWord = temp;
		getline(accountStudent, temp, ',');
		Student->student.info.idStudent = std::stoi(temp);
		getline(accountStudent, temp, ',');
		Student->student.info.lastName = temp;
		getline(accountStudent, temp, ',');
		Student->student.info.firstName = temp;
		getline(accountStudent, temp, ',');
		Student->student.info.gender = temp;
		getline(accountStudent, temp, ',');
		Student->student.info.d.year = std::stoi(temp);
		getline(accountStudent, temp, ',');
		Student->student.info.d.month = std::stoi(temp);
		getline(accountStudent, temp, ',');
		Student->student.info.d.day = std::stoi(temp);
		getline(accountStudent, temp, '\n');
		Student->student.info.socialId = temp;
		Temp->next = Student;
		Temp = Student;
	}
}
void studentLogIn(listStudent& lst, const char fileName[])
{
	std::ifstream accountStudent(fileName);
	if (!accountStudent.is_open())
	{
		return;
	}
	string Username,Password,name,pass;
	std::cout << "Username: ";
	std::cin >> Username;
	std::cout << "Password: ";
	std::cin >> Password;
	nodeStudent* temp = new nodeStudent();
	temp = lst.head;
	while (temp!=NULL)
	{
		if (temp->student.account.userName == Username && temp->student.account.passWord == Password)
		{
			workSessionOfStudent(temp);
			return;
		}
		temp = temp->next;
	}
	std::cout << "Fail to log in\n";
}
void workSessionOfStudent(nodeStudent*& node)
{
	system("cls");
	int section;
	std::cout << "Hello " << node->student.info.firstName << "\n";
	std::cout << "1. Changepass\n";
	std::cout << "2. View info\n";
	std::cout << "3. LogOut\n";
	while (true)
	{
		std::cin >> section;
		std::cin.ignore();
		if (section == 2)
		{
			viewInfo(node);
		}
		if (section == 3)
		{
			system("cls");
			return;
		}
	}
}
void viewInfo(nodeStudent* Student)
{
	if (Student == NULL)
	{
		return;
	}
	std::cout << "YOUR INFO\n";
	std::cout <<"Username: "<< Student->student.account.userName << "\n";
	std::cout << "Password: " << Student->student.account.passWord << "\n";
	std::cout << "ID student: " << Student->student.info.idStudent << "\n";
	std::cout << "Last name: " << Student->student.info.lastName << "\n";
	std::cout << "First name: " << Student->student.info.firstName << "\n";
	std::cout <<"Gender: "<< Student->student.info.gender << "\n";
	std::cout << "Date of birth " << Student->student.info.d.year << "," << Student->student.info.d.month << "," << Student->student.info.d.day << "\n";
	std::cout << "Social ID: " << Student->student.info.socialId << "\n";
}
bool isStudentExisted(listStudent lst, string userName)
{
	if (lst.head == nullptr)
	{
		return false;
	}
	nodeStudent* temp = lst.head;
	while (temp != NULL)
	{
		if (temp->student.account.userName == userName)
		{
			return true;
		}
		temp = temp->next;
	}
	return false;
}

void writeStudentToFile(listStudent lst, const char fileName[])
{
	std::ofstream accountStudent(fileName,std::ios_base::app);
	if (accountStudent.is_open() == false)
	{
		return;
	}
	nodeStudent* temp = lst.head;
	if (lst.head == NULL)
	{
		return;
	}
	while (temp != NULL)
	{
		accountStudent << temp->student.account.userName << ",";
		accountStudent << temp->student.account.passWord << ",";
		accountStudent << temp->student.info.idStudent << ",";
		accountStudent << temp->student.info.lastName << ",";
		accountStudent << temp->student.info.firstName << ",";
		accountStudent << temp->student.info.gender << ",";
		accountStudent << temp->student.info.d.year << "," << temp->student.info.d.month << "," << temp->student.info.d.day << ",";
		accountStudent << temp->student.info.socialId << "\n";
		temp = temp->next;
	}

}

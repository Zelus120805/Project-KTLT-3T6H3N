#include "privateUser.h"
#include "Windows.h"

void studentRegister(listStudent& lst, const char fileName[], int x, int y, int height)
{
	//Ghi ra file
	nodeStudent* Student = new nodeStudent();
	Student->next = nullptr;
	gotoXY(x + strlen("1. Username: "), y);
	getline(cin, Student->student.account.userName);

	gotoXY(x + strlen("2. Password: "), y + height * 1);
	getline(cin, Student->student.account.passWord);

	std::string fullName;
	gotoXY(x + strlen("3. Fullname: "), y + height * 2);
	getline(cin, fullName);
	size_t index = fullName.find(' ');
	if (index != string::npos)
	{
		Student->student.info.lastName = fullName.substr(0, index);
		Student->student.info.firstName = fullName.substr(index + 1);
	}
	else
	{
		Student->student.info.lastName = fullName;
		Student->student.info.firstName = "";
	}


	gotoXY(x + strlen("4. Gender: "), y + height * 3);
	getline(cin, Student->student.info.gender);

	gotoXY(x + strlen("5. ID student: "), y + height * 4);
	cin >> Student->student.info.idStudent; cin.ignore();


	gotoXY(x + strlen("6. Date of birth (dd mm yyyy): "), y + height * 5);
	cin >> Student->student.info.d.day >> Student->student.info.d.month >> Student->student.info.d.year;
	cin.ignore();

	gotoXY(x + strlen("7. Social ID: "), y + height * 6);
	getline(cin, Student->student.info.socialId);

	gotoXY(x + strlen("8. Class: "), y + height * 7);
	getline(cin, Student->student.info.inClass);

	if (isStudentExisted(lst,Student->student.account.userName))
	{
		system("cls");
		std::cout << "Username has existed \n";
		return;
	}
	std::ofstream accountStudent;
	accountStudent.open(fileName, std::ios_base::app);
	if (accountStudent.is_open() == false)
	{
		return;
	}
	if (lst.head == NULL)
	{
		lst.head = Student;
	}
	else
	{
		nodeStudent* temp = lst.head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = Student;
	}

	accountStudent << Student->student.account.userName << ",";
	accountStudent << Student->student.account.passWord << ",";
	accountStudent << Student->student.info.idStudent << ",";
	accountStudent << Student->student.info.lastName << ",";
	accountStudent << Student->student.info.firstName << ",";
	accountStudent << Student->student.info.gender << ",";
	accountStudent << Student->student.info.d.day << "/" << Student->student.info.d.month << "/" << Student->student.info.d.year << ",";
	accountStudent << Student->student.info.socialId << ",";
	accountStudent << Student->student.info.inClass << "\n";
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
//	getline(accountStudent, temp);
	nodeStudent* Student1 = new nodeStudent();
	Student1->next = nullptr;
	
	getline(accountStudent, temp, ',');
	if (temp == "")
	{
		return;
	}
	accountStudent.seekg(0, std::ios::beg);
	getline(accountStudent, temp);
	if (temp == "")
		return;


//	accountStudent.seekg(0, std::ios::beg);
	getline(accountStudent, temp,',');
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
	getline(accountStudent, temp, '/');
	Student1->student.info.d.day = std::stoi(temp);
	getline(accountStudent, temp, '/');
	Student1->student.info.d.month = std::stoi(temp);
	getline(accountStudent, temp, ',');
	Student1->student.info.d.year= std::stoi(temp);
	getline(accountStudent, temp, ',');
	Student1->student.info.socialId = temp;
	getline(accountStudent, temp, '\n');
	Student1->student.info.inClass = temp;
//	Student1->student.info.inClass 
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
		getline(accountStudent, temp, '/');
		Student->student.info.d.day = std::stoi(temp);
		getline(accountStudent, temp, '/');
		Student->student.info.d.month = std::stoi(temp);
		getline(accountStudent, temp, ',');
		Student->student.info.d.year = std::stoi(temp);
		getline(accountStudent, temp, ',');
		Student->student.info.socialId = temp;
		getline(accountStudent, temp, '\n');
		Student->student.info.inClass = temp;
		Temp->next = Student;
		Temp = Student;
	}
}
void studentLogIn(listStudent& lst, const char fileName[], listCourse list)
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
			workSessionOfStudent(temp,list);
			return;
		}
		temp = temp->next;
	}
	std::cout << "Fail to log in\n";
}
void workSessionOfStudent(nodeStudent*& node, listCourse list)
{
	system("cls");
	int section;
	std::cout << "Hello " << node->student.info.firstName << "\n";
	std::cout << "1. Changepass\n";
	std::cout << "2. View info\n";
	std::cout << "3. LogOut\n";
	std::cout << "4. Register Course\n";
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
		if (section == 4)
		{
			nodeCourse* temp = list.head;
			if (temp == NULL)
			{
				cout << "Khong co khoa hoc" << endl;
			}
			else
			{
				int i = 1, sub;
				while (temp != NULL)
				{
					cout << i << ". " << temp->crs.info.courseName << " - " << temp->crs.info.className << "\n";
					temp = temp->Next;
					i++;
				}
				i = 1;
				temp = list.head;
				cout << "Select course: ";
				cin >> sub;
				while (temp != NULL)
				{
					if (i == sub)
					{
						addAStudentToCourse(temp, node);
						break;
					}
					i++;
					temp = temp->Next;
				}

			}
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
	std::cout << "Date of birth " << Student->student.info.d.day << "/" << Student->student.info.d.month << "/" << Student->student.info.d.year << "\n";
	std::cout << "Social ID: " << Student->student.info.socialId << "\n";
	std::cout << "Class: " << Student->student.info.inClass << "\n";
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
		accountStudent << temp->student.info.d.day << "/" << temp->student.info.d.month << "/" << temp->student.info.d.year << ",";
		accountStudent << temp->student.info.socialId << ",";
		accountStudent << temp->student.info.inClass << "\n";
		temp = temp->next;
	}
}
//Nhóm hàm thao tác c?a staff
void addTailStaff(listStaff& lst, staffUser newStaff)
{
	nodeStaff* newNode = new nodeStaff();
	newNode->staff = newStaff;
	newNode->next = NULL;
	if (lst.head == NULL)
	{
		lst.head = newNode;
		return;
	}
	nodeStaff* temp = lst.head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}

void staffRegister(listStaff& lst, const char fileName[], int x, int y, int height)
{

	//Ghi ra file
	nodeStaff* staff = new nodeStaff();
	staff->next = NULL;
	gotoXY(x + strlen("1. Username: "), y);
	// std::cout << "Username: ";
	std::cin >> staff->staff.account.userName;
	gotoXY(x + strlen("2. Password: "), y + height * 1);
	// std::cout << "Password: ";
	std::cin >> staff->staff.account.passWord;
	std::cin.ignore();

	std::string fullName;
	gotoXY(x + strlen("3. Fullname: "), y + height * 2);
	// std::cout << "Lastname: ";
	std::getline(std::cin, fullName);
	size_t index = fullName.find(' ');
	if (index != string::npos)
	{
		staff->staff.lastName = fullName.substr(0, index);
		staff->staff.firstName = fullName.substr(index + 1);
	}
	else
	{
		staff->staff.lastName = fullName;
		staff->staff.firstName = "";
	}

	gotoXY(x + strlen("4. Gender: "), y + height * 3);
	// std::cout << "Gender: ";
	std::cin >> staff->staff.gender;
	gotoXY(x + strlen("5. ID staff: "), y + height * 4);
	// std::cout << "ID staff: ";
	std::cin >> staff->staff.IDofStaff;
	gotoXY(x + strlen("6. Date of birth (dd mm yyyy): "), y + height * 5);
	// std::cout << "Date of birth (yyyy mm dd): ";
	std::cin >> staff->staff.d.day >> staff->staff.d.month >> staff->staff.d.year;
	gotoXY(x + strlen("7. Social ID: "), y + height * 6);
	// std::cout << "Social ID: ";
	std::cin >> staff->staff.socialId;

	//?o?n này ki?m tra s? t?n t?i c?a tài kho?n, chút vi?t sau
	/*if (isstaffExisted(lst,staff->staff.account.userName))
	{
		system("cls");
		std::cout << "Username has existed \n";
		return;
	}*/

	std::ofstream accountstaff;
	accountstaff.open(fileName, std::ios_base::app);
	if (accountstaff.is_open() == false)
	{
		return;
	}
	addTailStaff(lst, staff->staff);

	accountstaff << staff->staff.account.userName << ",";
	accountstaff << staff->staff.account.passWord << ",";
	accountstaff << staff->staff.IDofStaff << ",";
	accountstaff << staff->staff.lastName << ",";
	accountstaff << staff->staff.firstName << ",";
	accountstaff << staff->staff.gender << ",";
	accountstaff << staff->staff.d.day << "/" << staff->staff.d.month << "/" << staff->staff.d.year << ",";
	accountstaff << staff->staff.socialId << ",";
}


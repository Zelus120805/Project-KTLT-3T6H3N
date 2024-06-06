#include "include.h"
#include "Menu.h"
#include "Windows.h"

//Nhóm hàm thao tác của Staff-------------------------------------------------
void createSchoolYear(listOfSchoolYear& lst)
{
	nodeSchoolYear* newNode = new nodeSchoolYear();
	newNode->nextYear = nullptr;
	ofstream fileSchoolYear("SchoolYear.txt", std::ios_base::app);
	if (!fileSchoolYear.is_open())
	{
		return;
	}
	std::cout << "Start year and End year: ";
	std::cin >> newNode->y.startYear >> newNode->y.endYear;
	if (lst.head == nullptr)
	{
		lst.head = newNode;
		fileSchoolYear << newNode->y.startYear << "-" << newNode->y.endYear << std::endl;
		return;
	}
	nodeSchoolYear* temp = lst.head;
	while (temp->nextYear != nullptr)
	{
		temp = temp->nextYear;
	}
	temp->nextYear = newNode;

	fileSchoolYear << newNode->y.startYear << "-" << newNode->y.endYear << std::endl;
}
void add1StudentToClass(Class& myClass, const char fileName[])
{
	readFileStudent(myClass.lst, fileName);
	nodeStudent* Student = myClass.lst.head;




	while (Student != nullptr)
	{
		//Thêm lớp
		Student->student.info.inClass = myClass.nameClass;
		std::cout << Student->student.account.userName << ",";
		std::cout << Student->student.account.passWord << ",";
		std::cout << Student->student.info.idStudent << ",";
		std::cout << Student->student.info.lastName << ",";
		std::cout << Student->student.info.firstName << ",";
		std::cout << Student->student.info.gender << ",";
		std::cout << Student->student.info.d.day << "/" << Student->student.info.d.month << "/" << Student->student.info.d.year << ",";
		std::cout << Student->student.info.socialId << ",";
		std::cout << Student->student.info.inClass << "\n";
		Student = Student->next;
	}
}
void createClass(listClass& lst)
{
	nodeClass* newNode = new nodeClass();
	newNode->next = nullptr;
	newNode->myClass.lst.head = nullptr;
	char fileName[100];
	std::cout << "Nhap ten lop: ";
	std::cin >> newNode->myClass.nameClass;

	//Kiểm tra tên lớp có tồn tại hay chưa?
	//nodeClass* check = lst.head;
	std::cout << "File input: ";
	cin >> fileName;
	/*while (check != NULL)
	{
		if (check->myClass.nameClass == newNode->myClass.nameClass)
		{
			add1StudentToClass(check->myClass, fileName);
			return;
		}
		check = check->next;
	}*/

	add1StudentToClass(newNode->myClass, fileName);

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
	temp->next = newNode;

}
void writeStudentToFileClass(Class a, const char fileName[])
{
	std::ofstream fileClass(fileName, std::ios_base::app);
	if (!fileClass)
		return;
	fileClass << a.nameClass << "|\n";
	//writeStudentToFile(a.lst, fileName);

	nodeStudent* temp = a.lst.head;
	if (a.lst.head == NULL)
	{
		return;
	}
	std::ofstream account("accountStudent.txt", std::ios_base::app);
	if (account.is_open() == false)
	{
		return;
	}
	while (temp != NULL)
	{
		temp->student.info.inClass = a.nameClass;
		fileClass << temp->student.account.userName << ",";
		fileClass << temp->student.account.passWord << ",";
		fileClass << temp->student.info.idStudent << ",";
		fileClass << temp->student.info.lastName << ",";
		fileClass << temp->student.info.firstName << ",";
		fileClass << temp->student.info.gender << ",";
		fileClass << temp->student.info.d.day << "/" << temp->student.info.d.month << "/" << temp->student.info.d.year << ",";
		fileClass << temp->student.info.socialId << "\n";
		account << temp->student.account.userName << ",";
		account << temp->student.account.passWord << ",";
		account << temp->student.info.idStudent << ",";
		account << temp->student.info.lastName << ",";
		account << temp->student.info.firstName << ",";
		account << temp->student.info.gender << ",";
		account << temp->student.info.d.day << "/" << temp->student.info.d.month << "/" << temp->student.info.d.year << ",";
		account << temp->student.info.socialId << ",";
		account << temp->student.info.inClass << "\n";
		temp = temp->next;
	}

	fileClass.close();
	account.close();
}
void addTailSchoolYear(listOfSchoolYear& lst, schoolYear addition)
{
	nodeSchoolYear* add = new nodeSchoolYear();
	add->nextYear = nullptr;
	add->y = addition;
	nodeSchoolYear* temp = lst.head;
	if (lst.head == NULL)
	{
		lst.head = add;
		return;
	}
	while (temp->nextYear != NULL)
	{
		temp = temp->nextYear;
	}
	temp->nextYear = add;
}
void readSchoolYear(listOfSchoolYear& lst)
{
	std::ifstream myFile("SchoolYear.txt");
	if (myFile.is_open() == false)
	{
		return;
	}
	myFile.seekg(0, ios::beg);
	string temp;
	getline(myFile, temp, '-');

	if (temp == "")
	{
		return;
	}
	myFile.seekg(0, ios::beg);
	//Chút viết tiếp, viết hàm addTail năm học đã.
	while (getline(myFile, temp, '-'))
	{

		nodeSchoolYear* newNode = new nodeSchoolYear();
		newNode->nextYear = NULL;
		//	getline(myFile, temp, '-');
		newNode->y.startYear = std::stoi(temp);
		getline(myFile, temp, '\n');
		newNode->y.endYear = std::stoi(temp);
		addTailSchoolYear(lst, newNode->y);
	}
}
void operateWithSchoolYear(listOfSchoolYear& lst)
{
	system("cls");
	readSchoolYear(lst);
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
			//Thực thi năm học 
			int i = 1;
			nodeSchoolYear* temp = lst.head;
			if (temp == NULL)
			{
				std::cout << "Please create at least 1 school year" << std::endl;
				return;
			}
			while (temp != nullptr)
			{
				std::cout << i << ". " << temp->y.startYear << "-" << temp->y.endYear << "\n";
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
			std::cout << "Create class for " << temp->y.startYear << "-" << temp->y.endYear << "\n";
			createClass(temp->y.listOfClass);//Tạo một lớp của năm học đó

			string fileName = to_string(temp->y.startYear) + "-" + to_string(temp->y.endYear) + ".txt";
			char* tmp = new char[fileName.length() + 1];
			fileName.copy(tmp, fileName.length());
			tmp[fileName.length()] = '\0';
			std::ofstream classOfSchoolYear(tmp, std::ios::app);

			if (classOfSchoolYear.is_open() == false)
			{
				std::cout << "Cannot open file" << std::endl;
				break;
			}

			nodeClass* Tmp = temp->y.listOfClass.head;
			while (Tmp->next != nullptr)
			{
				Tmp = Tmp->next;
			}
			//Ghi lớp cuối cùng vừa thêm vào file năm học tương ứng
			writeStudentToFileClass(Tmp->myClass, tmp);
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
}

void writeACourseToFile(nodeCourse* course, const string fileName)
{
	std::ofstream fileCourse(fileName, std::ios_base::app);
	if (fileCourse.is_open() == false)
	{
		std::cout << "Khong the tao file\n";
		return;
	}
	fileCourse << course->crs.info.idCourse << "," << course->crs.info.courseName << "," << course->crs.info.className << "," << course->crs.info.teacherName << "," << course->crs.info.numberOfCredits << "," << course->crs.info.numberOfCurrentStudent << "," << course->crs.info.maxStudent << "," << course->crs.info.dayOfWeek << "\n";
	fileCourse.close();
}
//Hàm tạo node mới 
void createNewCourse(listCourse& lst)
{
	nodeCourse* newCourse = new nodeCourse();
	//Nhập thông tin cơ bản một khóa học
	std::cin.ignore();
	std::cout << "Input ID course: ";
	getline(std::cin, newCourse->crs.info.idCourse);
	cin.ignore();
	std::cout << "Input courseName: ";
	getline(std::cin, newCourse->crs.info.courseName);

	std::cout << "Input Class name: ";
	getline(std::cin, newCourse->crs.info.className);
	std::cout << "Input teacher's Name: ";
	getline(std::cin, newCourse->crs.info.teacherName);
	std::cout << "Input day of week: ";
	std::cin >> newCourse->crs.info.dayOfWeek;
	std::cout << "Input number of credits: ";
	std::cin >> newCourse->crs.info.numberOfCredits;
	std::cin.ignore();
	std::cout << "Input max students: ";
	std::cin >> newCourse->crs.info.maxStudent;
	newCourse->Next = NULL;

	//Tạo file danh sách lớp 
	string fileListStudent = "./raw/" + newCourse->crs.info.courseName + "_" + newCourse->crs.info.className + ".txt";
	std::ofstream listStudentInCourse(fileListStudent, std::ios_base::app);
	if (listStudentInCourse.is_open() == false)
	{
		cout << "Khong the tao danh sach lop\n";
		return;
	}
	//Danh sách liên kết bình thường
	if (lst.head == NULL)
	{
		lst.head = newCourse;

		//Ghi ra file Lưu trữ các khóa học
		writeACourseToFile(newCourse, "./raw/Course.txt");

		//Ghi các trường cơ bản của file danh sách lớp ra 
		listStudentInCourse << "No," << "Student ID," << "Student Last Name," << "Student First Name," << "Gender," << "Other Mark(Assignment)," << "Midterm Mark," << "Final Mark," << "Average Mark\n";
		return;
	}
	writeACourseToFile(newCourse, "./raw/Course.txt");
	listStudentInCourse << "No," << "Student ID," << "Student Last Name," << "Student First Name," << "Gender," << "Other Mark(Assignment)," << "Midterm Mark," << "Final Mark," << "Average Mark\n";
	//Thao tác AddTail thôi.
	nodeCourse* temp = lst.head;
	while (temp->Next != NULL)
	{
		temp = temp->Next;
	}
	temp->Next = newCourse;
}

//Thêm một học sinh vào danh sách
void addAStudentToCourse(nodeCourse*& course, nodeStudent* student)
{
	string nameFile = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className + ".txt";
	std::ofstream fileList(nameFile, std::ios_base::app);

	string studentFile = "./raw/" + to_string(student->student.info.idStudent) + "_Course" + ".txt";
	std::ofstream fileStudent(studentFile, std::ios_base::app);

	if (!fileList.is_open() || !fileStudent.is_open())
	{
		std::cout << "Khong the mo file\n";
		return;
	}
	course->crs.info.numberOfCurrentStudent++;
	if (course->crs.info.numberOfCurrentStudent > course->crs.info.maxStudent)
	{
		std::cout << "The class has been full\n";
		return;
	}
	//Ghi ra file riêng của học sinh đó
	fileStudent << course->crs.info.idCourse << "," << course->crs.info.courseName << "," << course->crs.info.className << "," << course->crs.info.teacherName << "," << course->crs.info.numberOfCredits << "," << course->crs.info.dayOfWeek << ",0,0,0,0\n";
	//Cập nhật danh sách lớp của khóa học đó.


	fileList << course->crs.info.numberOfCurrentStudent << "," << student->student.info.idStudent << "," << student->student.info.lastName << "," << student->student.info.firstName << "," << student->student.info.gender << ",0,0,0,0\n";

	std::ifstream fileCourse("./raw/Course.txt");
	string temp, remember;

	while (!fileCourse.eof())
	{

		getline(fileCourse, temp);
		if (temp.find(course->crs.info.idCourse.c_str()) != std::string::npos && temp.find(course->crs.info.className.c_str()) != std::string::npos)
		{
			continue;
		}
		else
		{
			remember = remember + "\n" + temp;
		}
	}

	fileCourse.close();
	std::ofstream update("./raw/Course.txt");
	update << course->crs.info.idCourse << "," << course->crs.info.courseName << "," << course->crs.info.className << "," << course->crs.info.teacherName << "," << course->crs.info.numberOfCredits << "," << course->crs.info.numberOfCurrentStudent << "," << course->crs.info.maxStudent << "," << course->crs.info.dayOfWeek;
	update << remember;

	update.close();
}

//Viết hàm addTail khóa học
void addTailCourse(listCourse& lst, Course newCourse)
{
	nodeCourse* newNode = new nodeCourse();
	newNode->crs = newCourse;
	newNode->Next = NULL;
	if (lst.head == NULL)
	{
		lst.head = newNode;
		return;
	}
	nodeCourse* temp = lst.head;
	while (temp->Next != NULL)
	{
		temp = temp->Next;
	}
	temp->Next = newNode;
}

//Đọc file khóa học mỗi khi chạy chương trình
void readCourseFile(listCourse& lst)
{
	std::ifstream fileCourse("./raw/Course.txt");
	if (!fileCourse.is_open())
	{
		cout << "Khong the mo file\n";
		return;
	}
	string temp;
	while (!fileCourse.eof())
	{
		Course newCourse;
		getline(fileCourse, temp, ',');
		newCourse.info.idCourse = temp;
		if (temp == "")
			break;
		getline(fileCourse, temp, ',');
		newCourse.info.courseName = temp;
		getline(fileCourse, temp, ',');
		newCourse.info.className = temp;
		getline(fileCourse, temp, ',');
		newCourse.info.teacherName = temp;
		getline(fileCourse, temp, ',');
		newCourse.info.numberOfCredits = stoi(temp);
		getline(fileCourse, temp, ',');
		newCourse.info.numberOfCurrentStudent = stoi(temp);
		getline(fileCourse, temp, ',');
		newCourse.info.maxStudent = stoi(temp);
		getline(fileCourse, temp, '\n');
		newCourse.info.dayOfWeek = temp;
		addTailCourse(lst, newCourse);
	}
}

void addTailStudent(listStudent& lst, nodeStudent* newNode)
{
	if (lst.head == NULL)
	{
		lst.head = newNode;
		return;
	}
	nodeStudent* temp = lst.head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}

//Đọc sinh viên từ file.csv
void readStudentFromCSV(listStudent& lst, const string fileName)
{
	ifstream fileStudent(fileName);
	if (!fileStudent.is_open())
	{
		return;
	}
	//Đọc dòng đầu
	string temp;
	getline(fileStudent, temp);
	lst.head = NULL;

	while (!fileStudent.eof())
	{
		nodeStudent* Student = new nodeStudent();
		Student->next = NULL;
		getline(fileStudent, temp, ',');
		if (temp == "")
		{
			delete Student;
			return;
		}
		Student->student.info.idStudent = std::stoi(temp);
		getline(fileStudent, temp, ',');

		Student->student.info.lastName = temp;
		getline(fileStudent, temp, ',');

		Student->student.info.firstName = temp;
		getline(fileStudent, temp, ',');

		Student->student.info.gender = temp;
		getline(fileStudent, temp, '/');

		Student->student.info.d.day = std::stoi(temp);
		getline(fileStudent, temp, '/');
		Student->student.info.d.month = std::stoi(temp);
		getline(fileStudent, temp, ',');
		Student->student.info.d.year = std::stoi(temp);
		getline(fileStudent, temp, ',');

		Student->student.info.socialId = temp;
		getline(fileStudent, temp, '\n');

		Student->student.info.inClass = temp;
		addTailStudent(lst, Student);

	}

	fileStudent.close();
}

//Thêm n sinh viên vào khóa học từ file CSV
void addNStudentFromFile(nodeCourse*& course, const string fileName)
{
	ifstream fileStudent(fileName);
	if (!fileStudent.is_open())
	{
		std::cout << "Khong the doc file" << endl;
		return;
	}
	//Đọc từng sinh viên
	listStudent lst = { };
	lst.head = NULL;
	readStudentFromCSV(lst, fileName);
	//readFileStudent(lst, fileName.c_str());

	string courseName = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className + ".txt";
	ofstream fileCourse(courseName, ios_base::app);
	nodeStudent* temp = lst.head;
	while (temp != NULL)
	{
		addAStudentToCourse(course, temp);
		temp = temp->next;
	}
	std::cout << "Da them thanh cong\n";
	fileStudent.close();
}


//---------------------------------------------------------------------------

//Nhóm hàm thao tác tài khoản của sinh viên ------------------------------------------------------
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

	if (isStudentExisted(lst, Student->student.account.userName))
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
	getline(accountStudent, temp, ',');
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
	Student1->student.info.d.year = std::stoi(temp);
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
	string Username, Password, name, pass;
	std::cout << "Username: ";
	std::cin >> Username;
	std::cout << "Password: ";
	std::cin >> Password;
	nodeStudent* temp = new nodeStudent();
	temp = lst.head;
	while (temp != NULL)
	{
		if (temp->student.account.userName == Username && temp->student.account.passWord == Password)
		{
			workSessionOfStudent(temp, list);
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
	std::cout << "Username: " << Student->student.account.userName << "\n";
	std::cout << "Password: " << Student->student.account.passWord << "\n";
	std::cout << "ID student: " << Student->student.info.idStudent << "\n";
	std::cout << "Last name: " << Student->student.info.lastName << "\n";
	std::cout << "First name: " << Student->student.info.firstName << "\n";
	std::cout << "Gender: " << Student->student.info.gender << "\n";
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
	std::ofstream accountStudent(fileName, std::ios_base::app);
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
//------------------------------------------------------------------------------------------------
//Nhóm hàm thao tác của staff
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

//Quản lí đã tồn tại?
bool isStaffExisted(listStaff lst, string userName)
{
	if (lst.head == nullptr)
	{
		return false;
	}
	nodeStaff* temp = lst.head;
	while (temp != NULL)
	{
		if (temp->staff.account.userName == userName)
		{
			return true;
		}
		temp = temp->next;
	}
	return false;
}

//Quản lí đăng kí
void staffRegister(listStaff& lst, const char fileName[], int x, int y, int height)
{
	//Ghi ra file
	nodeStaff* Staff = new nodeStaff();
	Staff->next = nullptr;
	gotoXY(x + strlen("1. Username: "), y);
	// std::cout << "Username: ";
	std::cin >> Staff->staff.account.userName;
	gotoXY(x + strlen("2. Password: "), y + height * 1);
	// std::cout << "Password: ";
	std::cin >> Staff->staff.account.passWord;
	std::cin.ignore();

	std::string fullName;
	gotoXY(x + strlen("3. Fullname: "), y + height * 2);
	// std::cout << "Lastname: ";
	std::getline(std::cin, fullName);
	size_t index = fullName.find(' ');
	if (index != string::npos)
	{
		Staff->staff.lastName = fullName.substr(0, index);
		Staff->staff.firstName = fullName.substr(index + 1);
	}
	else
	{
		Staff->staff.lastName = fullName;
		Staff->staff.firstName = "";
	}

	gotoXY(x + strlen("4. Gender: "), y + height * 3);
	// std::cout << "Gender: ";
	std::cin >> Staff->staff.gender;
	gotoXY(x + strlen("5. ID Staff: "), y + height * 4);
	// std::cout << "ID Staff: ";
	std::cin >> Staff->staff.IDofStaff;
	gotoXY(x + strlen("6. Date of birth (dd mm yyyy): "), y + height * 5);
	// std::cout << "Date of birth (yyyy mm dd): ";
	std::cin >> Staff->staff.d.day >> Staff->staff.d.month >> Staff->staff.d.year;
	gotoXY(x + strlen("7. Social ID: "), y + height * 6);
	// std::cout << "Social ID: ";
	std::cin >> Staff->staff.socialId;

	if (isStaffExisted(lst, Staff->staff.account.userName))
	{
		system("cls");
		std::cout << "Username has existed \n";
		return;
	}

	std::ofstream accountStaff;
	accountStaff.open(fileName, std::ios_base::app);
	if (accountStaff.is_open() == false)
	{
		return;
	}
	if (lst.head == NULL)
	{
		lst.head = Staff;
	}
	else
	{
		nodeStaff* temp = lst.head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = Staff;
	}

	accountStaff << Staff->staff.account.userName << ",";
	accountStaff << Staff->staff.account.passWord << ",";
	accountStaff << Staff->staff.IDofStaff << ",";
	accountStaff << Staff->staff.lastName << ",";
	accountStaff << Staff->staff.firstName << ",";
	accountStaff << Staff->staff.gender << ",";
	accountStaff << Staff->staff.d.day << "/" << Staff->staff.d.month << "/" << Staff->staff.d.year << ",";
	accountStaff << Staff->staff.socialId << ",";
}

//Đọc file staff
void readFileStaff(listStaff& lst, const char fileName[])
{
	ifstream fileStaff(fileName);
	if (!fileStaff.is_open())
	{
		cout << "Khong the mo file de doc" << endl;
		return;
	}
	string temp;
	while (!fileStaff.eof())
	{
		staffUser Staff;
		getline(fileStaff, temp, ',');
		if (temp == "")
		{
			return;
		}
		Staff.account.userName = temp;
		getline(fileStaff, temp, ',');
		Staff.account.passWord = temp;
		getline(fileStaff, temp, ',');
		Staff.IDofStaff = std::stoi(temp);
		getline(fileStaff, temp, ',');
		Staff.lastName = temp;
		getline(fileStaff, temp, ',');
		Staff.firstName = temp;
		getline(fileStaff, temp, ',');
		Staff.gender = temp;
		getline(fileStaff, temp, '/');
		Staff.d.day = std::stoi(temp);
		getline(fileStaff, temp, '/');
		Staff.d.month = std::stoi(temp);
		getline(fileStaff, temp, ',');
		Staff.d.year = std::stoi(temp);
		getline(fileStaff, temp, ',');
		Staff.socialId = temp;
		getline(fileStaff, temp, '\n');
		addTailStaff(lst, Staff);
	}
	fileStaff.close();
}
//Xem thông tin staff
void viewInfoStaff(nodeStaff* staff)
{
	if (staff == NULL)
	{
		return;
	}
	std::cout << "YOUR INFO\n";
	std::cout << "Username: " << staff->staff.account.userName << "\n";
	std::cout << "Password: " << staff->staff.account.passWord << "\n";
	std::cout << "ID Staff: " << staff->staff.IDofStaff << "\n";
	std::cout << "Last name: " << staff->staff.lastName << "\n";
	std::cout << "First name: " << staff->staff.firstName << "\n";
	std::cout << "Gender: " << staff->staff.gender << "\n";
	std::cout << "Date of birth " << staff->staff.d.day << "/" << staff->staff.d.month << "/" << staff->staff.d.year << "\n";
	std::cout << "Social ID: " << staff->staff.socialId << "\n";
}

//Đăng nhập staff
void staffLogIn(listStaff& staff, listOfSchoolYear& lstSchoolYear, listCourse& lstCourse)
{
	ifstream fileStaff("accountStaff.txt");
	if (!fileStaff.is_open())
	{
		cout << "Cannot open file\n";
		return;
	}
	string Username, Password, name, pass;
	std::cout << "Username: ";
	std::cin >> Username;
	std::cout << "Password: ";
	std::cin >> Password;
	nodeStaff* temp = new nodeStaff();
	temp = staff.head;
	while (temp != NULL)
	{
		if (temp->staff.account.userName == Username && temp->staff.account.passWord == Password)
		{
			workSessionOfStaff(temp,lstSchoolYear,lstCourse);
			return;
		}
		temp = temp->next;
	}
	std::cout << "Fail to log in\n";
}
//Phiên làm việc của staff
void workSessionOfStaff(nodeStaff*& staff, listOfSchoolYear& lstSchoolYear, listCourse& lstCourse)
{
	system("cls");
	int optn;
	cout << "Hello " << staff->staff.firstName << "\n";
	cout << "1. View Info\n";
	cout << "2. Change Password\n";
	cout << "3. Log out\n";
	cout << "4. School year\n";
	cout << "5. Semester\n";
	cout << "6. Create Class\n";
	cout << "7. Course\n";
	while (true)
	{
		cin >> optn;
		cin.ignore();
		switch (optn)
		{
		case 2:
		{
			viewInfoStaff(staff);
			break;
		}
		case 3:
			return;
		}
	}
		

}
//------------------------------------------------------------------------------------------------

/*Menu*/
void drawBox(int x, int y, int width, int height, std::string option)
{

	for (int i = x + 1; i < x + width; i++)
	{
		gotoXY(i, y);
		std::cout << (char)196;
		gotoXY(i, y + height);
		std::cout << (char)196;
	}

	for (int j = y + 1; j < y + height; j++)
	{
		gotoXY(x, j);
		std::cout << (char)179;
		gotoXY(x + width, j);
		std::cout << (char)179;
	}

	gotoXY(x, y); std::cout << (char)218;
	gotoXY(x + width, y); std::cout << (char)191;
	gotoXY(x, y + height); std::cout << (char)192;
	gotoXY(x + width, y + height); std::cout << (char)217;
	gotoXY(x + 1, y + 1); std::cout << option;
}

void drawNBox(int x, int y, int width, int height, int nBox, std::string* option)
{
	for (int i = 0; i < nBox; i++)
		drawBox(x, y + i * height, width, height, option[i]);

	for (int i = 1; i < nBox; i++)
	{
		gotoXY(x, y + i * height); std::cout << (char)195;
		gotoXY(x + width, y + i * height); std::cout << (char)180;
	}
}

void focus(int x, int y, int width, char c)
{
	gotoXY(x + width - 1, y + 1); std::cout << c;
}

void menuLogin(int x, int y, int width, int height, int nBox)
{
	system("cls");
	ShowCur(0);

	std::string* option = new std::string[nBox];
	option[0] = "1. Register";
	option[1] = "2. Sign in";
	option[2] = "3. Add a school year";
	option[3] = "4. Create a course";
	option[4] = "5. Quit";
	drawNBox(x, y, width, height, nBox, option);

	delete[] option;
}

void chooseOptionMenuLogin(listStaff&listS,listStudent& listST, listOfSchoolYear& listSY, listCourse& listOfCourse)
{
	int x = 40, y = 5, width = 50, height = 2, nBox = 5;
	int newX = x, newY = y;
	int oldX = x, oldY = y;
	bool check = true;
	int count = 0;
	while (true)
	{
		if (count == 0)
		{
			menuLogin(x, y, width, height, nBox);
			count++;
		}
		if (check == true)
		{
			gotoXY(oldX, oldY);
			focus(oldX, oldY, width, ' ');
			oldX = newX, oldY = newY;

			focus(newX, newY, width, (char)174);
			check = false;
		}
		if (_kbhit())
		{
			char choose = _getch();
			if (choose == 13)
			{
				if (oldY == y)
				{
					int optn;
					cout << "Staff or student";
					cin >> optn;
					cin.ignore();
					if (optn == 1)
					{
						menuStaffRegister(40, 5, 50, 2, 7);
						staffRegister(listS, "accountStaff.txt", x + 1, y + 1, height);
					}
					else
					{
						menuStudentRegister(40, 5, 50, 2, 8);
						studentRegister(listST, "accountStudent.txt", x + 1, y + 1, height);
					}
				}
				else if (oldY == y + height * 1)
				{
					int optn;
					cout << "Staff or student";
					cin >> optn;
					cin.ignore();
					if (optn == 1)
					{
						readFileStaff(listS, "accountStaff.txt");
						staffLogIn(listS, listSY, listOfCourse);
					}
					else
					{
						readFileStudent(listST, "accountStudent.txt");
						studentLogIn(listST, "accountStudent.txt", listOfCourse);//Sua tham so ham LogIn de vao phien dang nhap cua user do.
					}
				}
				else if (oldY == y + height * 2)
				{
					operateWithSchoolYear(listSY);
				}
				else if (oldY == y + height * 3)
				{

					createNewCourse(listOfCourse);
				}
				else if (oldY == y + height * 4)
				{

					return;
				}


				count = 0;
			}
			else if (choose == -32)
			{
				choose = _getch();
				if (choose == 72 && newY > y)
					newY -= 2;
				else if (choose == 80 && newY < y + height * (nBox - 1))
					newY += 2;
			}

			check = true;
		}
	}
}

void menuStudentRegister(int x, int y, int width, int height, int nBox)
{
	system("cls");
	ShowCur(1);

	std::string* option = new std::string[nBox];
	option[0] = "1. Username: ";
	option[1] = "2. Password: ";
	option[2] = "3. Fullname: ";
	option[3] = "4. Gender: ";
	option[4] = "5. ID student: ";
	option[5] = "6. Date of birth (dd mm yyyy): ";
	option[6] = "7. Social ID: ";
	option[7] = "8. Class: ";

	drawNBox(x, y, width, height, nBox, option);

	delete[] option;
}

void menuStaffRegister(int x, int y, int width, int height, int nBox)
{
	system("cls");
	ShowCur(1);

	std::string* option = new std::string[nBox];
	option[0] = "1. Username: ";
	option[1] = "2. Password: ";
	option[2] = "3. Fullname: ";
	option[3] = "4. Gender: ";
	option[4] = "5. ID staff: ";
	option[5] = "6. Date of birth (dd mm yyyy): ";
	option[6] = "7. Social ID: ";

	drawNBox(x, y, width, height, nBox, option);

	delete[] option;
}
/*User*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void userRegister(listUser& lst, const char fileName[])
{
	std::ofstream account;
	account.open(fileName, std::ios_base::app);
	if (account.is_open() == false)
	{
		return;
	}
	User user;
	std::cout << "Username: ";
	std::cin >> user.userName;
	std::cout << "Password: ";
	std::cin >> user.passWord;
	account << user.userName << "," << user.passWord << "\n";
	nodeUser* newNode = new nodeUser;
	newNode->user = user;
	newNode->next = NULL;
	if (lst.head == NULL)
	{
		lst.head = newNode;
	}
	else
	{
		nodeUser* temp = new nodeUser();
		temp = lst.head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	account.close();
}
void userLogIn(listUser& lst)
{
	std::ifstream account;
	account.open("account.txt");
	if (account.is_open() == false)
	{
		return;
	}
	User user;
	std::cout << "Username: ";
	std::cin >> user.userName;
	std::cout << "Password: ";
	std::cin >> user.passWord;
	string temp;
	while (!account.eof())
	{
		User user1;
		getline(account, temp, ',');
		user1.userName = temp;
		getline(account, temp, '\n');
		user1.passWord = temp;
		if (user1.userName == user.userName && user1.passWord == user.passWord)
		{
			//workSession( user);//Neu ten dang nhap va mat khau dung thi vao phien dang nhap
			return;
		}
	}
	std::cout << "Account does not exist" << "\n";
	system("cls");//Them ham xoa man hinh cho dep
	account.close();
}

//void changePassword(listStudent *lst, const char fileName[],const string userName, const string newPass)
//{
//	std::ifstream oldFile(fileName);
//	std::ofstream newFile("temp.txt");
//
//	if (!oldFile.is_open() || !newFile.is_open()) {
//		std::cout << "Can't open file" << std::endl;
//		return;
//	}
//
//	std::string name, pass;
//	int count = 0;
//
//	while (getline(oldFile, name, ',')) {
//		getline(oldFile, pass);
//		if (name.empty() || pass.empty()) break;
//
//		if (count == 0)
//		{
//			if (name == userName)
//			{
//				newFile << name << "," << newPass << "\n";
//				count++;
//			}
//			else
//				newFile << name << "," << pass << "\n";
//		}
//		else
//			newFile << name << "," << pass << "\n";
//
//		name.clear();
//		pass.clear();
//	}
//	oldFile.close();
//	newFile.close();
//	if (count == 0) std::cout << "Can't find entered username";
//	string line;
//	std::ifstream new_File("temp.txt");
//	std::ofstream old_File(fileName);
//
//	if (!new_File.is_open() || !old_File.is_open()) {
//		std::cout << "Can't change the password" << std::endl;
//		return;
//	}
//	while (getline(new_File, line))
//	{
//		old_File << line << "\n";
//	}
//	cout << "Your pass has been changed" << std::endl;
//}
//
//
//void workSession( User& user)
//{
//	system("cls");
//	if (user.userName.length() == 0)
//	{
//		return;
//	}
//
//	int section;
//	while (true)
//	{
//		std::cout << "Hello " << user.userName << "\n";
//		std::cout << "1. Change password" << "\n";
//		std::cout << "2. Log out" << "\n";
//		cin >> section;
//		if (section == 1)
//		{
//			string newPass;
//			std::cin >> newPass;
//			//changePassword(user.userName,newPass);
//		}
//		if (section == 2)
//		{
//			system("cls");
//			break;
//		}
//	}
//}


/*Windows*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void ShowCur(bool showCursor)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showCursor;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoXY(int x, int y)
{
	COORD coord = { };
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//Nhóm hàm giải phóng bộ nhớ ---------------------------------------
//Xóa sạch sinh viên
void deleteAllStudent(listStudent& lst)
{
	if (lst.head == NULL)
	{
		std::cout << "List rong" << endl;
		return;
	}
	while (lst.head != NULL)
	{
		nodeStudent* deletion = lst.head;
		lst.head = lst.head->next;
		delete deletion;
	}
}
//Xóa sạch course
void deleteAllCourse(listCourse& lst)
{
	if (lst.head == NULL)
	{
		std::cout << "List rong" << endl;
		return;
	}
	while (lst.head != NULL)
	{
		nodeCourse* deletion = lst.head;
		lst.head = lst.head->Next;
		delete deletion;
	}
}
//Xóa sạch schoolyear
void deleteAllSchoolYear(listOfSchoolYear& lst)
{
	if (lst.head == NULL)
	{
		std::cout << "List rong" << endl;
		return;
	}
	while (lst.head != NULL)
	{
		nodeSchoolYear* deletion = lst.head;
		lst.head = lst.head->nextYear;
		delete deletion;
	}
}
//Xóa sạch staff
void deleteAllStaff(listStaff& lst)
{
	if (lst.head == NULL)
	{
		std::cout << "List rong" << endl;
		return;
	}
	while (lst.head != NULL)
	{
		nodeStaff* deletion = lst.head;
		lst.head = lst.head->next;
		delete deletion;
	}
}
//----------------------------------------------------------------
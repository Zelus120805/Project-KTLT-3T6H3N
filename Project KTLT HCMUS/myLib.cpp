#include "myLib.h"

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

void viewListCourse(listCourse lst)
{
	nodeCourse* temp = lst.head;
	if (temp == NULL)
	{
		cout << "Khong co khoa hoc nao\n";
		return;
	}
	int i = 1;
	while (temp != NULL)
	{
		cout << i << "." << temp->crs.info.idCourse << " - " << temp->crs.info.courseName << " - " << temp->crs.info.className << endl;
		i++;
		temp = temp->Next;
	}
	delete temp;
}

void viewListStudentsInCourse(listCourse lst)
{
	viewListCourse(lst);
	int choice;
	cout << "Nhap lop muon xem danh sach hoc sinh: ";
	cin >> choice;
	if (choice < 1)
	{
		cout << " Khong hop le.\n";
		return;
	};
	nodeCourse* temp = lst.head;
	int i = 1;
	while (temp != NULL)
	{
		if (i != choice)
		{
			i++;
			temp = temp->Next;
		}
		else
		{
			ifstream fin;
			string fileName = "./raw/" + temp->crs.info.courseName + "_" + temp->crs.info.className + ".txt";
			fin.open(fileName);
			if (fin.is_open() == false)
			{
				cout << "Khong the tao file\n";
				return;
			}
			string tempFirstLine;
			getline(fin,tempFirstLine);
			string tempLine;
			int stt = 1;
			while (!fin.eof())
			{
				getline(fin,tempLine);
				if (tempLine == "")
				{
					break;
				}
				cout << stt << ".";
				int dem = 0;
				//Chạy 2 lần while để tới Last Name
				while (tempLine[dem] != ',')
				{
					dem++;
				}
				dem++;
				while (tempLine[dem] != ',')
				{
					dem++;
				}
				dem++;
				// ghi Last Name
				while (tempLine[dem] != ',')
				{
					cout << tempLine[dem];
					dem++;
				}
				dem++;
				cout << " ";
				// ghi First Name
				while (tempLine[dem] != ',')
				{
					cout << tempLine[dem];
					dem++;
				}
				cout << endl;
				stt++;
			}
			break;
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
void studentRegister(listStudent& lst, const char fileName[], int x, int y)
{
	ShowCur(1);
	nodeStudent* Student = new nodeStudent();
	Student->next = nullptr;

	gotoXY(x + 2, y + 2); cout << "Username: "; drawBox(x + 2 + strlen("Username: "), y + 1, 65 - strlen("Username: "), 2);
	bool check = false;
	while (true)
	{
		string str = "Username has existed!";
		gotoXY(x + 2 + strlen("Username: ") + 1, y + 2); getline(cin, Student->student.account.userName);
		if (check == true)
		{
			for (int i = 0; i < str.length(); i++) {
				gotoXY(WIDTH_CONSOLE / 2 - 8 + i, HEIGHT_CONSOLE / 2 + 7);
				cout << " ";
			}
		}

		if (isStudentExisted(lst, Student->student.account.userName))
		{
			setTextColor(red);
			for (int i = 0; i < str.length(); i++) {
				gotoXY(WIDTH_CONSOLE / 2 - 8 + i, HEIGHT_CONSOLE / 2 + 7);
				cout << str[i];
				Sleep(40);
			}
			Sleep(500);
			setTextColor(black);

			for (int i = 0; i < Student->student.account.userName.length(); i++)
			{
				gotoXY(x + 2 + strlen("Username: ") + 1 + i, y + 2);
				cout << " ";
			}

			check = true;
		}
		else
			break;
	}

	gotoXY(x + 2, y + 5); cout << "Password: "; drawBox(x + 2 + strlen("Password: "), y + 4, 65 - strlen("Password: "), 2);
	gotoXY(x + 2 + strlen("Password: ") + 1, y + 5); getline(cin, Student->student.account.passWord);

	std::string fullName;
	gotoXY(x + 2, y + 8); cout << "Fullname: "; drawBox(x + 2 + strlen("Fullname: "), y + 7, 65 - strlen("Fullname: "), 2);
	gotoXY(x + 2 + strlen("Fullname: ") + 1, y + 8); getline(cin, fullName);
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

	gotoXY(x + 2, y + 11); cout << "Date Of Birth(dd mm yyyy): "; drawBox(x + 2 + strlen("Date of birth(dd mm yyyy): "), y + 10, 65 - strlen("Date of birth(dd mm yyyy): "), 2);
	gotoXY(x + 2 + strlen("Date of birth(dd mm yyyy): ") + 1, y + 11); 
	cin >> Student->student.info.d.day >> Student->student.info.d.month >> Student->student.info.d.year; cin.ignore();

	gotoXY(x + 2, y + 14); cout << "Gender(Male/Female): "; drawBox(x + 2 + strlen("Gender(Male/Female): "), y + 13, 8, 2);
	gotoXY(x + 2 + strlen("Gender(Male/Female): ") + 1, y + 14); getline(cin, Student->student.info.gender);

	gotoXY(x + 35, y + 14); cout << "ID Student: "; drawBox(x + 35 + strlen("ID student: "), y + 13, 20, 2);
	gotoXY(x + 35 + strlen("ID student: ") + 1, y + 14); 
	cin >> Student->student.info.idStudent; cin.ignore();

	gotoXY(x + 2, y + 17); cout << "Social ID: "; drawBox(x + 2 + strlen("Social ID: "), y + 16, 18, 2);
	gotoXY(x + 2 + strlen("Social ID: ") + 1, y + 17); getline(cin, Student->student.info.socialId);

	gotoXY(x + 35, y + 17); cout << "Class: "; drawBox(x + 35 + strlen("Class: "), y + 16, 25, 2);
	gotoXY(x + 35 + strlen("Class: ") + 1, y + 17); getline(cin, Student->student.info.inClass);

	setTextColor(yellow);
	string str = "Register succesful!";
	for (int i = 0; i < str.length(); i++) {
		gotoXY(x - 30 + 7 + i, y + 17);
		cout << str[i];
		Sleep(40);
	}
	ShowCur(0);
	Sleep(500);

	//Ghi ra file
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
//Đổi mật khẩu cho sinh viên. 
void changePasswordForStudent(nodeStudent*& student, const char fileName[])
{
	ifstream fileStudent(fileName);
	if (!fileStudent.is_open())
	{
		cout << "Cannot open file\n";
		return;
	}
	string line, pass;

	cout << "Input old password: ";
	std::getline(cin, pass);

	while (pass != student->student.account.passWord)
	{
		cout << "Password is not correct\n";
		cout << "Input old password: ";
		std::getline(cin, pass);
	}

	string remember;

	while (!fileStudent.eof())
	{
		std::getline(fileStudent, line);
		if (line.find(student->student.account.userName.c_str()) != std::string::npos && line.find(student->student.account.passWord.c_str()) != std::string::npos && line.find(to_string(student->student.info.idStudent).c_str()) != std::string::npos)
		{
			continue;
		}
		else
		{
			remember = remember + "\n" + line;
		}
	}

	cout << "Input new password: ";
	std::getline(cin, student->student.account.passWord);
	fileStudent.close();

	ofstream newFileStudent;
	newFileStudent.open(fileName);
	newFileStudent << remember << "\n";
	newFileStudent << student->student.account.userName << ",";
	newFileStudent << student->student.account.passWord << ",";
	newFileStudent << student->student.info.idStudent << ",";
	newFileStudent << student->student.info.lastName << ",";
	newFileStudent << student->student.info.firstName << ",";
	newFileStudent << student->student.info.gender << ",";
	newFileStudent << student->student.info.d.day << "/" << student->student.info.d.month << "/" << student->student.info.d.year << ",";
	newFileStudent << student->student.info.socialId << ",";
	newFileStudent << student->student.info.inClass << "\n";
	newFileStudent.close();
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
void staffRegister(listStaff& lst, const char fileName[], int x, int y)
{
	ShowCur(1);
	nodeStaff* Staff = new nodeStaff();
	Staff->next = nullptr;

	gotoXY(x + 2, y + 2); cout << "Username: "; drawBox(x + 2 + strlen("Username: "), y + 1, 65 - strlen("Username: "), 2);
	bool check = false;
	while (true)
	{
		string str = "Username has existed!";
		gotoXY(x + 2 + strlen("Username: ") + 1, y + 2); getline(cin, Staff->staff.account.userName);
		if (check == true)
		{
			for (int i = 0; i < str.length(); i++) {
				gotoXY(WIDTH_CONSOLE / 2 - 8 + i, HEIGHT_CONSOLE / 2 + 7);
				cout << " ";
			}
		}

		if (isStaffExisted(lst, Staff->staff.account.userName))
		{
			setTextColor(red);
			for (int i = 0; i < str.length(); i++) {
				gotoXY(WIDTH_CONSOLE / 2 - 8 + i, HEIGHT_CONSOLE / 2 + 7);
				cout << str[i];
				Sleep(40);
			}
			Sleep(500);
			setTextColor(black);

			for (int i = 0; i < Staff->staff.account.userName.length(); i++)
			{
				gotoXY(x + 2 + strlen("Username: ") + 1 + i, y + 2);
				cout << " ";
			}

			check = true;
		}
		else
			break;
	}

	gotoXY(x + 2, y + 5); cout << "Password: "; drawBox(x + 2 + strlen("Password: "), y + 4, 65 - strlen("Password: "), 2);
	gotoXY(x + 2 + strlen("Password: ") + 1, y + 5); getline(cin, Staff->staff.account.passWord);

	std::string fullName;
	gotoXY(x + 2, y + 8); cout << "Fullname: "; drawBox(x + 2 + strlen("Fullname: "), y + 7, 65 - strlen("Fullname: "), 2);
	gotoXY(x + 2 + strlen("Fullname: ") + 1, y + 8); getline(cin, fullName);
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

	gotoXY(x + 2, y + 11); cout << "Date Of Birth(dd mm yyyy): "; drawBox(x + 2 + strlen("Date of birth(dd mm yyyy): "), y + 10, 65 - strlen("Date of birth(dd mm yyyy): "), 2);
	gotoXY(x + 2 + strlen("Date Of Birth(dd mm yyyy): ") + 1, y + 11);
	cin >> Staff->staff.d.day >> Staff->staff.d.month >> Staff->staff.d.year; cin.ignore();

	gotoXY(x + 2, y + 14); cout << "Gender(Male/Female): "; drawBox(x + 2 + strlen("Gender(Male/Female): "), y + 13, 8, 2);
	gotoXY(x + 2 + strlen("Gender(Male/Female): ") + 1, y + 14); getline(cin, Staff->staff.gender);

	gotoXY(x + 35, y + 14); cout << "ID Staff: "; drawBox(x + 35 + strlen("ID Staff: "), y + 13, 22, 2);
	gotoXY(x + 35 + strlen("ID Staff: ") + 1, y + 14);
	cin >> Staff->staff.IDofStaff; cin.ignore();

	gotoXY(x + 2, y + 17); cout << "Social ID: "; drawBox(x + 2 + strlen("Social ID: "), y + 16, 18, 2);
	gotoXY(x + 2 + strlen("Social ID: ") + 1, y + 17); getline(cin, Staff->staff.socialId);

	setTextColor(yellow);
	string str = "Register succesful!";
	for (int i = 0; i < str.length(); i++) {
		gotoXY(x - 30 + 7 + i, y + 17);
		cout << str[i];
		Sleep(40);
	}
	ShowCur(0);
	Sleep(500);

	//Ghi ra file
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
	accountStaff << Staff->staff.socialId << "," << endl;
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
//------------------------DELETE A STUDENT ----------------------------
bool isInCourse(nodeStudent* student, nodeCourse* course)
{
	string studentFile = "./raw/" + to_string(student->student.info.idStudent) + "_Course" + ".txt";
	std::ifstream fileStudent(studentFile);

	if (!fileStudent.is_open())
	{
		return false;
	}
	string line;
	while (std::getline(fileStudent, line))
	{
		if (line.find(course->crs.info.courseName.c_str()) != string::npos)
		{
			return true;
		}
	}
	return false;
}
void deleteNodeStudent(listStudent& lst, nodeStudent* deletion)
{
	if (lst.head == NULL)
	{
		return;
	}
	//N?u node head th?a mãn thì xóa d?n khi nào node head không còn th?a n?a 
	while (lst.head->student.info.idStudent == deletion->student.info.idStudent)
	{
		nodeStudent* temp = lst.head;
		lst.head = lst.head->next;
		delete temp;
		//N?u xóa h?t danh sách, thì return;
		if (lst.head == NULL)
		{
			return;
		}

	}
	//N?u node head không còn th?a n?a, ta b?t d?u duy?t node k? head và xóa theo ki?u prev - curr d? xóa node gi?a.
	nodeStudent* curr = lst.head->next;
	nodeStudent* prev = lst.head;
	//Ðã xu?ng du?c dây thì còn ít nh?t 1 node không th?a mãn. 
	if (lst.head->next == NULL)
	{
		return;
	}
	//Duy?t d?n node áp chót thôi. 
	while (curr->next != NULL)
	{
		if (curr->student.info.idStudent == deletion->student.info.idStudent)
		{
			nodeStudent* temp = curr;
			curr = curr->next;
			prev->next = curr;
			delete temp;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	if (curr->student.info.idStudent == deletion->student.info.idStudent)
	{
		prev->next = NULL;
		delete curr;
	}
}
void printStudent(listStudent lst)
{
	if (lst.head == NULL)
	{
		cout << "List is empty\n";
		return;
	}
	nodeStudent* temp = lst.head;
	int i = 1;
	while (temp != NULL)
	{
		cout << i << ": " << temp->student.info.idStudent << " - " << temp->student.info.lastName << " " << temp->student.info.firstName << endl;
		temp = temp->next;
		i++;
	}
}
nodeStudent* goToStudent(int No, listStudent lst)
{
	if (lst.head == NULL)
	{
		cout << "List is empty\n";
		return NULL;
	}
	int i = 1;
	nodeStudent* temp = lst.head;
	while (No != i)
	{
		temp = temp->next;
		i++;
	}
	return temp;

}
void readListStudentOfACourse(listStudent& lst, const string fileName)
{
	ifstream fileStudent(fileName);
	if (!fileStudent.is_open())
	{
		return;
	}
	//Đọc dòng đầu
	string temp;
	std::getline(fileStudent, temp);
	lst.head = NULL;

	while (!fileStudent.eof())
	{
		nodeStudent* Student = new nodeStudent();
		Student->next = NULL;
		std::getline(fileStudent, temp, ',');
		if (temp == "")
		{
			delete Student;
			return;
		}
		std::getline(fileStudent, temp, ',');

		Student->student.info.idStudent = std::stoi(temp);
		std::getline(fileStudent, temp, ',');

		Student->student.info.lastName = temp;
		std::getline(fileStudent, temp, ',');

		Student->student.info.firstName = temp;
		std::getline(fileStudent, temp, ',');

		Student->student.info.gender = temp;
		std::getline(fileStudent, temp, '\n');

		addTailStudent(lst, Student);

	}

	fileStudent.close();
}
void deleteAStudentFromCourse(nodeCourse*& course, nodeStudent* deletion)
{
	string courseName = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className + ".txt";
	ifstream fileCourse(courseName);
	if (!fileCourse.is_open())
	{
		cout << "Cannot open file course\n";
		return;
	}
	listStudent lst = {};
	lst.head = NULL;
	readListStudentOfACourse(lst, courseName);

	nodeStudent* Head = lst.head;

	//Xóa khóa học trong file tất cả các bạn học sinh
	while (Head != NULL)
	{
		string Line, Temp;
		string studentFile = "./raw/" + to_string(Head->student.info.idStudent) + "_Course" + ".txt";
		std::ifstream fileStudent(studentFile);
		if (!fileStudent.is_open())
		{
			return;
		}
		while (std::getline(fileStudent, Line))
		{
			if (Line.find(course->crs.info.idCourse) != string::npos)
			{
				continue;
			}
			else
			{
				if (Temp.empty())
					Temp = Temp + Line;
				else
					Temp = Temp + "\n" + Line;
			}
		}
		fileStudent.close();
		ofstream fileStudent2(studentFile);
		fileStudent2 << Temp << "\n";
		fileStudent2.close();
		Head = Head->next;
	}


	deleteNodeStudent(lst, deletion);
	printStudent(lst);
	fileCourse.close();

	ofstream newFile;
	newFile.open(courseName);
	newFile << "No," << "Student ID," << "Student Last Name," << "Student First Name," << "Gender," << "Other Mark(Assignment)," << "Midterm Mark," << "Final Mark," << "Average Mark\n";
	nodeStudent* temp = lst.head;
	course->crs.info.numberOfCurrentStudent = 0;
	newFile.close();
	ifstream fileCourseToRead("./raw/Course.txt");

	string line, remember;
	while (std::getline(fileCourseToRead, line))
	{

		if (line.find(course->crs.info.idCourse.c_str()) != string::npos && line.find(course->crs.info.className.c_str()) != string::npos)
		{
			continue;
		}
		else
		{
			if (remember.empty())
				remember = remember + line;
			else
				remember = remember + "\n" + line;
		}
	}
	fileCourse.close();


	course->crs.info.numberOfCurrentStudent = 0;




	ofstream fileCourseToWrite("./raw/Course.txt");
	fileCourseToWrite << remember << "\n";
	fileCourseToWrite.close();
	writeACourseToFile(course, "./raw/Course.txt");//fileCourseToWrite.close();
	while (temp != NULL)
	{
		addAStudentToCourse(course, temp);
		temp = temp->next;
	}
	system("cls");


	printStudent(lst);
	system("Pause");

	deleteAllStudent(lst);

}
//---------------------------------------------------------------------

//--------------------------DELETE A COURSE-----------------------------
void deleteNodeCourse(listCourse& lst, nodeCourse* deletion)
{
	if (lst.head == NULL)
	{
		cout << "List is empty\n";
		return;
	}
	while (lst.head->crs.info.idCourse == deletion->crs.info.idCourse && lst.head->crs.info.className == deletion->crs.info.className)
	{
		nodeCourse* temp = lst.head;
		lst.head = lst.head->Next;
		delete temp;
		if (lst.head == NULL)
		{
			cout << "List is empty\n";
			return;
		}
	}
	nodeCourse* Prev = lst.head;
	nodeCourse* Curr = Prev->Next;
	while (Curr->Next != NULL)
	{
		if (Curr->crs.info.idCourse == deletion->crs.info.idCourse && deletion->crs.info.className == deletion->crs.info.className)
		{
			nodeCourse* temp = Curr;
			Curr = Curr->Next;
			Prev->Next = Curr;
			delete temp;
		}
		else
		{
			Prev = Curr;
			Curr = Curr->Next;
		}
	}
	if (Curr->crs.info.idCourse == deletion->crs.info.idCourse && deletion->crs.info.className == deletion->crs.info.className)
	{
		Prev->Next = NULL;
		delete Curr;
	}

}
void deleteACourse(listCourse& lst, nodeCourse* deletion)
{
	//Kí hiệu R là file để đọc
	//Kí hiệu W là file để ghi

	//Xóa dòng chứa khóa học này trong file Course.txt;
	ifstream fileCourseR("./raw/Course.txt");
	if (!fileCourseR.is_open())
	{
		return;
	}

	string line, remember;
	string idCourse = deletion->crs.info.idCourse;
	string nameClass = deletion->crs.info.className;

	while (std::getline(fileCourseR, line))
	{
		if (line.find(idCourse.c_str()) != string::npos && line.find(nameClass.c_str()) != string::npos)
		{
			continue;
		}
		else
		{
			if (remember.empty())
				remember = remember + line;
			else
				remember = remember + "\n" + line;
		}
	}
	fileCourseR.close();

	ofstream fileCourseW("./raw/Course.txt");
	if (!fileCourseW.is_open())
	{
		return;
	}
	fileCourseW << remember << "\n";
	fileCourseW.close();
	//Xóa toàn bộ học sinh 
	const string courseName = "./raw/" + deletion->crs.info.courseName + "_" + deletion->crs.info.className + ".txt";
	listStudent listS;
	readListStudentOfACourse(listS, courseName);
	nodeStudent* Temp = listS.head;
	while (Temp != NULL)
	{
		deleteAStudentFromCourse(deletion, Temp);
		Temp = Temp->next;
	}
	deleteNodeCourse(lst, deletion);
	cout << "The course has been removed\n";
	system("Pause");


}

//----------------------------------------------------------------------
void changePasswordForStaff(nodeStaff*& staff, const char fileName[])
{
	ifstream fileStudent(fileName);
	if (!fileStudent.is_open())
	{
		cout << "Cannot open file\n";
		return;
	}
	string line, pass;

	cout << "Input old password: ";
	std::getline(cin, pass);

	while (pass != staff->staff.account.passWord)
	{
		cout << "Password is not correct\n";
		cout << "Input old password: ";
		std::getline(cin, pass);
	}

	string remember;

	while (!fileStudent.eof())
	{
		std::getline(fileStudent, line);
		if (line.find(staff->staff.account.userName.c_str()) != std::string::npos && line.find(staff->staff.account.passWord.c_str()) != std::string::npos && line.find(to_string(staff->staff.IDofStaff).c_str()) != std::string::npos)
		{
			continue;
		}
		else
		{
			remember = remember + "\n" + line;
		}
	}

	cout << "Input new password: ";
	std::getline(cin, staff->staff.account.passWord);
	fileStudent.close();

	ofstream newFileStudent;
	newFileStudent.open(fileName);
	newFileStudent << remember << "\n";
	newFileStudent << staff->staff.account.userName << ",";
	newFileStudent << staff->staff.account.passWord << ",";
	newFileStudent << staff->staff.IDofStaff << ",";
	newFileStudent << staff->staff.lastName << ",";
	newFileStudent << staff->staff.firstName << ",";
	newFileStudent << staff->staff.gender << ",";
	newFileStudent << staff->staff.d.day << "/" << staff->staff.d.month << "/" << staff->staff.d.year << ",";
	newFileStudent << staff->staff.socialId << ",\n";
	newFileStudent.close();
}
//------------------------------------------------------------------------------------------------

//-----------------EXPORT .CSV FILE AND OPERATE WITH SCORE-------------------------
void exportCSVFile(const string address, nodeCourse* course)
{
	string addressFile = address;
	if (addressFile[0] == '"')
	{
		addressFile.erase(0, 1);
	}
	if (addressFile[addressFile.size() - 1] == '"')
	{
		addressFile.pop_back();
	}

	if (address.back() == '\\')
	{
		addressFile = addressFile + course->crs.info.courseName + "_" + course->crs.info.className + ".csv";
	}
	else
		addressFile = addressFile + "\\" + course->crs.info.courseName + "_" + course->crs.info.className + ".csv";
	cout << addressFile << endl;
	system("Pause");
	ofstream fileCSV(addressFile);
	if (!fileCSV.is_open())
	{
		cout << "Cannot write to file\n";
		return;
	}
	const string courseName = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className + ".txt";
	ifstream fileCourseR(courseName);
	string line;
	while (std::getline(fileCourseR, line))
	{
		fileCSV << line << "\n";
	}
	fileCSV.close();
	fileCourseR.close();
	cout << "Sucessfully exported!!. Press any key to continue\n";
	system("Pause");
}


//---------------------------------------------------------------------------------
void workSessionOfStaff(nodeStaff*& staff, listOfSchoolYear& lstSchoolYear, listCourse& lstCourse)
{
	system("cls");
	int optn;

	while (true)
	{
		system("cls");
		int Optn;
		cout << "Hello " << staff->staff.firstName << "\n";
		cout << "1. View Info\n";
		cout << "2. Change Password\n";
		cout << "3. Log out\n";
		cout << "4. School year\n";
		cout << "5. Semester\n";
		cout << "6. Create Class\n";
		cout << "7. Add course by .CSV\n";
		cout << "8. Adjust student in course\n";
		cout << "9. Delete a course\n";
		cout << "10. Export a course\n";
		cin >> Optn;
		cin.ignore();
		switch (Optn)
		{
		case 1:
		{
			viewInfoStaff(staff);
			break;
		}
		case 2:
		{
			changePasswordForStaff(staff, "accountStaff.txt");
			cout << "Your password has been changed\n";
			break;
		}
		case 3:
			return;
		case 7:
		{
			int i = 1;
			nodeCourse* temp = lstCourse.head;
			if (temp == NULL)
			{
				cout << "No course available\n";
				return;
			}
			while (temp != NULL)
			{
				if (temp == NULL)
				{
					break;
				}
				cout << i << ": " << temp->crs.info.courseName << " - " << temp->crs.info.className << endl;
				temp = temp->Next;
				i++;
			}
			temp = lstCourse.head;
			int maxChoice = i;
			i = 1;
			int optn;
			do {
				cout << "Please select a course: ";
				cin >> optn;
			} while (optn > maxChoice || optn <= 0);
			cin.ignore();
			while (optn != i)
			{
				temp = temp->Next;
				i++;
			}
			string fileName;
			std::getline(cin, fileName);
			addNStudentFromFile(temp, fileName);

			break;
		}
		case 8:
		{
			int i = 1;
			nodeCourse* temp = lstCourse.head;
			if (temp == NULL)
			{
				cout << "No course available\n";
				return;
			}
			while (temp != NULL)
			{
				cout << i << ": " << temp->crs.info.courseName << " - " << temp->crs.info.className << endl;
				temp = temp->Next;
				i++;
			}
			temp = lstCourse.head;
			int maxChoice = i;
			i = 1;
			int optn;
			do {
				cout << "Please select a course: ";
				cin >> optn;
			} while (optn > maxChoice || optn <= 0);
			cin.ignore();
			while (optn != i)
			{
				if (temp == NULL)
				{
					cout << "Invalid input\n";
					break;
				}
				temp = temp->Next;
				i++;
			}
			listStudent lst;
			lst.head = NULL;
			string fileName = "./raw/" + temp->crs.info.courseName + "_" + temp->crs.info.className + ".txt";
			readListStudentOfACourse(lst, fileName);
			printStudent(lst);
			if (lst.head != NULL)
			{
				//Chọn hcoj sinh muốn xóa
				int no;
				cout << "Input No of student you want to delete: ";
				cin >> no;
				cin.ignore();

				//Đi tới chỗ học sinh cần xóa.
				nodeStudent* deletion = new nodeStudent();
				deletion = goToStudent(no, lst);
				deleteAStudentFromCourse(temp, deletion);
			}
			else
			{
				cout << "List is empty\n";
			}

			//	printStudent(lst);
			break;
		}
		case 9:
		{
			int i = 1;
			nodeCourse* temp = lstCourse.head;
			if (temp == NULL)
			{
				cout << "No course available\n";
				return;
			}
			while (temp != NULL)
			{
				cout << i << ": " << temp->crs.info.courseName << " - " << temp->crs.info.className << endl;
				temp = temp->Next;
				i++;
			}
			temp = lstCourse.head;
			int maxChoice = i;
			i = 1;
			int optn;
			do {
				cout << "Please select a course: ";
				cin >> optn;
			} while (optn > maxChoice || optn <= 0);
			cin.ignore();
			while (optn != i)
			{
				temp = temp->Next;
				i++;
			}
			deleteACourse(lstCourse, temp);
			break;
		}
		case 10:
		{
			int i = 1;
			nodeCourse* temp = lstCourse.head;
			if (temp == NULL)
			{
				cout << "No course available\n";
				return;
			}
			while (temp != NULL)
			{
				cout << i << ": " << temp->crs.info.courseName << " - " << temp->crs.info.className << endl;
				temp = temp->Next;
				i++;
			}
			temp = lstCourse.head;
			int maxChoice = i;
			i = 1;
			int optn;
			do {
				cout << "Please select a course: ";
				cin >> optn;
			} while (optn > maxChoice || optn <= 0);
			cin.ignore();
			while (optn != i)
			{
				temp = temp->Next;
				i++;
			}
			string address;
			cout << "Input address of file: ";
			std::getline(cin, address);
			exportCSVFile(address, temp);
		}
		}
	}
}

bool checkPassword(User p)
{
	int doDai = p.passWord.length();
	if (doDai < 6)
		return 0;
	int coKiTuHoa = 0;
	for (int i = 0; i < doDai; i++) {
		if (p.passWord[i] >= 'A' && p.passWord[i] <= 'Z') {
			coKiTuHoa = 1;
		}
	}
	if (coKiTuHoa == 0)
		return 0;
	int coKiTu = 0;
	for (int i = 0; i < doDai; i++) {
		if (p.passWord[i] >= 'a' && p.passWord[i] <= 'z')
			coKiTu = 1;
		if (p.passWord[i] >= 'A' && p.passWord[i] <= 'Z')
			coKiTu = 1;
	}
	if (coKiTu == 0)
		return 0;

	int coSo = 0;
	for (int i = 0; i < doDai; i++) {
		if (p.passWord[i] >= '0' && p.passWord[i] <= '9')
			coSo = 1;
	}
	if (coSo == 0)
		return 0;

	int coDau = 0;
	for (int i = 0; i < doDai; i++) {
		if (p.passWord[i] == ',' || p.passWord[i] == '.' || p.passWord[i] == ':' || p.passWord[i] == '?' || p.passWord[i] == '~' || p.passWord[i] == '-' || p.passWord[i] == '_' || p.passWord[i] == ';' || p.passWord[i] == '@')
			coDau = 1;
	}
	if (coDau == 0)
		return 0;
	return 1;
}
bool KiemTraHoTen(string hoTen)
{
	int coKhoangTrang = 0;
	int doDai = hoTen.length();
	for (int i = 0; i < doDai; i++) {
		if (hoTen[i] == ' ') {
			coKhoangTrang = 1;
		}
	}
	if (coKhoangTrang == 0)
		return 0;
	return 1;
}
void XoaKhoangCach(string &name)
{
	string res="";
	int dodai = name.length();
	for (int i = 0; i < dodai; i++)
	{
		if (name[i] == ' ' && name[i + 1] == ' ')
		{
			continue;
		}
		else
		{
			res = res + name[i];
		}
	}
	int i = 0;
	if (res[0] == ' ');
	while (i < res.length())
	{
		res[i] = res[i + 1];
		i++;
	}
	if (res[res.length()-1] == ' ')
	{
		res[res.length()-1] = '\0';
	}
	name = res;
}
void ChuanHoaHoTen(string &name)
{
	XoaKhoangCach(name);
	int dem = 0;
	while (dem < name.length())
	{
		if (dem == 0) name[dem] = toupper(name[dem]);
		else if (name[dem - 1] == ' ') name[dem] = toupper(name[dem]);
		else
		{
			name[dem] = tolower(name[dem]);
		}
		dem++;
	}
}

void importScoreBoard(nodeCourse*& course, const string fileName)
{
	string fileScoreBoard = fileName;
	if (fileScoreBoard[0] == '"')
	{
		fileScoreBoard.erase(0, 1);
	}
	if (fileScoreBoard[fileScoreBoard.size() - 1] == '"')
	{
		fileScoreBoard.pop_back();
	}
	ifstream fileScoreR(fileScoreBoard);
	const string courseName = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className + ".txt";
	ofstream fileCourseW(courseName);
	if (!fileScoreR.is_open())
	{
		return;
	}
	if (!fileCourseW.is_open())
	{
		return;
	}
	string Line;
	string idCourse = course->crs.info.idCourse;
	string nameClass = course->crs.info.className;
	while (std::getline(fileScoreR, Line))
	{
		fileCourseW << Line << "\n";
	}
	fileCourseW.close();
	fileScoreR.close();
	fileScoreR.open(fileScoreBoard);
	std::getline(fileScoreR, Line);
	while (!fileScoreR.eof())
	{
		std::getline(fileScoreR, Line, ',');
		std::getline(fileScoreR, Line, ',');
		const string studentFile = "./raw/" + Line + "_Course" + ".txt";
		std::ifstream fileStudent(studentFile);
		if (!fileStudent.is_open())
		{
			cout << "OK" << endl;
			return;
		}

		std::getline(fileScoreR, Line, ',');
		std::getline(fileScoreR, Line, ',');
		std::getline(fileScoreR, Line, ',');
		std::getline(fileScoreR, Line, '\n');
		cout << Line << endl;
		system("Pause");
		string line, remember;
		string linetemp;
		//Xóa trạng thái khóa học hiện t
		bool flag = false;
		cout << idCourse << " - " << nameClass << endl;
		while (!fileStudent.eof())
		{
			flag = false;
			std::getline(fileStudent, line);
			cout << "Line: " << line << endl;
			if (line == "" || line == "\n")
			{
				flag = true;
				break;
			}
			if (line.find(idCourse.c_str()) != string::npos && line.find(nameClass.c_str()) != string::npos && !flag)
			{
				linetemp = line;
				cout << "Linetemp7777: " << linetemp << endl;
				//cout << line << endl;
				//cout << "OKOK" << endl;
			}
			else
			{
				if (remember.empty())
					remember = remember + line;
				else
					remember = remember + "\n" + line;
			}

		}
		{
			cout << "Linetemp: " << linetemp << endl;
			//cout << "OK3456" << endl;
			int i = 0;
			while (linetemp[i] != ',')
			{
				i++;
			}
			cout << "OK1" << endl;
			i++;
			while (linetemp[i] != ',')
			{
				i++;
			}
			cout << "OK2" << endl;
			i++;
			while (linetemp[i] != ',')
			{
				i++;
			}
			cout << "OK3" << endl;
			i++;
			while (linetemp[i] != ',')
			{
				i++;
			}
			cout << "OK4" << endl;
			i++;
			while (linetemp[i] != ',')
			{
				i++;
			}
			i++;
			while (linetemp[i] != ',')
			{
				i++;
			}
			i++;
			linetemp = linetemp.substr(0, i);
			linetemp += Line;
			linetemp += '\n';
			fileStudent.close();
			ofstream fileStudentW(studentFile);
			fileStudentW << remember << "\n";
			fileStudentW << linetemp;
			fileStudentW.close();
		}
	}
	fileScoreR.close();


	std::system("Pause");
}
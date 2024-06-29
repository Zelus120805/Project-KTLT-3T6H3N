#include "myLib.h"

//Nhóm hàm của Date
bool isLeapYear(int y)
{
	if ((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int getNumDaysInMonth(int m, int y)
{
	int d;
	if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
	{
		d = 31;
	}
	else if ((m == 4) || (m == 6) || (m == 9) || (m == 11))
	{
		d = 30;
	}
	else
	{
		if (isLeapYear(y))
		{
			d = 29;
		}
		else
		{
			d = 28;
		}
	}
	return d;
}

bool isValidDate(int d, int m, int y)
{
	if (m < 1 || m > 12)
		return false;
	if (d < 1 || d > getNumDaysInMonth(m, y))
		return false;

	return true;
}

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
	add->nextYear = NULL;
	add->y = addition;
	nodeSchoolYear* temp = lst.head;
	if (lst.head == NULL)
	{
		lst.head = add;
		return;
	}
	if (temp == NULL)
		return;
	while (temp->nextYear != NULL)
	{
		temp = temp->nextYear;
	}
	temp->nextYear = add;
}

void readSchoolYear(listOfSchoolYear& lst)
{
	std::ifstream myFile("SchoolYear.txt");
	if (!myFile.is_open())
	{
		return;
	}
	myFile.seekg(0, ios::beg);
	string temp;
	getline(myFile, temp, '-');
	if (temp == ""||temp=="\n")
	{
		return;
	}
	myFile.seekg(0, ios::beg);
	while (!myFile.eof())
	{
		getline(myFile, temp, '-');
		nodeSchoolYear* newNode = new nodeSchoolYear();
		newNode->nextYear = NULL;
		if (temp == "" || temp == "\n")
		{
			return;
		}
		newNode->y.startYear = std::stoi(temp);
		getline(myFile, temp);
		newNode->y.endYear = std::stoi(temp);
		addTailSchoolYear(lst, newNode->y);
	}
}

//void operateWithSchoolYear(listOfSchoolYear& lst)
//{
//	system("cls");
//	readSchoolYear(lst);
//	int section;
//	std::cout << "1. Create school year\n";
//	std::cout << "2. View and operate with school year\n";
//	std::cout << "3. Exit\n";
//	while (std::cin >> section)
//	{
//
//		if (section == 1)
//		{
//			createSchoolYear(lst);
//			system("cls");
//			std::cout << "1. Create school year\n";
//			std::cout << "2. View and operate with school year\n";
//			std::cout << "3. Exit\n";
//		}
//		if (section == 2)
//		{
//			//Thực thi năm học 
//			int i = 1;
//			nodeSchoolYear* temp = lst.head;
//			if (temp == NULL)
//			{
//				std::cout << "Please create at least 1 school year" << std::endl;
//				return;
//			}
//			while (temp != nullptr)
//			{
//				std::cout << i << ". " << temp->y.startYear << "-" << temp->y.endYear << "\n";
//				temp = temp->nextYear;
//				i++;
//			}
//			std::cout << "Select a school year\n";
//			std::cin >> i;
//			temp = lst.head;
//			nodeSchoolYear* selected = nullptr;
//			for (int j = 1; j < i; j++)
//			{
//				temp = temp->nextYear;
//			}
//			std::cout << "Create class for " << temp->y.startYear << "-" << temp->y.endYear << "\n";
//			createClass(temp->y.listOfClass);//Tạo một lớp của năm học đó
//
//			string fileName = to_string(temp->y.startYear) + "-" + to_string(temp->y.endYear) + ".txt";
//			char* tmp = new char[fileName.length() + 1];
//			fileName.copy(tmp, fileName.length());
//			tmp[fileName.length()] = '\0';
//			std::ofstream classOfSchoolYear(tmp, std::ios::app);
//
//			if (classOfSchoolYear.is_open() == false)
//			{
//				std::cout << "Cannot open file" << std::endl;
//				break;
//			}
//
//			nodeClass* Tmp = temp->y.listOfClass.head;
//			while (Tmp->next != nullptr)
//			{
//				Tmp = Tmp->next;
//			}
//			//Ghi lớp cuối cùng vừa thêm vào file năm học tương ứng
//			writeStudentToFileClass(Tmp->myClass, tmp);
//			system("cls");
//			std::cout << "1. Create school year\n";
//			std::cout << "2. View and operate with school year\n";
//			std::cout << "3. Exit\n";
//		}
//		if (section == 3)
//		{
//			system("cls");
//			return;
//		}
//	}
//}

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
		//std::cout << "Khong the tao file\n";
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
//void addAStudentToCourse(nodeCourse*& course, nodeStudent* student)
//{
//	string nameFile = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className + ".txt";
//	std::ofstream fileList(nameFile, std::ios_base::app);
//
//	string studentFile = "./raw/" + to_string(student->student.info.idStudent) + "_Course" + ".txt";
//	std::ofstream fileStudent(studentFile, std::ios_base::app);
//
//	if (!fileList.is_open() || !fileStudent.is_open())
//	{
//		std::cout << "Khong the mo file\n";
//		return;
//	}
//	course->crs.info.numberOfCurrentStudent++;
//	if (course->crs.info.numberOfCurrentStudent > course->crs.info.maxStudent)
//	{
//		std::cout << "The class has been full\n";
//		return;
//	}
//	//Ghi ra file riêng của học sinh đó
//	fileStudent << course->crs.info.idCourse << "," << course->crs.info.courseName << "," << course->crs.info.className << "," << course->crs.info.teacherName << "," << course->crs.info.numberOfCredits << "," << course->crs.info.dayOfWeek << ",0,0,0,0\n";
//	//Cập nhật danh sách lớp của khóa học đó.
//
//
//	fileList << course->crs.info.numberOfCurrentStudent << "," << student->student.info.idStudent << "," << student->student.info.lastName << "," << student->student.info.firstName << "," << student->student.info.gender << ",0,0,0,0\n";
//
//	std::ifstream fileCourse("./raw/Course.txt");
//	string temp, remember;
//
//	while (!fileCourse.eof())
//	{
//
//		getline(fileCourse, temp);
//		if (temp.find(course->crs.info.idCourse.c_str()) != std::string::npos && temp.find(course->crs.info.className.c_str()) != std::string::npos)
//		{
//			continue;
//		}
//		else
//		{
//			remember = remember + "\n" + temp;
//		}
//	}
//
//	fileCourse.close();
//	std::ofstream update("./raw/Course.txt");
//	update << course->crs.info.idCourse << "," << course->crs.info.courseName << "," << course->crs.info.className << "," << course->crs.info.teacherName << "," << course->crs.info.numberOfCredits << "," << course->crs.info.numberOfCurrentStudent << "," << course->crs.info.maxStudent << "," << course->crs.info.dayOfWeek;
//	update << remember;
//
//	update.close();
//}

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
void readCourseFile(listCourse& lst, const string fileName)
{
	std::ifstream fileCourse(fileName);
	if (!fileCourse.is_open())
		return;
	string temp;
	while (!fileCourse.eof())
	{
		Course newCourse;
		getline(fileCourse, temp, ',');
		newCourse.info.idCourse = temp;
		getline(fileCourse, temp, ',');
		newCourse.info.courseName = temp;
		getline(fileCourse, temp, ',');
		newCourse.info.className = temp;
		getline(fileCourse, temp, ',');
		newCourse.info.teacherName = temp;
		getline(fileCourse, temp, ',');
		if (temp == "" || temp == "\n")
			break;
		newCourse.info.numberOfCredits = stoi(temp);
		getline(fileCourse, temp, ',');
		newCourse.info.numberOfCurrentStudent = stoi(temp);
		getline(fileCourse, temp, ',');
		newCourse.info.maxStudent = stoi(temp);
		getline(fileCourse, temp, '\n');
		newCourse.info.dayOfWeek = temp;
		addTailCourse(lst, newCourse);
	}

	fileCourse.close();
}

void readCourseFileOfStudent(listCourse& lst, const string fileName) {
	std::ifstream fileCourse(fileName);
	if (!fileCourse.is_open()) {
		return;
	}

	while (!fileCourse.eof()) 
	{
		Course newCourse = { };

		getline(fileCourse, newCourse.info.idCourse, ',');
		if (fileCourse.eof()) 
			break;

		getline(fileCourse, newCourse.info.courseName, ',');

		getline(fileCourse, newCourse.info.className, ',');

		getline(fileCourse, newCourse.info.teacherName, ',');

		fileCourse >> newCourse.info.numberOfCredits;
		fileCourse.ignore();

		getline(fileCourse, newCourse.info.dayOfWeek, ',');

		fileCourse >> newCourse.info.score.otherMark;
		fileCourse.ignore();

		fileCourse >> newCourse.info.score.midtermMark;
		fileCourse.ignore();

		fileCourse >> newCourse.info.score.finalMark;
		fileCourse.ignore();

		fileCourse >> newCourse.info.score.totalMark;
		fileCourse.ignore();

		addTailCourse(lst, newCourse);
	}

	fileCourse.close();
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
//void readStudentFromCSV(listStudent& lst, const string fileName)
//{
//	ifstream fileStudent(fileName);
//	if (!fileStudent.is_open())
//	{
//		return;
//	}
//	//Đọc dòng đầu
//	string temp;
//	getline(fileStudent, temp);
//	lst.head = NULL;
//
//	while (!fileStudent.eof())
//	{
//		nodeStudent* Student = new nodeStudent();
//		Student->next = NULL;
//		getline(fileStudent, temp, ',');
//		if (temp == "")
//		{
//			delete Student;
//			return;
//		}
//		Student->student.info.idStudent = std::stoi(temp);
//		getline(fileStudent, temp, ',');
//
//		Student->student.info.lastName = temp;
//		getline(fileStudent, temp, ',');
//
//		Student->student.info.firstName = temp;
//		getline(fileStudent, temp, ',');
//
//		Student->student.info.gender = temp;
//		getline(fileStudent, temp, '/');
//
//		Student->student.info.d.day = std::stoi(temp);
//		getline(fileStudent, temp, '/');
//		Student->student.info.d.month = std::stoi(temp);
//		getline(fileStudent, temp, ',');
//		Student->student.info.d.year = std::stoi(temp);
//		getline(fileStudent, temp, ',');
//
//		Student->student.info.socialId = temp;
//		getline(fileStudent, temp, '\n');
//
//		Student->student.info.inClass = temp;
//		addTailStudent(lst, Student);
//
//	}
//
//	fileStudent.close();
//}

//Thêm n sinh viên vào khóa học từ file CSV
//void addNStudentFromFile(nodeCourse*& course, const string fileName)
//{
//	ifstream fileStudent(fileName);
//	if (!fileStudent.is_open())
//	{
//		std::cout << "Khong the doc file" << endl;
//		return;
//	}
//	//Đọc từng sinh viên
//	listStudent lst = { };
//	lst.head = NULL;
//	readStudentFromCSV(lst, fileName);
//	//readFileStudent(lst, fileName.c_str());
//
//	string courseName = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className + ".txt";
//	ofstream fileCourse(courseName, ios_base::app);
//	nodeStudent* temp = lst.head;
//	while (temp != NULL)
//	{
//		addAStudentToCourse(course, temp);
//		temp = temp->next;
//	}
//	std::cout << "Da them thanh cong\n";
//	fileStudent.close();
//}

//---------------------------------------------------------------------------

//Nhóm hàm thao tác tài khoản của sinh viên ------------------------------------------------------
void studentRegister(listStudent& lst, const char fileName[], int x, int y)
{
	ShowCur(1);
	nodeStudent* Student = new nodeStudent();
	Student->next = nullptr;

	gotoXY(x + 2, y + 2); cout << "Username: "; drawBox(x + 2 + strlen("Username: "), y + 1, 65 - strlen("Username: "), 2);
	gotoXY(x + 2, y + 5); cout << "Password: "; drawBox(x + 2 + strlen("Username: "), y + 4, 65 - strlen("Password: "), 2);
	gotoXY(x + 2, y + 8); cout << "Fullname: "; drawBox(x + 2 + strlen("Username: "), y + 7, 65 - strlen("Fullname: "), 2);
	gotoXY(x + 2, y + 11); cout << "Date of birth(dd mm yyyy): "; drawBox(x + 2 + strlen("Date of birth(dd mm yyyy): "), y + 10, 65 - strlen("Date of birth(dd mm yyyy): "), 2);
	gotoXY(x + 2, y + 14); cout << "Gender(Male/Female): "; drawBox(x + 2 + strlen("Gender(Male/Female): "), y + 13, 8, 2);
	gotoXY(x + 35, y + 14); cout << "ID student: "; drawBox(x + 35 + strlen("ID student: "), y + 13, 20, 2);
	gotoXY(x + 2, y + 17); cout << "Social ID: "; drawBox(x + 2 + strlen("Social ID: "), y + 16, 18, 2);
	gotoXY(x + 35, y + 17); cout << "Class: "; drawBox(x + 35 + (int)strlen("Class: "), y + 16, 25, 2);

	char ch;
	int i = 0, curPos[8] = { 0 };
	std::string input[8];

	int newX[8] = { x + 2 + strlen("Username: ") + 1,
					x + 2 + strlen("Password: ") + 1,
					x + 2 + strlen("Fullname: ") + 1,
					x + 2 + strlen("Date of birth(dd mm yyyy): ") + 1,
					x + 2 + strlen("Gender(Male/Female): ") + 1,
					x + 35 + strlen("ID student: ") + 1,
					x + 2 + strlen("Social ID: ") + 1,
					x + 35 + strlen("Class: ") + 1 };
	int newY[8] = { y + 2, y + 5, y + 8, y + 11, y + 14, y + 14, y + 17, y + 17 };
	int oldX = newX[0], oldY = newY[0];
	std::string prev = " ";

	gotoXY(oldX, oldY);
	while (true) {
		ch = _getch();

		if (ch == 27)
		{
			ShowCur(0);
			deleteTextAtXY(x - 15, y + 17, prev);
			printTextAtXY(x - 15, y + 17, "Exit register !!!");
			return;
		}
		else if (ch == '\r')
		{
			if (input[0].length() == 0)
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Data isn't full !!!");
				ShowCur(1);
				prev = "Data isn't full !!!";
				i = 0;
			}
			else if (isStudentExisted(lstStudent, input[0]))
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Username is existed !!!");
				ShowCur(1);
				prev = "Username is existed !!!";
				i = 0;
			}
			else if (!checkPassword(input[1]))
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Invalid password entered !!!");
				ShowCur(1);
				prev = "Invalid fullname entered !!!";
				i = 1;
			}
			else if (input[2].length() == 0 || !KiemTraHoTen(input[2]))
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Invalid fullname entered !!!");
				ShowCur(1);
				prev = "Invalid password entered !!!";
				i = 2;
			}
			else if (!isValidRegisterDate(input[3]))
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Invalid date entered !!!");
				ShowCur(1);
				prev = "Invalid date entered !!!";
				i = 3;
			}
			else if (input[4].length() == 0)
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Data isn't full !!!");
				ShowCur(1);
				prev = "Data isn't full !!!";
				i = 4;
			}
			else if (input[5].length() == 0)
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Data isn't full !!!");
				ShowCur(1);
				prev = "Data isn't full !!!";
				i = 5;
			}
			else if (input[6].length() == 0)
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Data isn't full !!!");
				ShowCur(1);
				prev = "Data isn't full !!!";
				i = 6;
			}
			else if (input[7].length() == 0)
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Data isn't full !!!");
				ShowCur(1);
				prev = "Data isn't full !!!";
				i = 7;
			}
			else
			{
				ShowCur(0);
				break;
			}

			curPos[i] = input[i].length();
			oldX = newX[i] + input[i].length();
			oldY = newY[i];
			gotoXY(oldX, oldY);
		}
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && i > 0) {
				i--;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 80 && i < 7) {
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 75 && curPos[i] > 0) {
				curPos[i]--;
				gotoXY(--oldX, oldY);
			}
			else if (ch == 77 && curPos[i] < input[i].length()) {
				curPos[i]++;
				gotoXY(++oldX, oldY);
			}
		}
		else if (ch == 9)
		{
			if (i < 7)
			{
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
		}
		else if (ch == '\b' && curPos[i] > 0)
		{
			curPos[i]--;
			input[i].erase(curPos[i], 1);
			gotoXY(newX[i], oldY);
			std::cout << input[i] << " ";
			gotoXY(--oldX, oldY);
		}
		else if (ch != '\b')
		{
			input[i].insert(curPos[i], 1, ch);
			curPos[i]++;
			std::cout << input[i].substr(curPos[i] - 1);
			gotoXY(++oldX, oldY);
		}
	}

	Student->student.account.userName = input[0];
	Student->student.account.passWord = input[1];
	ChuanHoaHoTen(input[2]);
	size_t index = input[2].find(' ');
	Student->student.info.lastName = input[2].substr(0, index);
	Student->student.info.firstName = input[2].substr(index + 1);
	size_t index1 = input[3].find(' ');
	size_t index2 = input[3].find(' ', index1 + 1);
	Student->student.info.d.day = stoi(input[3].substr(0, index1));
	Student->student.info.d.month = stoi(input[3].substr(index1 + 1, index2));
	Student->student.info.d.year = stoi(input[3].substr(index2 + 1));
	Student->student.info.gender = input[4];
	Student->student.info.idStudent = stol(input[5]);
	Student->student.info.socialId = input[6];
	Student->student.info.inClass = input[7];

	printTextAtXY(x - 15, y + 17, "Register succesful!");

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

	accountStudent.close();
}

void studentLogIn(listStudent& lst, listCourse list, int x, int y)
{
	ShowCur(1);
	gotoXY(x + strlen("Username: ") + 1, y);
	gotoXY(x + strlen("Password: ") + 1, y + 3);

	char ch;
	int i = 0, curPos[2] = { 0 };
	std::string input[2];

	int newX[2] = { x + strlen("Username: ") + 1,
					x + strlen("Password: ") + 1 };
	int newY[2] = { y, y + 3 };
	int oldX = newX[0], oldY = newY[0];
	std::string prev = "Username or password is not correct !!!";

	gotoXY(oldX, oldY);
	while (true) {
		ch = _getch();

		if (ch == 27)
		{
			deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, prev);
			ShowCur(0);
			printTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, "Exit login !!!");
			return;
		}
		else if (ch == '\r')
		{
			if (input[0].length() != 0 && input[1].length() != 0)
			{
				nodeStudent* temp = new nodeStudent();
				temp = lst.head;
				while (temp != NULL)
				{
					if (temp->student.account.userName == input[0] && temp->student.account.passWord == input[1])
					{
						deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, prev);
						printTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, "login succesful !!!");
						ShowCur(0);
						workSessionOfStudent(temp, list);
						return;
					}
					temp = temp->next;
				}
			}
			if (input[0].length() == 0)
				i = 0;
			else
				i = 1;
			deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, prev);
			ShowCur(0);
			printTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, prev);
			ShowCur(1);

			curPos[i] = input[i].length();
			oldX = newX[i] + input[i].length();
			oldY = newY[i];
			gotoXY(oldX, oldY);
		}
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && i > 0) {
				i--;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 80 && i < 1) {
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 75 && curPos[i] > 0) {
				curPos[i]--;
				gotoXY(--oldX, oldY);
			}
			else if (ch == 77 && curPos[i] < input[i].length()) {
				curPos[i]++;
				gotoXY(++oldX, oldY);
			}
		}
		else if (ch == 9)
		{
			if (i < 1)
			{
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
		}
		else if (ch == '\b' && curPos[i] > 0)
		{
			curPos[i]--;
			input[i].erase(curPos[i], 1);
			gotoXY(newX[i], oldY);
			if (i == 0)
				std::cout << input[i] << " ";
			else if (i == 1)
			{
				for (int j = 1; j <= input[i].length(); j++)
					cout << "*";
				cout << " ";
			}
			gotoXY(--oldX, oldY);
		}
		else if (ch != '\b')
		{
			input[i].insert(curPos[i], 1, ch);
			curPos[i]++;
			if (i == 0)
				std::cout << input[i].substr(curPos[i] - 1);
			else if (i == 1)
				std::cout << "*";
			gotoXY(++oldX, oldY);
		}
	}
}

void workSessionOfStudent(nodeStudent*& node, listCourse list)
{
	int x = WIDTH_CONSOLE / 2 - 30, y = HEIGHT_CONSOLE / 2 - 7;
	int newX = x + 15, newY = y + 2;
	int oldX = newX, oldY = newY;
	int newWidth = 30, newHeight = 2;
	int nBox = 4, dis = 2;

	int count = 0;
	bool check = true;
	while (true)
	{
		if (count == 0)
		{
			system("cls");
			setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
			setBackgroundColor(lwhite);
			std::string str = node->student.info.lastName + " " + node->student.info.firstName;
			setTextColor(blue); gotoXY(1, 0); cout << "Username: " << node->student.account.userName;
			gotoXY(1, 1); cout << "Fullname: " << str;
			setTextColor(lgreen); print("Picture\\Hello Student.txt", WIDTH_CONSOLE / 2 - 29, 1);
			setTextColor(green); printTwoLine(x, y, 18, 60);
			setTextColor(black);

			string* option = new string[nBox];
			option[0] = "Change password";
			option[1] = "View info";
			option[2] = "View student";
			option[3] = "Log out";
			drawNBoxByY(x + 15, y + 2, newWidth, newHeight, nBox, dis, option);
			delete[] option;

			count++;
		}
		if (check == true)
		{
			gotoXY(oldX, oldY);
			focus(oldX, oldY, newWidth, ' ');
			oldX = newX, oldY = newY;

			focus(newX, newY, newWidth, (char)174);
			check = false;
		}
		if (_kbhit())
		{
			char choose = _getch();
			if (choose == 13)
			{
				if (newY == y + 2)
				{
					changePasswordForStudent(node, "accountStudent.txt");
					count = 0;
				}
				else if (newY == y + 2 + newHeight + dis)
				{
					viewInfoStudent(node);
					count = 0;
				}
				else if (newY == y + 2 + 2 * (newHeight + dis))
				{
					menuViewOfStudent(node);
					count = 0;
				}
				else if (newY == y + 2 + 3 * (newHeight + dis))
				{
					setTextColor(yellow); 
					printTextAtXY(WIDTH_CONSOLE / 2, newY + 3, "Goodbye student !!!");
					return;
				}
			}
			else if (choose == -32)
			{
				choose = _getch();
				if (choose == 72 && newY > y + 2)
					newY = newY - newHeight - dis;
				else if (choose == 80 && newY < y + (nBox - 1) * (newHeight + dis))
					newY = newY + newHeight + dis;
			}

			check = true;
		}
	}
}

void viewInfoStudent(nodeStudent* Student)
{
	system("cls");
	setBackgroundColor(lyellow); setTextColor(red);
	std::string str = "       Press any key to return       "; gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, HEIGHT_CONSOLE - 4); cout << str;
	setBackgroundColor(lwhite); setTextColor(purple); print("Picture\\Your Information.txt", WIDTH_CONSOLE / 2 - 50, 2);
	int x = WIDTH_CONSOLE / 2 - 30, y = HEIGHT_CONSOLE / 2 - 7, height = 14, width = 60;
	setTextColor(green); printTwoLine(x, y, height, width);
	
	setBackgroundColor(lyellow); setTextColor(aqua); printTextAtXY(WIDTH_CONSOLE / 2, y + 2, "Infomation of student");
	setBackgroundColor(lwhite);
	setTextColor(black); gotoXY(x + 3, y + 4); std::cout << "- Username: "; setTextColor(blue); cout << Student->student.account.userName;
	setTextColor(black); gotoXY(x + 3, y + 5); std::cout << "- Password: "; setTextColor(blue); cout << Student->student.account.passWord;
	setTextColor(black); gotoXY(x + 3, y + 6); std::cout << "- ID student: "; setTextColor(blue); cout << Student->student.info.idStudent;
	setTextColor(black); gotoXY(x + 3, y + 7); std::cout << "- Last name: "; setTextColor(blue); cout << Student->student.info.lastName;
	setTextColor(black); gotoXY(x + 3, y + 8); std::cout << "- First name: "; setTextColor(blue); cout << Student->student.info.firstName;
	setTextColor(black); gotoXY(x + 3, y + 9); std::cout << "- Gender: "; setTextColor(blue); cout << Student->student.info.gender;
	setTextColor(black); gotoXY(x + 3, y + 10); std::cout << "- Date of birth: "; setTextColor(blue); cout << Student->student.info.d.day << "/" << Student->student.info.d.month << "/" << Student->student.info.d.year;
	setTextColor(black); gotoXY(x + 3, y + 11); std::cout << "- Social ID: "; setTextColor(blue); cout << Student->student.info.socialId ;
	setTextColor(black); gotoXY(x + 3, y + 12); std::cout << "- Class: "; setTextColor(blue); cout << Student->student.info.inClass;

	while (true)
	{
		if (_kbhit)
		{
			char ch = _getch();
			return;
		}
	}
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
	int x = 0, y = 0;
	menuChangePassword(x, y);

	int i = 0, curPos[3] = { 0 };
	int newX[3] = { x + strlen("Input old password: ") + 1,
					x + strlen("Input new password: ") + 1,
					x + strlen("Confirm new password: ") + 1};
	int newY[3] = { y, y + 3, y + 6 };
	int oldX = newX[0], oldY = newY[0];

	std::string input[3], remember, prev = " ";

	gotoXY(oldX, oldY);
	while (true) {
		ShowCur(1);
		char ch = _getch();

		if (ch == 27)
		{
			ShowCur(0);
			deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
			printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Exit change password !!!");
			return;
		}
		else if (ch == '\r')
		{
			if (student->student.account.passWord == input[0] && input[1] == input[2] && checkPassword(input[1]))
			{
				ifstream fileStudent(fileName);
				if (!fileStudent.is_open())
					return;

				string line;
				while (!fileStudent.eof())
				{
					std::getline(fileStudent, line);
					if (line == "" || line == "\n")
						break;

					if (line.find(student->student.account.userName.c_str()) != std::string::npos && line.find(student->student.account.passWord.c_str()) != std::string::npos)
					{
						continue;
					}
					else
					{
						if (remember.length() == 0)
							remember = line;
						else
							remember = remember + "\n" + line;
					}
				}
				student->student.account.passWord = input[1];
				fileStudent.close();

				ShowCur(0);
				deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
				printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Change password succesfull !!!");

				break;
			}
			else if (student->student.account.passWord != input[0])
			{
				i = 0;
				ShowCur(0);
				deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
				printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Old password is invalid !!!");
				prev = "Old password is invalid !!!";
			}
			else if (!checkPassword(input[1]))
			{
				i = 1;
				ShowCur(0);
				deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
				printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Invalid new password entered !!!");
				prev = "Invalid new password entered !!!";
			}
			else if (input[1] != input[2])
			{
				i = 2;
				ShowCur(0);
				deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
				printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Confirm new password is invalid !!!");
				prev = "Confirm new password is invalid !!!";
			}

			curPos[i] = input[i].length();
			oldX = newX[i] + input[i].length();
			oldY = newY[i];
			gotoXY(oldX, oldY);
		}
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && i > 0) {
				i--;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 80 && i < 7) {
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 75 && curPos[i] > 0) {
				curPos[i]--;
				gotoXY(--oldX, oldY);
			}
			else if (ch == 77 && curPos[i] < input[i].length()) {
				curPos[i]++;
				gotoXY(++oldX, oldY);
			}
		}
		else if (ch == 9)
		{
			if (i < 2)
			{
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
		}
		else if (ch == '\b' && curPos[i] > 0)
		{
			curPos[i]--;
			input[i].erase(curPos[i], 1);
			gotoXY(newX[i], oldY);
			std::cout << input[i] << " ";
			gotoXY(--oldX, oldY);
		}
		else if (ch != '\b')
		{
			input[i].insert(curPos[i], 1, ch);
			curPos[i]++;
			std::cout << input[i].substr(curPos[i] - 1);
			gotoXY(++oldX, oldY);
		}
	}

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
	gotoXY(x + 2, y + 5); cout << "Password: "; drawBox(x + 2 + strlen("Password: "), y + 4, 65 - strlen("Password: "), 2);
	gotoXY(x + 2, y + 8); cout << "Fullname: "; drawBox(x + 2 + strlen("Fullname: "), y + 7, 65 - strlen("Fullname: "), 2);
	gotoXY(x + 2, y + 11); cout << "Date Of Birth(dd mm yyyy): "; drawBox(x + 2 + strlen("Date of birth(dd mm yyyy): "), y + 10, 65 - strlen("Date of birth(dd mm yyyy): "), 2);
	gotoXY(x + 2, y + 14); cout << "Gender(Male/Female): "; drawBox(x + 2 + strlen("Gender(Male/Female): "), y + 13, 8, 2);
	gotoXY(x + 35, y + 14); cout << "ID Staff: "; drawBox(x + 35 + strlen("ID Staff: "), y + 13, 22, 2);
	gotoXY(x + 2, y + 17); cout << "Social ID: "; drawBox(x + 2 + strlen("Social ID: "), y + 16, 18, 2);

	char ch;
	int i = 0, curPos[7] = { 0 };
	std::string input[7];

	int newX[7] = { x + 2 + strlen("Username: ") + 1,
					x + 2 + strlen("Password: ") + 1,
					x + 2 + strlen("Fullname: ") + 1,
					x + 2 + strlen("Date of birth(dd mm yyyy): ") + 1,
					x + 2 + strlen("Gender(Male/Female): ") + 1,
					x + 35 + strlen("ID Staff: ") + 1,
					x + 2 + strlen("Social ID: ") + 1 };
	int newY[7] = { y + 2, y + 5, y + 8, y + 11, y + 14, y + 14, y + 17 };
	int oldX = newX[0], oldY = newY[0];
	std::string prev = " ";

	gotoXY(oldX, oldY);
	while (true) {
		ch = _getch();

		if (ch == 27)
		{
			ShowCur(0);
			deleteTextAtXY(x - 15, y + 17, prev);
			printTextAtXY(x - 15, y + 17, "Exit register !!!");
			return;
		}
		else if (ch == '\r')
		{
			if (input[0].length() == 0)
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Data isn't full !!!");
				ShowCur(1);
				prev = "Data isn't full !!!";
				i = 0;
			}
			else if (isStaffExisted(lstStaff, input[0]))
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Username is existed !!!");
				ShowCur(1);
				prev = "Username is existed !!!";
				i = 0;
			}
			else if (!checkPassword(input[1]))
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Invalid password entered !!!");
				ShowCur(1);
				prev = "Invalid password entered !!!";
				i = 1;
			}
			else if (input[2].length() == 0 || !KiemTraHoTen(input[2]))
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Invalid fullname entered !!!");
				ShowCur(1);
				prev = "Invalid fullname entered !!!";
				i = 2;
			}
			else if (!isValidRegisterDate(input[3]))
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Invalid date entered !!!");
				ShowCur(1);
				prev = "Invalid date entered !!!";
				i = 3;
			}
			else if (input[4].length() == 0)
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Data isn't full !!!");
				ShowCur(1);
				prev = "Data isn't full !!!";
				i = 4;
			}
			else if (input[5].length() == 0)
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Data isn't full !!!");
				ShowCur(1);
				prev = "Data isn't full !!!";
				i = 5;
			}
			else if (input[6].length() == 0)
			{
				deleteTextAtXY(x - 15, y + 17, prev);
				ShowCur(0);
				printTextAtXY(x - 15, y + 17, "Data isn't full !!!");
				ShowCur(1);
				prev = "Data isn't full !!!";
				i = 6;
			}
			else
			{
				ShowCur(0);
				break;
			}

			curPos[i] = input[i].length();
			oldX = newX[i] + input[i].length();
			oldY = newY[i];
			gotoXY(oldX, oldY);
		}
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && i > 0) {
				i--;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 80 && i < 6) {
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 75 && curPos[i] > 0) {
				curPos[i]--;
				gotoXY(--oldX, oldY);
			}
			else if (ch == 77 && curPos[i] < input[i].length()) {
				curPos[i]++;
				gotoXY(++oldX, oldY);
			}
		}
		else if (ch == 9)
		{
			if (i < 6)
			{
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
		}
		else if (ch == '\b' && curPos[i] > 0)
		{
			curPos[i]--;
			input[i].erase(curPos[i], 1);
			gotoXY(newX[i], oldY);
			std::cout << input[i] << " ";
			gotoXY(--oldX, oldY);
		}
		else if (ch != '\b')
		{
			input[i].insert(curPos[i], 1, ch);
			curPos[i]++;
			std::cout << input[i].substr(curPos[i] - 1);
			gotoXY(++oldX, oldY);
		}
	}

	Staff->staff.account.userName = input[0];
	Staff->staff.account.passWord = input[1];
	ChuanHoaHoTen(input[2]);
	size_t index = input[2].find(' ');
	Staff->staff.lastName = input[2].substr(0, index);
	Staff->staff.firstName = input[2].substr(index + 1);
	size_t index1 = input[3].find(' ');
	size_t index2 = input[3].find(' ', index1 + 1);
	Staff->staff.d.day = stoi(input[3].substr(0, index1));
	Staff->staff.d.month = stoi(input[3].substr(index1 + 1, index2));
	Staff->staff.d.year = stoi(input[3].substr(index2 + 1));
	Staff->staff.gender = input[4];
	Staff->staff.IDofStaff = stol(input[5]);
	Staff->staff.socialId = input[6];

	printTextAtXY(x - 15, y + 17, "Register succesful!");

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
	accountStaff << Staff->staff.IDofStaff << ",";
	accountStaff << Staff->staff.socialId << endl;
}

//Đọc file staff
void readFileStaff(listStaff& lst, const char fileName[])
{
	ifstream fileStaff(fileName);
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
		getline(fileStaff, temp);
		Staff.socialId = temp;
		addTailStaff(lst, Staff);
	}
	fileStaff.close();
}
//Xem thông tin staff
void viewInfoStaff(nodeStaff* staff)
{
	system("cls");
	setBackgroundColor(lyellow); setTextColor(red);
	std::string str = "       Press any key to return       "; gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, HEIGHT_CONSOLE - 4); cout << str;
	setBackgroundColor(lwhite); setTextColor(purple); print("Picture\\Your Information.txt", WIDTH_CONSOLE / 2 - 50, 2);
	int x = WIDTH_CONSOLE / 2 - 30, y = HEIGHT_CONSOLE / 2 - 6, height = 13, width = 60;
	setTextColor(green); printTwoLine(x, y, height, width);

	setBackgroundColor(lyellow); setTextColor(aqua); printTextAtXY(WIDTH_CONSOLE / 2, y + 2, "Infomation of staff");
	setBackgroundColor(lwhite);
	setTextColor(black); gotoXY(x + 3, y + 4); std::cout << "- Username: "; setTextColor(blue); cout << staff->staff.account.userName;
	setTextColor(black); gotoXY(x + 3, y + 5); std::cout << "- Password: "; setTextColor(blue); cout << staff->staff.account.passWord;
	setTextColor(black); gotoXY(x + 3, y + 6); std::cout << "- ID student: "; setTextColor(blue); cout << staff->staff.IDofStaff;
	setTextColor(black); gotoXY(x + 3, y + 7); std::cout << "- Last name: "; setTextColor(blue); cout << staff->staff.lastName;
	setTextColor(black); gotoXY(x + 3, y + 8); std::cout << "- First name: "; setTextColor(blue); cout << staff->staff.firstName;
	setTextColor(black); gotoXY(x + 3, y + 9); std::cout << "- Gender: "; setTextColor(blue); cout << staff->staff.gender;
	setTextColor(black); gotoXY(x + 3, y + 10); std::cout << "- Date of birth: "; setTextColor(blue); cout << staff->staff.d.day << "/" << staff->staff.d.month << "/" << staff->staff.d.year;
	setTextColor(black); gotoXY(x + 3, y + 11); std::cout << "- Social ID: "; setTextColor(blue); cout << staff->staff.socialId;

	while (true)
	{
		if (_kbhit)
		{
			char ch = _getch();
			return;
		}
	}
}

//Đăng nhập staff
void staffLogIn(listStaff& staff, listOfSchoolYear& lstSchoolYear, listCourse& lstCourse, int x, int y)
{
	ShowCur(1);
	gotoXY(x + strlen("Username: ") + 1, y);
	gotoXY(x + strlen("Password: ") + 1, y + 3);

	char ch;
	int i = 0, curPos[2] = { 0 };
	std::string input[2];

	int newX[2] = { x + strlen("Username: ") + 1,
					x + strlen("Password: ") + 1 };
	int newY[2] = { y, y + 3 };
	int oldX = newX[0], oldY = newY[0];
	std::string prev = "Username or password is not correct !!!";

	gotoXY(oldX, oldY);
	while (true) {
		ch = _getch();

		if (ch == 27)
		{
			ShowCur(0);
			deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, prev);
			printTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, "Exit login !!!");
			return;
		}
		else if (ch == '\r')
		{
			if (input[0].length() != 0 && input[2].length() != 0)
			{
				nodeStaff* temp = new nodeStaff();
				temp = staff.head;
				while (temp != NULL)
				{
					if (temp->staff.account.userName == input[0] && temp->staff.account.passWord == input[1])
					{
						deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, prev);
						ShowCur(0);
						printTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, "login succesful !!!");
						workSessionOfStaff(temp, lstSchoolYear, lstCourse);
						return;
					}
					temp = temp->next;
				}
			}
			if (input[0].length() == 0)
				i = 0;
			else
				i = 1;
			deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, prev);
			ShowCur(0);
			printTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, prev);
			ShowCur(1);

			curPos[i] = input[i].length();
			oldX = newX[i] + input[i].length();
			oldY = newY[i];
			gotoXY(oldX, oldY);
		}
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && i > 0) {
				i--;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 80 && i < 1) {
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 75 && curPos[i] > 0) {
				curPos[i]--;
				gotoXY(--oldX, oldY);
			}
			else if (ch == 77 && curPos[i] < input[i].length()) {
				curPos[i]++;
				gotoXY(++oldX, oldY);
			}
		}
		else if (ch == 9)
		{
			if (i < 1)
			{
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
		}
		else if (ch == '\b' && curPos[i] > 0)
		{
			curPos[i]--;
			input[i].erase(curPos[i], 1);
			gotoXY(newX[i], oldY);
			if (i == 0)
				std::cout << input[i] << " ";
			else if (i == 1)
			{
				for (int j = 1; j <= input[i].length(); j++)
					cout << "*";
				cout << " ";
			}
			gotoXY(--oldX, oldY);
		}
		else if (ch != '\b')
		{
			input[i].insert(curPos[i], 1, ch);
			curPos[i]++;
			if (i == 0)
				std::cout << input[i].substr(curPos[i] - 1);
			else if (i == 1)
				std::cout << "*";
			gotoXY(++oldX, oldY);
		}
	}
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

//Nhóm hàm giải phóng bộ nhớ ---------------------------------------
//Xóa sạch sinh viên
void deleteAllStudent(listStudent& lst)
{
	if (lst.head == NULL)
		return;
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
		return;
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
		return;
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
		return;
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
void printStudent(listStudent lst, int start, int end, int x, int y)
{
	if (end == 0)
	{
		setTextColor(red);
		gotoXY(HEIGHT_CONSOLE / 2, y + 3); cout << "No data of student in this course !!!";
		return;
	}

	setTextColor(black);
	int index = 0, i = 1;
	nodeStudent* temp = lst.head;
	while (temp != NULL)
	{
		if (i == start)
			break;
		i++;
		temp = temp->next;
	}

	while (temp != NULL)
	{
		if (i == end + 1)
			break;
		gotoXY(x + 1, y + 3 + index); cout << i;
		gotoXY(x + 5, y + 3 + index); cout << temp->student.info.idStudent;
		gotoXY(x + 20, y + 3 + index); cout << temp->student.info.lastName;
		gotoXY(x + 45, y + 3 + index); cout << temp->student.info.firstName;

		temp = temp->next;
		index++; i++;
	}
}

nodeStudent* goToStudent(int No, listStudent lst)
{
	if (lst.head == NULL)
	{
		//cout << "List is empty\n";
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

//void deleteAStudentFromCourse(nodeCourse*& course, nodeStudent* deletion)
//{
//	string courseName = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className + ".txt";
//	ifstream fileCourse(courseName);
//	if (!fileCourse.is_open())
//	{
//		cout << "Cannot open file course\n";
//		return;
//	}
//	listStudent lst = {};
//	lst.head = NULL;
//	readListStudentOfACourse(lst, courseName);
//
//	nodeStudent* Head = lst.head;
//
//	//Xóa khóa học trong file tất cả các bạn học sinh
//	while (Head != NULL)
//	{
//		string Line, Temp;
//		string studentFile = "./raw/" + to_string(Head->student.info.idStudent) + "_Course" + ".txt";
//		std::ifstream fileStudent(studentFile);
//		if (!fileStudent.is_open())
//		{
//			return;
//		}
//		while (std::getline(fileStudent, Line))
//		{
//			if (Line.find(course->crs.info.idCourse) != string::npos)
//			{
//				continue;
//			}
//			else
//			{
//				if (Temp.empty())
//					Temp = Temp + Line;
//				else
//					Temp = Temp + "\n" + Line;
//			}
//		}
//		fileStudent.close();
//		ofstream fileStudent2(studentFile);
//		fileStudent2 << Temp << "\n";
//		fileStudent2.close();
//		Head = Head->next;
//	}
//
//
//	deleteNodeStudent(lst, deletion);
//	printStudent(lst);
//	fileCourse.close();
//
//	ofstream newFile;
//	newFile.open(courseName);
//	newFile << "No," << "Student ID," << "Student Last Name," << "Student First Name," << "Gender," << "Other Mark(Assignment)," << "Midterm Mark," << "Final Mark," << "Average Mark\n";
//	nodeStudent* temp = lst.head;
//	course->crs.info.numberOfCurrentStudent = 0;
//	newFile.close();
//	ifstream fileCourseToRead("./raw/Course.txt");
//
//	string line, remember;
//	while (std::getline(fileCourseToRead, line))
//	{
//
//		if (line.find(course->crs.info.idCourse.c_str()) != string::npos && line.find(course->crs.info.className.c_str()) != string::npos)
//		{
//			continue;
//		}
//		else
//		{
//			if (remember.empty())
//				remember = remember + line;
//			else
//				remember = remember + "\n" + line;
//		}
//	}
//	fileCourse.close();
//
//
//	course->crs.info.numberOfCurrentStudent = 0;
//
//
//
//
//	ofstream fileCourseToWrite("./raw/Course.txt");
//	fileCourseToWrite << remember << "\n";
//	fileCourseToWrite.close();
//	writeACourseToFile(course, "./raw/Course.txt");//fileCourseToWrite.close();
//	while (temp != NULL)
//	{
//		addAStudentToCourse(course, temp);
//		temp = temp->next;
//	}
//	system("cls");
//
//
//	printStudent(lst);
//	system("Pause");
//
//	deleteAllStudent(lst);
//
//}
//---------------------------------------------------------------------

//--------------------------DELETE A COURSE-----------------------------
//void deleteNodeCourse(listCourse& lst, nodeCourse* deletion)
//{
//	if (lst.head == NULL)
//	{
//		cout << "List is empty\n";
//		return;
//	}
//	while (lst.head->crs.info.idCourse == deletion->crs.info.idCourse && lst.head->crs.info.className == deletion->crs.info.className)
//	{
//		nodeCourse* temp = lst.head;
//		lst.head = lst.head->Next;
//		delete temp;
//		if (lst.head == NULL)
//		{
//			cout << "List is empty\n";
//			return;
//		}
//	}
//	nodeCourse* Prev = lst.head;
//	nodeCourse* Curr = Prev->Next;
//	while (Curr->Next != NULL)
//	{
//		if (Curr->crs.info.idCourse == deletion->crs.info.idCourse && deletion->crs.info.className == deletion->crs.info.className)
//		{
//			nodeCourse* temp = Curr;
//			Curr = Curr->Next;
//			Prev->Next = Curr;
//			delete temp;
//		}
//		else
//		{
//			Prev = Curr;
//			Curr = Curr->Next;
//		}
//	}
//	if (Curr->crs.info.idCourse == deletion->crs.info.idCourse && deletion->crs.info.className == deletion->crs.info.className)
//	{
//		Prev->Next = NULL;
//		delete Curr;
//	}
//
//}
//void deleteACourse(listCourse& lst, nodeCourse* deletion)
//{
//	//Kí hiệu R là file để đọc
//	//Kí hiệu W là file để ghi
//
//	//Xóa dòng chứa khóa học này trong file Course.txt;
//	ifstream fileCourseR("./raw/Course.txt");
//	if (!fileCourseR.is_open())
//	{
//		return;
//	}
//
//	string line, remember;
//	string idCourse = deletion->crs.info.idCourse;
//	string nameClass = deletion->crs.info.className;
//
//	while (std::getline(fileCourseR, line))
//	{
//		if (line.find(idCourse.c_str()) != string::npos && line.find(nameClass.c_str()) != string::npos)
//		{
//			continue;
//		}
//		else
//		{
//			if (remember.empty())
//				remember = remember + line;
//			else
//				remember = remember + "\n" + line;
//		}
//	}
//	fileCourseR.close();
//
//	ofstream fileCourseW("./raw/Course.txt");
//	if (!fileCourseW.is_open())
//	{
//		return;
//	}
//	fileCourseW << remember << "\n";
//	fileCourseW.close();
//	//Xóa toàn bộ học sinh 
//	const string courseName = "./raw/" + deletion->crs.info.courseName + "_" + deletion->crs.info.className + ".txt";
//	listStudent listS;
//	readListStudentOfACourse(listS, courseName);
//	nodeStudent* Temp = listS.head;
//	while (Temp != NULL)
//	{
//		deleteAStudentFromCourse(deletion, Temp);
//		Temp = Temp->next;
//	}
//	deleteNodeCourse(lst, deletion);
//	cout << "The course has been removed\n";
//	system("Pause");
//
//
//}

//----------------------------------------------------------------------
void changePasswordForStaff(nodeStaff*& staff, const char fileName[])
{
	int x = 0, y = 0;
	menuChangePassword(x, y);

	int i = 0, curPos[3] = { 0 };
	int newX[3] = { x + strlen("Input old password: ") + 1,
					x + strlen("Input new password: ") + 1,
					x + strlen("Confirm new password: ") + 1 };
	int newY[3] = { y, y + 3, y + 6 };
	int oldX = newX[0], oldY = newY[0];

	std::string input[3], remember, prev = " ";

	gotoXY(oldX, oldY);
	while (true) {
		ShowCur(1);
		char ch = _getch();

		if (ch == 27)
		{
			ShowCur(0);
			deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
			printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Exit change password !!!");
			return;
		}
		else if (ch == '\r')
		{
			if (staff->staff.account.passWord == input[0] && input[1] == input[2] && checkPassword(input[1]))
			{
				ifstream fileStudent(fileName);
				if (!fileStudent.is_open())
					return;

				string line;
				while (!fileStudent.eof())
				{
					std::getline(fileStudent, line); 
					if (line == "" || line == "\n")
						break;

					if (line.find(staff->staff.account.userName.c_str()) != std::string::npos && line.find(staff->staff.account.passWord.c_str()) != std::string::npos)
					{
						continue;
					}
					else
					{
						if (remember.length() == 0)
							remember = line;
						else
							remember = remember + "\n" + line;
					}
				}
				staff->staff.account.passWord = input[1];
				fileStudent.close();

				ShowCur(0);
				deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
				printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Change password succesfull !!!");

				break;
			}
			else if (staff->staff.account.passWord != input[0])
			{
				i = 0;
				ShowCur(0);
				deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
				printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Old password is invalid !!!");
				prev = "Old password is invalid !!!";
			}
			else if (!checkPassword(input[1]))
			{
				i = 1;
				ShowCur(0);
				deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
				printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Invalid new password entered !!!");
				prev = "Invalid new password entered !!!";
			}
			else if (input[1] != input[2])
			{
				i = 2;
				ShowCur(0);
				deleteTextAtXY(WIDTH_CONSOLE / 2, y + 9, prev);
				printTextAtXY(WIDTH_CONSOLE / 2, y + 9, "Confirm new password is invalid !!!");
				prev = "Confirm new password is invalid !!!";
			}

			curPos[i] = input[i].length();
			oldX = newX[i] + input[i].length();
			oldY = newY[i];
			gotoXY(oldX, oldY);
		}
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && i > 0) {
				i--;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 80 && i < 7) {
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 75 && curPos[i] > 0) {
				curPos[i]--;
				gotoXY(--oldX, oldY);
			}
			else if (ch == 77 && curPos[i] < input[i].length()) {
				curPos[i]++;
				gotoXY(++oldX, oldY);
			}
		}
		else if (ch == 9)
		{
			if (i < 2)
			{
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
		}
		else if (ch == '\b' && curPos[i] > 0)
		{
			curPos[i]--;
			input[i].erase(curPos[i], 1);
			gotoXY(newX[i], oldY);
			std::cout << input[i] << " ";
			gotoXY(--oldX, oldY);
		}
		else if (ch != '\b')
		{
			input[i].insert(curPos[i], 1, ch);
			curPos[i]++;
			std::cout << input[i].substr(curPos[i] - 1);
			gotoXY(++oldX, oldY);
		}
	}

	ofstream newFileStaff;
	newFileStaff.open(fileName);
	newFileStaff << remember << "\n";
	newFileStaff << staff->staff.account.userName << ",";
	newFileStaff << staff->staff.account.passWord << ",";
	newFileStaff << staff->staff.IDofStaff << ",";
	newFileStaff << staff->staff.lastName << ",";
	newFileStaff << staff->staff.firstName << ",";
	newFileStaff << staff->staff.gender << ",";
	newFileStaff << staff->staff.d.day << "/" << staff->staff.d.month << "/" << staff->staff.d.year << ",";
	newFileStaff << staff->staff.socialId << "\n";
	newFileStaff.close();
}
//------------------------------------------------------------------------------------------------

//-----------------EXPORT .CSV FILE AND OPERATE WITH SCORE-------------------------
//void exportCSVFile(const string address, nodeCourse* course)
//{
//	string addressFile = address;
//	if (addressFile[0] == '"')
//	{
//		addressFile.erase(0, 1);
//	}
//	if (addressFile[addressFile.size() - 1] == '"')
//	{
//		addressFile.pop_back();
//	}
//
//	if (address.back() == '\\')
//	{
//		addressFile = addressFile + course->crs.info.courseName + "_" + course->crs.info.className + ".csv";
//	}
//	else
//		addressFile = addressFile + "\\" + course->crs.info.courseName + "_" + course->crs.info.className + ".csv";
//	cout << addressFile << endl;
//	system("Pause");
//	ofstream fileCSV(addressFile);
//	if (!fileCSV.is_open())
//	{
//		cout << "Cannot write to file\n";
//		return;
//	}
//	const string courseName = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className + ".txt";
//	ifstream fileCourseR(courseName);
//	string line;
//	while (std::getline(fileCourseR, line))
//	{
//		fileCSV << line << "\n";
//	}
//	fileCSV.close();
//	fileCourseR.close();
//	cout << "Sucessfully exported!!. Press any key to continue\n";
//	system("Pause");
//}


//---------------------------------------------------------------------------------
void workSessionOfStaff(nodeStaff*& staff, listOfSchoolYear& lstSchoolYear, listCourse& lstCourse)
{
	int x = WIDTH_CONSOLE / 2 - 30, y = HEIGHT_CONSOLE / 2 - 9;
	int newX = x + 15, newY = y + 1;
	int oldX = newX, oldY = newY;
	int newWidth = 30, newHeight = 2;
	int nBox = 6, dis = 1;

	int count = 0;
	bool check = true;

	while (true)
	{
		if (count == 0)
		{
			system("cls");
			setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
			std::string str = staff->staff.lastName + " " + staff->staff.firstName;
			setTextColor(blue); gotoXY(1, 0); cout << "Username: " << staff->staff.account.userName;
			gotoXY(1, 1); cout << "Fullname: " << str;
			setBackgroundColor(lwhite); setTextColor(black);
			setTextColor(lpurple); print("Picture\\Hello Staff.txt", WIDTH_CONSOLE / 2 - 20, 1);
			setTextColor(green); printTwoLine(x, y, 20, 60);
			setTextColor(black);

			string* option = new string[nBox];
			option[0] = "Change password";
			option[1] = "View info";
			option[2] = "School Year";
			option[3] = "Class";
			option[4] = "Course";
			option[5] = "Log out";
			drawNBoxByY(x + 15, y + 1, newWidth, newHeight, nBox, dis, option);
			delete[] option;

			count++;
		}
		if (check == true)
		{
			gotoXY(oldX, oldY);
			focus(oldX, oldY, newWidth, ' ');
			oldX = newX, oldY = newY;

			focus(newX, newY, newWidth, (char)174);
			check = false;
		}
		if (_kbhit())
		{
			char choose = _getch();
			if (choose == 13)
			{
				if (newY == y + 1)
				{
					changePasswordForStaff(staff, "accountStaff.txt");
					count = 0;
				}
				else if (newY == y + 1 + newHeight + dis)
				{
					viewInfoStaff(staff);
					count = 0;
				}
				else if (newY == y + 1 + 2 * (newHeight + dis))
				{
					menuSchoolYearForStaff(staff);
					count = 0;
				}
				else if (newY == y + 1 + 3 * (newHeight + dis))
				{
					menuClassForStaff(staff);
					count = 0;
				}
				else if (newY == y + 1 + 4 * (newHeight + dis))
				{
					menuCourseForStaff(staff);
					count = 0;
				}
				else if (newY == y + 1 + 5 * (newHeight + dis))
				{
					setTextColor(yellow);
					printTextAtXY(WIDTH_CONSOLE / 2, newY + 3, "Goodbye staff !!!");
					return;
				}
			}
			else if (choose == -32)
			{
				choose = _getch();
				if (choose == 72 && newY > y + 1)
					newY = newY - newHeight - dis;
				else if (choose == 80 && newY < y + 1 + (nBox - 1) * (newHeight + dis))
					newY = newY + newHeight + dis;
			}

			check = true;
		}
	}	
}

bool checkPassword(std::string pass)
{
	int doDai = pass.length();
	if (doDai < 6)
		return false;

	int coKiTuHoa = 0;
	for (int i = 0; i < doDai; i++) {
		if (pass[i] >= 'A' && pass[i] <= 'Z') {
			coKiTuHoa = 1;
			break;
		}
	}
	
	int coKiTu = 0;
	for (int i = 0; i < doDai; i++) {
		if (pass[i] >= 'a' && pass[i] <= 'z')
		{
			coKiTu = 1;
			break;
		}
	}

	int coSo = 0;
	for (int i = 0; i < doDai; i++) {
		if (pass[i] >= '0' && pass[i] <= '9')
		{
			coSo = 1;
			break;
		}
	}

	int coDau = 0;
	for (int i = 0; i < doDai; i++) {
		if (pass[i] == ',' || pass[i] == '.' || pass[i] == ':' || pass[i] == '?' || pass[i] == '~' || pass[i] == '-' || pass[i] == '_' || pass[i] == ';' || pass[i] == '@')
			coDau = 1;
	}

	return (coKiTuHoa || coKiTu || coSo || coDau);
}

bool KiemTraHoTen(string hoTen)
{
	int coKhoangTrang = 0;
	int doDai = hoTen.length();
	for (int i = 0; i < doDai; i++) {
		if (hoTen[i] == ' ') {
			coKhoangTrang = 1;
			break;
		}
	}
	if (coKhoangTrang == 0)
		return 0;
	return 1;
}

void XoaKhoangCach(string &name)
{
	string res = "";
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
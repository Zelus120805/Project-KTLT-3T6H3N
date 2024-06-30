#include "myLib.h"

void viewOfStudent(nodeStudent* Student, int x, int y, int choice)
{
	std::string str = Student->student.info.lastName + " " + Student->student.info.firstName;
	setTextColor(blue); gotoXY(1, 0); cout << "Username: " << Student->student.account.userName;
	gotoXY(1, 1); cout << "Fullname: " << str;

	void (*pMenu)(int, int, int, int) = NULL;
	void (*pView)(listCourse, int, int, int, int) = NULL;

	listOfSchoolYear lst;
	lst.head = NULL;
	readSchoolYear(lst);
	nodeSchoolYear* schoolYearNow = goToSchoolYear(lst, x, y);
	int optn;

	setTextColor(blue); gotoXY(x, y); cout << "Input semester (1, 2, 3): ";
	ShowCur(1); setTextColor(black);
	do
	{
		gotoXY(x + strlen("Input semester (1, 2, 3): "), y); cout << "         ";
		gotoXY(x + strlen("Input semester (1, 2, 3): "), y); cin >> optn;
	} while (optn > 3 || optn < 1);
	ShowCur(0);

	string fileName = "./dataStudent/" + to_string(Student->student.info.idStudent) + "_Course_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(optn) + ".txt";
	listCourse l1;
	l1.head = NULL;
	readCourseFileOfStudent(l1, fileName);

	system("cls");
	setTextColor(green); print("Picture\\List.txt", WIDTH_CONSOLE / 2 - 12, 1);
	x = WIDTH_CONSOLE / 2 - 50, y = 7;
	int height = 17, width = 100;
	int Sum = countLine(fileName);
	int total, page;
	if (Sum % 12 == 0)
		total = Sum / 12;
	else
		total = Sum / 12 + 1;
	if (total == 0)
		page = 0;
	else
		page = 1;

	int New = 0, Old = 0;
	str = "     Use left and right keys to change pages !!!    ";
	setBackgroundColor(lyellow); setTextColor(red); gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE - 1); cout << str;
	str = "     Press 'esc' to return    ";
	gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE); cout << str;
	setBackgroundColor(lwhite);

	if (choice == 1)
	{
		pMenu = &menuBoxViewCoursesForStudent;
		pView = &viewCoursesForStudent;
	}
	else if (choice == 2)
	{
		pMenu = &menuBoxViewScoresForStudent;
		pView = &viewScoresForStudent;
	}

	bool check = true;
	while (true)
	{
		if (check == true)
		{
			str = "Page: " + to_string(page) + "/" + to_string(total);
			setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 99);
			setBackgroundColor(laqua);
			setTextColor(purple); 
			pMenu(x, y, height, width); gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;

			if (page != total)
				pView(l1, (page - 1) * 12 + 1, page * 12, x, y);
			else
				pView(l1, (page - 1) * 12 + 1, Sum, x, y);

			check = false;
		}
		gotoXY(x + 1, y + 3 + Old); setTextColor(black); cout << getConsoleLine(x + 1, y + 3 + Old, 99);
		setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 99);
		setBackgroundColor(laqua);
		Old = New;

		char ch = _getch();
		if (ch == 27)
			break;
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && New > 0) {
				New--;
			}
			else if (ch == 80) {
				if (page < total && New < 11)
					New++;
				else if (page == total && New < Sum - (total - 1) * 12 - 1)
					New++;
			}
			else if (ch == 75 && page > 1) {
				New = 0;
				page--;
				check = true;
			}
			else if (ch == 77 && page < total) {
				New = 0;
				page++;
				check = true;
			}
			else
				continue;
		}
	}

	setBackgroundColor(lwhite);
	deleteAllCourse(l1);
	deleteAllSchoolYear(lst);
}

void viewCoursesForStudent(listCourse l1, int start, int end, int x, int y)
{
	if (end == 0)
	{
		setTextColor(red);
		gotoXY(HEIGHT_CONSOLE / 2, y + 3); cout << "No data of student in this course !!!";
		return;
	}

	setTextColor(black);
	int index = 0, i = 1;
	nodeCourse* temp = l1.head;
	while (temp != NULL)
	{
		if (i == start)
			break;
		i++;
		temp = temp->Next;
	}

	while(temp != NULL)
	{
		if (i == end + 1)
			break;
		gotoXY(x + 1, y + 3 + index); cout << i;
		gotoXY(x + 5, y + 3 + index); cout << temp->crs.info.idCourse;
		gotoXY(x + 16, y + 3 + index); cout << temp->crs.info.className;
		gotoXY(x + 27, y + 3 + index); cout << temp->crs.info.courseName;
		gotoXY(x + 52, y + 3 + index); cout << temp->crs.info.teacherName;
		gotoXY(x + 79, y + 3 + index); cout << temp->crs.info.numberOfCredits;
		gotoXY(x + 88, y + 3 + index); cout << temp->crs.info.dayOfWeek;

		temp = temp->Next;
		index++; i++;
	}
}

void viewScoresForStudent(listCourse l1, int start, int end, int x, int y)
{
	setTextColor(red);
	if (checkScore == false)
	{
		gotoXY(HEIGHT_CONSOLE / 2, y + 3); cout << "Student can't see scoreboard in this time !!!";
		return;
	}
	if (end == 0)
	{
		gotoXY(HEIGHT_CONSOLE / 2, y + 3); cout << "Student doesn't have data in semester !!!";
		return;
	}

	setTextColor(black);
	int index = 0, i = 1;
	nodeCourse* temp = l1.head;
	while (temp != NULL)
	{
		if (i == start)
			break;
		i++;
		temp = temp->Next;
	}

	while (temp != NULL)
	{
		if (i == end + 1)
			break;
		gotoXY(x + 1, y + 3 + index); cout << i;
		gotoXY(x + 10, y + 3 + index); cout << temp->crs.info.courseName;
		gotoXY(x + 45, y + 3 + index); cout << temp->crs.info.className;
		gotoXY(x + 60, y + 3 + index); cout << temp->crs.info.score.otherMark;
		gotoXY(x + 70, y + 3 + index); cout << temp->crs.info.score.midtermMark;
		gotoXY(x + 80, y + 3 + index); cout << temp->crs.info.score.finalMark;
		gotoXY(x + 90, y + 3 + index); cout << temp->crs.info.score.totalMark;

		temp = temp->Next;
		index++; i++;
	}
}

void createNewCourseForStaff(listCourse& lst, nodeSchoolYear*& schoolYear, Semester semester)
{
	system("cls");
	setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions(); printMovingInstructionsAddTab();
	setBackgroundColor(lwhite);
	//setTextColor(blue); print("Picture\\Register.txt", WIDTH_CONSOLE / 2 - 23, 1);
	int x = WIDTH_CONSOLE / 2 - 50, y = HEIGHT_CONSOLE / 2 - 6, height = 15, width = 100;
	setTextColor(green); printTwoLine(x, y, height, width);
	setTextColor(black);
	nodeCourse* newCourse = new nodeCourse();
	//Nhập thông tin cơ bản một khóa học
	
	gotoXY(x + 2, y + 2); cout << "ID course: "; drawBox(x + 2 + strlen("Id Course: "), y + 1, 25, 2);
	gotoXY(x + 45, y + 2); cout << "Class name: "; drawBox(x + 45 + strlen("Class Name: "), y + 1, 40, 2);
	gotoXY(x + 2, y + 5); cout << "Course name: "; drawBox(x + 2 + strlen("Course Name: "), y + 4, 95 - strlen("Course Name: "), 2);
	gotoXY(x + 2, y + 8); cout << "Teacher name: "; drawBox(x + 2 + strlen("Teacher Name: "), y + 7, 95 - strlen("Teacher Name: "), 2);
	gotoXY(x + 2, y + 11); cout << "Day of week: "; drawBox(x + 2 + strlen("Day of week: "), y + 10, 15, 2);
	gotoXY(x + 35, y + 11); cout << "Number of credits: "; drawBox(x + 35 + strlen("number of credits: "), y + 10, 10, 2);
	gotoXY(x + 70, y + 11); cout << "Max students: "; drawBox(x + 70 + strlen("Max students: "), y + 10, 10, 2);

	char ch;
	int i = 0, curPos[7] = { 0 };
	std::string input[7];

	int newX[7] = { x + 2 + strlen("ID course: ") + 1,
					x + 45 + strlen("Class name: ") + 1,
					x + 2 + strlen("Course name: ") + 1,
					x + 2 + strlen("Teacher name: ") + 1,
					x + 2 + strlen("Day of week: ") + 1,
					x + 35 + strlen("Number of credits: ") + 1,
					x + 70 + strlen("Max students: ") + 1 };

	int newY[7] = { y + 2, y + 2, y + 5, y + 8, y + 11, y + 11, y + 11 };
	int oldX = newX[0], oldY = newY[0];
	std::string prev = " ";

	ShowCur(1);
	gotoXY(oldX, oldY);
	while (true) {
		ch = _getch();

		if (ch == 27)
		{
			ShowCur(0);

			return;
		}
		else if (ch == '\r')
		{
			int cnt = 0;
			for (int j = 0; j < 7; j++)
			{
				if (input[j].length() == 0)
				{
					cnt++;
					i = j;
					break;
				}
			}
			if (cnt == 0)
			{
				ShowCur(0);
				deleteTextAtXY(WIDTH_CONSOLE / 2, y + 14, prev);
				printTextAtXY(WIDTH_CONSOLE / 2, y + 14, "Create new course successfull !!!");
				break;
			}
			deleteTextAtXY(WIDTH_CONSOLE / 2, y + 14, prev);
			ShowCur(0);
			printTextAtXY(WIDTH_CONSOLE / 2, y + 14, "Input data invalid !!!");
			ShowCur(1);
			prev = "Input data invalid !!!";

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

	newCourse->crs.info.idCourse = input[0];
	newCourse->crs.info.courseName = input[2];
	newCourse->crs.info.className = input[1];
	newCourse->crs.info.teacherName = input[3];
	newCourse->crs.info.dayOfWeek = input[4];
	newCourse->crs.info.numberOfCredits = stoi(input[5]);
	newCourse->crs.info.maxStudent = stoi(input[6]);
	newCourse->Next = NULL;

	////Tạo file danh sách lớp 
	string fileListStudent = "./dataCourse/" + newCourse->crs.info.courseName + "_" + newCourse->crs.info.className + "_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";
	string fileSemester = "./dataSemester/Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";
	std::ofstream listStudentInCourse(fileListStudent, std::ios_base::app);
	if (listStudentInCourse.is_open() == false)
	{
		return;
	}
	if (lst.head == NULL)
	{
		lst.head = newCourse;
		writeACourseToFile(newCourse, fileSemester);
		listStudentInCourse << "No," << "Student ID," << "Student Last Name," << "Student First Name," << "Gender," << "Other Mark(Assignment)," << "Midterm Mark," << "Final Mark," << "Average Mark\n";
	}
	else
	{
		writeACourseToFile(newCourse, fileSemester);
		listStudentInCourse << "No," << "Student ID," << "Student Last Name," << "Student First Name," << "Gender," << "Other Mark(Assignment)," << "Midterm Mark," << "Final Mark," << "Average Mark\n";
		nodeCourse* temp = lst.head;
		while (temp->Next != NULL)
		{
			temp = temp->Next;
		}
		temp->Next = newCourse;
	}

	string str = "Press any key to continue";
	setTextColor(red); gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, y + 17); cout << str;
	ch = _getch();
	setTextColor(black);
}

void loadCourse(nodeSchoolYear*& schoolYear, Semester& semester)
{
	string fileName = "./dataSemester/Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";
	readCourseFile(semester.listCourse, fileName);
	if (semester.listCourse.head == NULL)
	{
		//cout << "No student in Course\n";
		return;
	}
}

nodeCourse* goToCourse(listCourse lstCourse)
{
	system("cls");
	setTextColor(laqua); print("Picture\\List Class.txt", WIDTH_CONSOLE / 2 - 12, 1);
	int x = WIDTH_CONSOLE / 2 - 40, y = 7;
	int height = 17, width = 80;
	int Sum = 0;
	nodeCourse* temp = lstCourse.head;
	if (temp == NULL)
		return NULL;
	while (temp != NULL)
	{
		temp = temp->Next;
		Sum++;
	}
	int total, page;
	if (Sum % 12 == 0)
		total = Sum / 12;
	else
		total = Sum / 12 + 1;
	if (total == 0)
		page = 0;
	else
		page = 1;

	int New = 0, Old = 0;
	string str = "     Use left and right keys to change pages    ";
	setBackgroundColor(lyellow); setTextColor(red); gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE - 1); cout << str;
	str = "     Press 'esc' to return and 'enter' to choose    ";
	gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE); cout << str;
	setBackgroundColor(lwhite);

	bool check = true;
	while (true)
	{
		if (check == true)
		{
			str = "Page: " + to_string(page) + "/" + to_string(total);
			setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 79);
			setBackgroundColor(laqua);
			setTextColor(purple);
			menuViewChooseCourses(x, y, height, width);
			gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;

			if (page != total)
				ViewChooseCourses(lstCourse, (page - 1) * 12 + 1, page * 12, x, y);
			else
				ViewChooseCourses(lstCourse, (page - 1) * 12 + 1, Sum, x, y);

			check = false;
		}
		gotoXY(x + 1, y + 3 + Old); setTextColor(black); cout << getConsoleLine(x + 1, y + 3 + Old, 79);
		setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 79);
		setBackgroundColor(laqua);
		Old = New;

		char ch = _getch();
		if (ch == 27)
		{
			setBackgroundColor(lwhite);
			return NULL;
		}
		else if (ch == '\r')
		{
			break;
		}
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && New > 0) {
				New--;
			}
			else if (ch == 80) {
				if (page < total && New < 11)
					New++;
				else if (page == total && New < Sum - (total - 1) * 12 - 1)
					New++;
			}
			else if (ch == 75 && page > 1) {
				New = 0;
				page--;
				check = true;
			}
			else if (ch == 77 && page < total) {
				New = 0;
				page++;
				check = true;
			}
			else
				continue;
		}
	}

	int i = 1;
	int optn = New + (page - 1) * 12 + 1;
	temp = lstCourse.head;
	while (optn != i)
	{
		temp = temp->Next;
		i++;
	}
	setBackgroundColor(lwhite);
	return temp;
}

void addNStudentFromFileForStaff(nodeSchoolYear*& schoolYear, Semester semester, nodeCourse*& course, string fileName)
{
	//Bước này chỉ xử lí tên file nhập vào, không cần bận tâm-------------------------------------------------
	string str = fileName;
	if (str[0] == '"')
	{
		str.erase(0, 1);
	}
	if (str[str.size() - 1] == '"')
	{
		str.pop_back();
	}
	//--------------------------------------------------------------------------------------------------------
	ifstream fileStudent(str);
	if (!fileStudent.is_open())
	{
		//std::cout << "Khong the doc file" << endl;
		return;
	}
	//Đọc từng sinh viên
	listStudent lst = { };
	lst.head = NULL;
	readStudentFromCSVForStaff(lst, str);
	nodeStudent* temp = lst.head;
	while (temp != NULL)
	{
		addAStudentToCourseForStaff(schoolYear, semester, course, temp);
		temp = temp->next;
	}
	setTextColor(red);
	if (lst.head != NULL)
		printTextAtXY(WIDTH_CONSOLE / 2, 12, "Successfully added !!!");
	else
		printTextAtXY(WIDTH_CONSOLE / 2, 12, "Fail to add !!!");
	setTextColor(black);

	//deleteAllStudent(lst);
	fileStudent.close();
}

void readStudentFromCSVForStaff(listStudent& lst, string fileName)
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
		Student->student.info.idStudent = std::stoi(temp);
		std::getline(fileStudent, temp, ',');

		Student->student.info.lastName = temp;
		std::getline(fileStudent, temp, ',');

		Student->student.info.firstName = temp;
		std::getline(fileStudent, temp, ',');

		Student->student.info.gender = temp;
		std::getline(fileStudent, temp, '/');

		Student->student.info.d.day = std::stoi(temp);
		std::getline(fileStudent, temp, '/');
		Student->student.info.d.month = std::stoi(temp);
		std::getline(fileStudent, temp, ',');
		Student->student.info.d.year = std::stoi(temp);
		std::getline(fileStudent, temp, ',');

		Student->student.info.socialId = temp;
		std::getline(fileStudent, temp, '\n');

		Student->student.info.inClass = temp;
		addTailStudent(lst, Student);

	}

	fileStudent.close();
}

void addAStudentToCourseForStaff(nodeSchoolYear* schoolYear, Semester semester, nodeCourse*& course, nodeStudent* student)
{
	if (isInCourse(schoolYear, semester, student, course))
	{
		return;
	}
	string nameFile = "./dataCourse/" + course->crs.info.courseName + "_" + course->crs.info.className + "_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";

	std::ofstream fileList(nameFile, std::ios_base::app);

	string studentFile = "./dataStudent/" + to_string(student->student.info.idStudent) + "_Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";

	std::ofstream fileStudent(studentFile, std::ios_base::app);
	if (!fileStudent.is_open())
	{
		cout << "ERROR\n";
		return;
	}
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

	string fileCourseR = "./dataSemester/Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";

	std::ifstream fileCourse(fileCourseR);
	string temp, remember;

	while (std::getline(fileCourse, temp))
	{

		if (temp.find(course->crs.info.idCourse.c_str()) != std::string::npos && temp.find(course->crs.info.className.c_str()) != std::string::npos)
		{
			continue;
		}
		else
		{
			if (remember.empty())
				remember = remember + temp;
			else
				remember = remember + "\n" + temp;
		}
	}

	fileCourse.close();
	std::ofstream update;
	update.open(fileCourseR);
	if (!remember.empty())
		update << remember << "\n";
	update.close();
	writeACourseToFile(course, fileCourseR);
}

void updateCourse(nodeSchoolYear* schoolYearNow, Semester semesterNow, nodeCourse*& courseNow)
{
	//Chọn thông tin muốn update
	string fileCourseR = "./dataSemester/Course_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(semesterNow.NO) + ".txt";

	std::ifstream fileCourse(fileCourseR);
	if (!fileCourse.is_open())
		return;
	string temp, remember;
	//Tạm thời xóa khóa học kia ra khỏi 

	while (std::getline(fileCourse, temp))
	{

		if (temp.find(courseNow->crs.info.idCourse.c_str()) != std::string::npos && temp.find(courseNow->crs.info.className.c_str()) != std::string::npos)
		{
			continue;
		}
		else
		{
			if (remember.empty())
				remember = remember + temp;
			else
				remember = remember + "\n" + temp;
		}
	}

	//Tên file danh sách lớp để hồi đổi
	string fileListStudentOld = "./dataCourse/" + courseNow->crs.info.courseName + "_" + courseNow->crs.info.className + "_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(semesterNow.NO) + ".txt";


	//Cho người dùng lựa chọn: Đổi cái gì. 
	int optn;

	int x = WIDTH_CONSOLE / 2 - 50, y = HEIGHT_CONSOLE / 2 - 8;
	int width = 30, height = 2;
	int nBox = 6, dis = 1;

	int newX = x + 10, newY = y + 1;
	int oldX = newX, oldY = newY;

	bool check = true;
	int cnt = 0;
	while (true)
	{
		if (cnt == 0)
		{
			system("cls");
			setTextColor(blue); print("Picture\\Update Info Course.txt", WIDTH_CONSOLE / 2 - 35, 1);
			setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
			setBackgroundColor(lwhite);
			setTextColor(green); printTwoLine(x, y, 19, 50);

			string* option = new string[nBox];
			option[0] = "ID Course";
			option[1] = "Course Name";
			option[2] = "Class name";
			option[3] = "Teacher name";
			option[4] = "Number of credit";
			option[5] = "Day of week";

			setTextColor(black); drawNBoxByY(x + 10, y + 1, width, height, nBox, dis, option);
			delete[] option;

			cnt++;
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
			if (choose == 27)
			{
				return;
			}
			else if (choose == 13)
			{
				if (newY == y + 1)
				{
					setTextColor(blue); gotoXY(x + 55, y + 1); cout << "Input new ID course: ";
					setTextColor(green); drawBox(x + 55 + strlen("Input new ID course: "), y, 30, 2);
					setTextColor(black);
					ShowCur(1); gotoXY(x + 55 + strlen("Input new ID course: ") + 1, y + 1);
					cin.ignore();
					getline(cin, courseNow->crs.info.idCourse);
					ShowCur(0);
				}
				else if (newY == y + 1 + 1 * (height + dis))
				{
					setTextColor(blue); gotoXY(x + 55, y + 1); cout << "Input new course name: ";
					setTextColor(green); drawBox(x + 55 + strlen("Input new course name: "), y, 30, 2);
					setTextColor(black);
					ShowCur(1); gotoXY(x + 55 + strlen("Input new course name: ") + 1, y + 1);
					cin.ignore();
					getline(cin, courseNow->crs.info.courseName);
					ShowCur(0);
				}
				else if (newY == y + 1 + 2 * (height + dis))
				{
					setTextColor(blue); gotoXY(x + 55, y + 1); cout << "Input new class name: ";
					setTextColor(green); drawBox(x + 55 + strlen("Input new class name: "), y, 30, 2);
					setTextColor(black);
					ShowCur(1); gotoXY(x + 55 + strlen("Input new class name: ") + 1, y + 1);
					cin.ignore();
					getline(cin, courseNow->crs.info.className);
					ShowCur(0);
				}
				else if (newY == y + 1 + 3 * (height + dis))
				{
					setTextColor(blue); gotoXY(x + 55, y + 1); cout << "Input new teacher name: ";
					setTextColor(green); drawBox(x + 55 + strlen("Input new teacher name: "), y, 30, 2);
					setTextColor(black);
					ShowCur(1); gotoXY(x + 55 + strlen("Input new teacher name: ") + 1, y + 1);
					cin.ignore();
					getline(cin, courseNow->crs.info.teacherName);
					ShowCur(0);
				}
				else if (newY == y + 1 + 4 * (height + dis))
				{
					setTextColor(blue); gotoXY(x + 55, y + 1); cout << "Input new number of credits: ";
					setTextColor(green); drawBox(x + 55 + strlen("Input new number of credits: "), y, 10, 2);
					setTextColor(black);
					ShowCur(1); gotoXY(x + 55 + strlen("Input new number of credits: ") + 1, y + 1);
					cin.ignore();
					cin >> courseNow->crs.info.numberOfCredits;
					ShowCur(0);
				}
				else if (newY == y + 1 + 5 * (height + dis))
				{
					setTextColor(blue); gotoXY(x + 55, y + 1); cout << "Input new day of week: ";
					setTextColor(green); drawBox(x + 55 + strlen("Input new day of week: "), y, 20, 2);
					setTextColor(black);
					ShowCur(1); gotoXY(x + 55 + strlen("Input new day of week: ") + 1, y + 1);
					cin.ignore();
					cin >> courseNow->crs.info.dayOfWeek;
					ShowCur(0);
				}

				break;
				cnt = 0;
			}
			else if (choose == -32)
			{
				choose = _getch();
				if (choose == 72 && newY > y + 1)
					newY = newY - height - dis;
				else if (choose == 80 && newY < y + 1 + (nBox - 1) * (height + dis))
					newY = newY + height + dis;
			}

			check = true;
		}
	}

	//Đổi tên file danh sách lớp cho phù hợp. 
	string fileListStudentNew = "./dataCourse/" + courseNow->crs.info.courseName + "_" + courseNow->crs.info.className + "_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(semesterNow.NO) + ".txt";
	int renameFile = rename(fileListStudentOld.c_str(), fileListStudentNew.c_str());


	fileCourse.close();
	std::ofstream update;
	update.open(fileCourseR);
	if (!remember.empty())
		update << remember << "\n";
	update.close();
	writeACourseToFile(courseNow, fileCourseR);
}

void deleteACourse(nodeSchoolYear* schoolYearNow, Semester& semesterNow, listCourse& lst, nodeCourse* deletion)
{
	string fileCourse = "./dataSemester/Course_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(semesterNow.NO) + ".txt";

	ifstream fileCourseR(fileCourse);
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

	ofstream fileCourseW(fileCourse);
	if (!fileCourseW.is_open())
	{
		return;
	}
	fileCourseW << remember << "\n";
	fileCourseW.close();
	//Xóa toàn bộ học sinh 
	const string courseName = "./dataCourse/" + deletion->crs.info.courseName + "_" + deletion->crs.info.className + "_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(semesterNow.NO) + ".txt";
	listStudent listS;
	readListStudentOfACourse(listS, courseName); //Có rồi, xem ở trên
	if (listS.head == NULL)
	{
		return;
	}
	nodeStudent* Temp = listS.head;
	while (Temp != NULL)
	{
		deleteAStudentFromCourse(schoolYearNow, semesterNow, deletion, Temp);
		Temp = Temp->next;
	}
}

void deleteAStudentFromCourse(nodeSchoolYear* schoolYear, Semester semester, nodeCourse*& course, nodeStudent* deletion)
{
	string courseName = "./dataCourse/" + course->crs.info.courseName + "_" + course->crs.info.className + "_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";
	ifstream fileCourse(courseName);
	if (!fileCourse.is_open())
	{
		//cout << "Cannot open file course\n";
		return;
	}
	listStudent lst = {};
	lst.head = NULL;
	readListStudentOfACourse(lst, courseName);//Có rồi

	nodeStudent* Head = lst.head;
	int no = deleteAStudentForStaffInCourse(lst);
	if (no == 0)
		return;
	deletion = goToStudent(no, lst);

	//Xóa khóa học trong file tất cả các bạn học sinh
	while (Head != NULL)
	{
		string Line, Temp;
		string studentFile = "./dataStudent/" + to_string(Head->student.info.idStudent) + "_Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";
		std::ifstream fileStudent(studentFile);
		if (!fileStudent.is_open())
		{
			break;
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
		if (!Temp.empty())
			fileStudent2 << Temp << "\n";

		fileStudent2.close();
		Head = Head->next;
	}


	deleteNodeStudent(lst, deletion);//Xem dưới
	fileCourse.close();

	ofstream newFile;
	newFile.open(courseName);
	newFile << "No," << "Student ID," << "Student Last Name," << "Student First Name," << "Gender," << "Other Mark(Assignment)," << "Midterm Mark," << "Final Mark," << "Average Mark\n";
	nodeStudent* temp = lst.head;
	course->crs.info.numberOfCurrentStudent = 0;
	newFile.close();
	ifstream fileCourseToRead("./dataSemester/Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt");

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

	ofstream fileCourseToWrite("./dataSemester/Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt");
	fileCourseToWrite << remember << "\n";
	fileCourseToWrite.close();

	writeACourseToFile(course, "./dataSemester/Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt");//Có rồi, xem trên

	while (temp != NULL)
	{
		addAStudentToCourseForStaff(schoolYear, semester, course, temp);//Có luôn
		temp = temp->next;
	}
	/*system("cls");
	system("Pause");*/

	deleteAllStudent(lst);//Hàm giải phóng bộ nhớ
}



void deleteNodeCourse(listCourse& lst, nodeCourse* deletion)
{
	if (lst.head == NULL)
	{
		//cout << "List is empty\n";
		return;
	}
	while (lst.head->crs.info.idCourse == deletion->crs.info.idCourse && lst.head->crs.info.className == deletion->crs.info.className)
	{
		nodeCourse* temp = lst.head;
		lst.head = lst.head->Next;
		delete temp;
		if (lst.head == NULL)
		{
			//cout << "List is empty\n";
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

void exportCSVFile(nodeSchoolYear* schoolYear, Semester semester, const string address, nodeCourse* course)
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

	ofstream fileCSV(addressFile);
	if (!fileCSV.is_open())
	{
		//cout << "Cannot write to file\n";
		//return;
	}
	const string courseName = "./dataCourse/" + course->crs.info.courseName + "_" + course->crs.info.className + "_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";
	ifstream fileCourseR(courseName);
	string line;
	while (std::getline(fileCourseR, line))
	{
		fileCSV << line << "\n";
	}
	fileCSV.close();
	fileCourseR.close();
	
	//setBackgroundColor(yellow), setTextColor(red);
	printTextAtXY(WIDTH_CONSOLE / 2 - strlen("     Export CSV file successful !!!     ") / 2, 12, "     Export CSV file successful !!!     ");
	setTextColor(red);
	string str = "Press any key to continue";
	gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, 14); cout << str;
	char ch = _getch();
	setBackgroundColor(lwhite);
}

void importScoreBoard(nodeSchoolYear* schoolYear, Semester semester, nodeCourse*& course, const string fileName)
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
	const string courseName = "./dataCourse/" + course->crs.info.courseName + "_" + course->crs.info.className + "_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";
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
		const string studentFile = "./dataStudent/" + Line + +"_Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";
		std::ifstream fileStudent(studentFile);
		if (!fileStudent.is_open())
		{
			return;
		}

		std::getline(fileScoreR, Line, ',');
		std::getline(fileScoreR, Line, ',');
		std::getline(fileScoreR, Line, ',');
		std::getline(fileScoreR, Line, '\n');
		string line, remember;
		string linetemp;
		//Xóa trạng thái khóa học hiện t
		bool flag = false;
		while (!fileStudent.eof())
		{
			flag = false;
			std::getline(fileStudent, line);
			if (line == "" || line == "\n")
			{
				flag = true;
				break;
			}
			if (line.find(idCourse.c_str()) != string::npos && line.find(nameClass.c_str()) != string::npos && !flag)
			{
				linetemp = line;
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
			//cout << "OK3456" << endl;
			int i = 0;
			while (linetemp[i] != ',')
			{
				i++;
			}
			//		cout << "OK1" << endl;
			i++;
			while (linetemp[i] != ',')
			{
				i++;
			}
			//		cout << "OK2" << endl;
			i++;
			while (linetemp[i] != ',')
			{
				i++;
			}
			//	cout << "OK3" << endl;
			i++;
			while (linetemp[i] != ',')
			{
				i++;
			}
			//	cout << "OK4" << endl;
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
			if (!remember.empty())
				fileStudentW << remember << "\n";
			fileStudentW << linetemp;
			fileStudentW.close();
		}
	}
	fileScoreR.close();
	
	setBackgroundColor(yellow), setTextColor(red);
	printTextAtXY(WIDTH_CONSOLE / 2 - strlen("     Import scoreboard successful !!!     ") / 2, 12, "     Import scoreboard successful !!!     ");
	string str = "Press any key to continue";
	gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, 14); cout << str;
	char ch = _getch();
	setBackgroundColor(lwhite);
}

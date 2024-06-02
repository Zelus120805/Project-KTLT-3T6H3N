#include "Class.h"
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
void add1StudentToClass(Class& myClass,const char fileName[])
{
	readFileStudent(myClass.lst,fileName);
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
	newNode->myClass.lst.head= nullptr;
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

	add1StudentToClass(newNode->myClass,fileName);

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



//Để đây chút viết hàm ghi student xong quay trở lại viết
void writeStudentToFileClass(Class a, const char fileName[])
{
	std::ofstream fileClass(fileName,std::ios_base::app);
	if (!fileClass)
		return;
	fileClass << a.nameClass << "|\n";
//writeStudentToFile(a.lst, fileName);

	nodeStudent* temp = a.lst.head;
	if (a.lst.head == NULL)
	{
		return;
	}
	std::ofstream account("accountStudent.txt",std::ios_base::app);
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
	while (getline(myFile, temp,'-'))
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
			int i=1;
			nodeSchoolYear* temp = lst.head;
			if (temp == NULL)
			{
				std::cout << "Please create at least 1 school year" << std::endl;
				return;
			}
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
			createClass(temp->y.listOfClass);//Tạo một lớp của năm học đó

			string fileName = to_string(temp->y.startYear) +"-"+ to_string(temp->y.endYear)+".txt";
			char *tmp = new char[fileName.length()+1];
			fileName.copy(tmp, fileName.length());
			tmp[fileName.length()] = '\0';
			std::ofstream classOfSchoolYear(tmp,std::ios::app);

			if (classOfSchoolYear.is_open() ==false)
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
//--------------------------------------
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
	getline(std::cin,newCourse->crs.info.idCourse);

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
	string fileListStudent = "./raw/"+ newCourse->crs.info.courseName + "_" + newCourse->crs.info.className + ".txt";
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
		listStudentInCourse << "No," << "Student ID," << "Student Last Name," << "Student First Name," <<"Gender," << "Other Mark(Assignment)," << "Midterm Mark," << "Final Mark," << "Average Mark\n";
		return;
	}
	writeACourseToFile(newCourse, "./raw/Course.txt");
	listStudentInCourse << "No," << "Student ID," << "Student Last Name," << "Student First Name," << "Gender,"<< "Other Mark(Assignment)," << "Midterm Mark," << "Final Mark," << "Average Mark\n";
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
	string nameFile = "./raw/" + course->crs.info.courseName + "_" + course->crs.info.className +".txt";
	std::ofstream fileList(nameFile, std::ios_base::app);

	string studentFile = "./raw/" + to_string(student->student.info.idStudent) + "_Course" + ".txt";
	std::ofstream fileStudent(studentFile, std::ios_base::app);

	if (!fileList.is_open()||!fileStudent.is_open())
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
	fileStudent << course->crs.info.idCourse << "," << course->crs.info.courseName << "," << course->crs.info.className << "," << course->crs.info.teacherName << "," << course->crs.info.numberOfCredits << "," << course->crs.info.dayOfWeek <<",0,0,0,0\n";
	//Cập nhật danh sách lớp của khóa học đó.
	

	fileList << course->crs.info.numberOfCurrentStudent << "," << student->student.info.idStudent << "," << student->student.info.lastName << "," << student->student.info.firstName << "," << student->student.info.gender << ",0,0,0,0\n";

	std::ifstream fileCourse("./raw/Course.txt");
	string temp,remember;
	
	while (!fileCourse.eof())
	{

		getline(fileCourse, temp);
		if (temp.find(course->crs.info.idCourse.c_str()) != std::string::npos && temp.find(course->crs.info.className.c_str()) != std::string::npos)
		{ 
			continue;
		}
		else
		{
			remember = remember + "\n"+temp;
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

//Đọc file khóa học mỗi khi chạy chương trình//Chút viết tiếp, viết hàm addTail Khóa học đã
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
	listStudent lst;
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
}

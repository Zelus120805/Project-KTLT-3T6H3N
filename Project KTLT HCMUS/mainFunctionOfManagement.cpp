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
	char fileName[100];
	std::cout << "File input: ";
	cin >> fileName;
	add1StudentToClass(newNode->myClass,fileName);
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
//Để đây chút viết hàm ghi student xong quay trở lại viết
void writeStudentToFileClass(Class a, const char fileName[])
{
	std::ofstream fileClass(fileName,std::ios::app);
	if (!fileClass)
		return;
	fileClass << a.nameClass << "|\n";
//writeStudentToFile(a.lst, fileName);

	nodeStudent* temp = a.lst.head;
	if (a.lst.head == NULL)
	{
		return;
	}
	while (temp != NULL)
	{
		fileClass << temp->student.account.userName << ",";
		fileClass << temp->student.account.passWord << ",";
		fileClass << temp->student.info.idStudent << ",";
		fileClass << temp->student.info.lastName << ",";
		fileClass << temp->student.info.firstName << ",";
		fileClass << temp->student.info.gender << ",";
		fileClass << temp->student.info.d.year << "," << temp->student.info.d.month << "," << temp->student.info.d.day << ",";
		fileClass << temp->student.info.socialId << "\n";
		temp = temp->next;
	}

	fileClass.close();
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
	//std::cout << "";
}
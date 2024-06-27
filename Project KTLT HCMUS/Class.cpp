#include "myLib.h"

void viewClassesForStaff(nodeStaff* staff, int x, int y)
{
	listOfSchoolYear lst;
	lst.head = NULL;
	readSchoolYear(lst);
	nodeSchoolYear* schoolYearNow = goToSchoolYear(lst, x, y);
}

void createClass(nodeSchoolYear* schoolYear, listClass& lst, int x ,int y)
{
    nodeClass* newNode = new nodeClass();
    newNode->next = NULL;
    newNode->myClass.lst.head = NULL;

    setTextColor(blue); gotoXY(x, y + 1); std::cout << "Input class name: ";
    setTextColor(black); 
    drawBox(x + strlen("Input class name: "), y, 40, 2);
    ShowCur(1);
    gotoXY(x + strlen("Input class name: ") + 1, y + 1); cin.ignore(); getline(cin, newNode->myClass.nameClass);
    ShowCur(0);

    string fileClassName = "./dataSchoolYear/" + newNode->myClass.nameClass + "" + to_string(schoolYear->y.startYear) + " - " + to_string(schoolYear->y.endYear) + ".txt";
    ofstream fileClassW(fileClassName);
    fileClassW << "ID Student,Last name,First Name,Gender,Date Of Birth,Social ID\n";
    fileClassW.close();
    string fileClass = "./dataSchoolYear/Class" + to_string(schoolYear->y.startYear) + " - " + to_string(schoolYear->y.endYear) + ".txt";
    ofstream fileListClass(fileClass, ios_base::app);
    fileListClass << newNode->myClass.nameClass << "\n";
    fileListClass.close();
    //"C:\Users\pc\Desktop\PythonApplication1\PythonApplication1\file.csv"
    //Kiểm tra tên lớp có tồn tại hay chưa?
    //nodeClass* check = lst.head;

    string fileName;
    setTextColor(blue); gotoXY(x, y + 5); std::cout << "Input file to import: ";
    setTextColor(black);
    drawBox(x + strlen("Input file to import: "), y + 4, 36, 2);
    ShowCur(1);
    gotoXY(x + strlen("Input file to import: ") + 1, y + 5); std::getline(cin, fileName);
    ShowCur(0);

    readFileCSVClass(newNode->myClass.lst, fileName);
    //    add1StudentToClass(newNode->myClass, fileName);
    nodeStudent* temp = newNode->myClass.lst.head;
    if (temp == NULL)
    {
        // cout << "List is empty\n";
    }
    else
    {

        while (temp != NULL)
        {
            addAStudentToClass(schoolYear, newNode->myClass, temp);
            temp = temp->next;
        }
    }

    string str = "Press any key to continue";
    setTextColor(red); gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, HEIGHT_CONSOLE - 3); cout << str;
    char ch = _getch();
    deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE - 3, str);
    deleteMenu(x, y, 9, 45);
    setTextColor(black);
}

void addAStudentToClass(nodeSchoolYear* schoolYear, Class& myClass, nodeStudent* student)
{
    string fileClassName = "./dataSchoolYear/" + myClass.nameClass + "_" + to_string(schoolYear->y.startYear) + " - " + to_string(schoolYear->y.endYear) + ".txt";
    ofstream fileClassW(fileClassName, ios_base::app);
    if (!fileClassW.is_open())
    {
        //cout << "Cannot open file\n";
        return;
    }

    //Ghi student đó ra file
    fileClassW << student->student.info.idStudent << ",";
    fileClassW << student->student.info.lastName << ",";
    fileClassW << student->student.info.firstName << ",";
    fileClassW << student->student.info.gender << ",";
    fileClassW << student->student.info.d.day << "/" << student->student.info.d.month << "/" << student->student.info.d.year << ",";
    fileClassW << student->student.info.socialId << "\n";
    student->student.info.inClass = myClass.nameClass;

    //Gán mặc định tên tài khoản và mật khẩu. 
    fileClassW.close();
    ofstream account("accountStudent.txt", ios_base::app);
    if (!account.is_open())
    {
        //cout << "ERROR!!\n";
        return;
    }
    student->student.account.userName = to_string(student->student.info.idStudent);
    student->student.account.passWord = "123";

    //Khởi tạo tài khoản cho học sinh đó. 
    account << student->student.account.userName << ",";
    account << student->student.account.passWord << ",";
    account << student->student.info.idStudent << ",";
    account << student->student.info.lastName << ",";
    account << student->student.info.firstName << ",";
    account << student->student.info.gender << ",";
    account << student->student.info.d.day << "/" << student->student.info.d.month << "/" << student->student.info.d.year << ",";
    account << student->student.info.socialId << ",";
    account << student->student.info.inClass << "\n";
    account.close();
    // addTailStudent(myClass.lst, student);
}

void readFileCSVClass(listStudent& lst, const string fileName)
{
    //Kí hiệu Rn là file để đọc lần thứ n
    // Kí hiệu Wn là file để ghi lần thứ n
    // n=1 không ghi
    //Mở file .CSV đó lên
    string str = fileName;
    if (str[0] == '"')
    {
        str.erase(0, 1);
    }
    if (str[str.length() - 1] == '"')
    {
        str.pop_back();
    }
    ifstream fileClassR(str);
    if (!fileClassR.is_open())
    {
        cout << "ERROR!\n";
        return;
    }
    string temp;
    std::getline(fileClassR, temp);
    while (std::getline(fileClassR, temp, ','))
    {
        nodeStudent* newNode = new nodeStudent();
        newNode->next = NULL;
        newNode->student.info.idStudent = stoi(temp);
        std::getline(fileClassR, temp, ',');
        newNode->student.info.lastName = temp;
        std::getline(fileClassR, temp, ',');
        newNode->student.info.firstName = temp;
        std::getline(fileClassR, temp, ',');
        newNode->student.info.gender = temp;
        std::getline(fileClassR, temp, '/');
        newNode->student.info.d.day = std::stoi(temp);
        std::getline(fileClassR, temp, '/');
        newNode->student.info.d.month = std::stoi(temp);
        std::getline(fileClassR, temp, ',');
        newNode->student.info.d.year = std::stoi(temp);
        std::getline(fileClassR, temp, '\n');
        newNode->student.info.socialId = temp;
        newNode->student.account.userName = to_string(newNode->student.info.idStudent);
        newNode->student.account.passWord = "123";
        addTailStudent(lst, newNode);
    }
}
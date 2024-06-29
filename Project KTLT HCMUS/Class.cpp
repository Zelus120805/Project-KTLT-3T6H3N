#include "myLib.h"

void viewClassesForStaff(nodeSchoolYear* node, int x, int y)
{
    string fileName = "dataSchoolYear\\Class_" + to_string(node->y.startYear) + "-" + to_string(node->y.endYear) + ".txt";
    int Sum = countLine(fileName);
    string* className = new string[Sum];
    string temp;
    int i = 0;
    ifstream file(fileName);
    if (Sum != 0)
    {
        while (getline(file, temp))
        {
            if (temp == "")
                break;
            className[i] = temp;
            i++;
        }
    }
    file.close();

    int total, page;
    if (Sum % 10 == 0)
        total = Sum / 10;
    else
        total = Sum / 10 + 1;
    if (total == 0)
        page = 0;
    else
        page = 1;

    int width = 40, height = 15;
    int New = 0, Old = 0;
    string str;

    bool check = true;
    while (true)
    {
        if (check == true)
        {
            str = "Page: " + to_string(page) + "/" + to_string(total);
            setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 39);
            setBackgroundColor(laqua);
            setTextColor(purple);
            menuViewClasses(x, y, height, width);
            gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;

            if (page != total)
                viewClasses(className, (page - 1) * 10 + 1, page * 10, x, y);
            else
                viewClasses(className, (page - 1) * 10 + 1, Sum, x, y);

                check = false;
        }
        gotoXY(x + 1, y + 3 + Old); setTextColor(black); cout << getConsoleLine(x + 1, y + 3 + Old, 39);
        setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 39);
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
                if (page < total && New < 9)
                    New++;
                else if (page == total && New < Sum - (total - 1) * 10 - 1)
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

    deleteMenu(x, y, height, width);
    setBackgroundColor(lwhite);
}

void viewClasses(string* className, int start, int end, int x, int y)
{
    setTextColor(black);
    int index = 0;

    for (int i = start; i <= end; i++)
    {
        gotoXY(x + 1, y + 3 + index); cout << i;
        gotoXY(x + 10, y + 3 + index); cout << className[i - 1];

        index++;
    }
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

    string fileClassName = "./dataClass/" + newNode->myClass.nameClass + "_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + ".txt";
    ofstream fileClassW(fileClassName);
    fileClassW << "ID Student,Last name,First Name,Gender,Date Of Birth,Social ID\n";
    fileClassW.close();

    string fileClass = "./dataSchoolYear/Class_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + ".txt";
    ofstream fileListClass(fileClass, ios_base::app);
    fileListClass << newNode->myClass.nameClass << "\n";
    fileListClass.close();

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
        string str = "No data of student in this file !!!";
        printTextAtXY(x + str.length() / 2, y + 7, str);
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
    string fileClassName = "./dataClass/" + myClass.nameClass + "_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + ".txt";
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
        //cout << "ERROR!\n";
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

void addTailClass(listClass& lst, Class newClass)
{
    nodeClass* newNode = new nodeClass();
    newNode->myClass = newClass;
    newNode->next = NULL;
    if (lst.head == NULL)
    {
        lst.head = newNode;
        return;
    }
    nodeClass* temp = lst.head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void readFileListClass(listClass& lst, const string fileName)
{
    ifstream fileListClass(fileName);
    if (!fileListClass.is_open())
    {
        //	cout << "ok1\n";
        return;
    }
    string Line;
    while (std::getline(fileListClass, Line))
    {
        if (Line == "" || Line == "\n")
            return;
        Class newClass;
        newClass.nameClass = Line;

        addTailClass(lst, newClass);
    }
    fileListClass.close();
}

//string fileName = "./dataSchoolYear/Class_" + to_string(schoolYearNow->y.startYear) + " - " + to_string(schoolYearNow->y.endYear) + ".txt";

void evaluateGPA(nodeStudent* studentNow, nodeSchoolYear* schoolYearNow, Semester semesterNow, bool staffViewAllCourseYes, bool staffViewGPAYes)
{
    double GPA = 0;
    int numOfCreadits = 0;
    string fileCourse = "./dataStudent/" + to_string(studentNow->student.info.idStudent) + "Course" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(semesterNow.NO) + ".txt";
    ifstream fileCourseR1(fileCourse);
    if (fileCourseR1.is_open() == false)
    {
        return;
    }
    int count = 0;
    string line;
    while (fileCourseR1.eof() == false)
    {
        getline(fileCourseR1, line, '\n');
        if (line == "")
            continue;
        count++;
    }
    // count = số dòng
    int** score = new int* [count];
    for (int i = 0; i < count; i++)
    {
        score[i] = new int[4];
    }
    Course* ListCourse = new Course[count];
    fileCourseR1.close();


    ifstream fileCourseR(fileCourse);
    int i = 0;
    while (getline(fileCourseR, line, ','))
    {

        ListCourse[i].info.idCourse = line;
        getline(fileCourseR, line, ',');
        ListCourse[i].info.courseName = line;
        getline(fileCourseR, line, ',');
        ListCourse[i].info.className = line;
        getline(fileCourseR, line, ',');
        ListCourse[i].info.teacherName = line;
        getline(fileCourseR, line, ',');
        ListCourse[i].info.numberOfCredits = stoi(line);
        numOfCreadits += stoi(line);
        getline(fileCourseR, line, ',');
        ListCourse[i].info.dayOfWeek = line;
        getline(fileCourseR, line, ',');
        getline(fileCourseR, line, ',');
        score[i][1] = stoi(line);
        getline(fileCourseR, line, ',');
        score[i][2] = stoi(line);
        getline(fileCourseR, line, '\n');
        score[i][3] = stoi(line);
        GPA += score[i][3] * ListCourse[i].info.numberOfCredits;
        i++;
    }
    fileCourseR.close();
    GPA = GPA / numOfCreadits;


    //Phần này dành cho giao diện sinh viên
    if (!staffViewAllCourseYes && !staffViewGPAYes)
    {
        cout << "ID course - CourseName - ClassName - Number of credits - Assigment - Midterm - Final - Average\n";
        for (int i = 0; i < count; i++)
        {
            cout << ListCourse[i].info.idCourse << " - " << ListCourse[i].info.courseName << " - " << ListCourse[i].info.className << " - " << ListCourse[i].info.numberOfCredits << " - " << score[i][0] << " - " << score[i][1] << " - " << score[i][2] << " - " << score[i][3] << endl;
        }
        cout << "GPA in this semester: " << GPA << endl;
    }

    if (staffViewGPAYes)//Phần này dành cho giao diện staff xem điểm GPA cả lớp
    {
        cout << "ID - Name - GPA\n";
        cout << studentNow->student.info.idStudent << " - " << studentNow->student.info.lastName + studentNow->student.info.firstName << " - " << GPA << endl;
    }

    system("Pause");
    system("cls");
    for (int i = 0; i < count; i++)
    {
        delete score[i];
    }
    delete score;
}
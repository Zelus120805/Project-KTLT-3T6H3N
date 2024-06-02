#include "Class.h"
#include "Course.h"
//#include "privateUser.h"
#include "Semester.h"
listStudent lst;

listOfSchoolYear list;

listCourse listOfCourse;

int main()
{
	int section;
	//readAccountFile(lst);
	//readAccountFile(lst);
	lst.head = nullptr;
	list.head = nullptr;
	listOfCourse.head = nullptr;
	readCourseFile(listOfCourse);
	readFileStudent(lst, "accountStudent.txt");
	while (true)
	{
		std::cout << "1. Register \n";
		std::cout << "2. SignIn\n";
		//std::cout << "3. ChangePassword\n";
		std::cout << "3. Exit\n";
		std::cout << "4. Add a school year\n";
		std::cout << "5. Create a course\n";
		std::cout << "6. Add students from file\n";
		std::cin >> section;
		if (section == 1)
		{
			//userRegister(lst,"account.txt");
			 //char fileName[500];
			 //cin >> fileName;
			 studentRegister(lst, "accountStudent.txt");
		}
		if (section == 2)
		{
			readFileStudent(lst, "accountStudent.txt");
			studentLogIn(lst, "accountStudent.txt",listOfCourse);//Sua tham so ham LogIn de vao phien dang nhap cua user do.
		}
		if (section == 3)
		{
			return 0;
		}
		if (section == 4)
		{
			operateWithSchoolYear(list);
		}
		if (section == 5)
		{
			createNewCourse(listOfCourse);
		}
		if (section == 6)
		{
			//IN khóa học ra để lựa chọn 
			nodeCourse* temp = listOfCourse.head;
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
				//Di chuyển tới khóa học đã chọn và thực hiện thêm sinh viên từ file. 
				i = 1;
				temp = listOfCourse.head;
				cout << "Select course: ";
				cin >> sub;
				while (temp != NULL)
				{
					if (i == sub)
					{
						string fileName;
						cout << "Nhap ten file: ";
						cin.ignore();
						getline(cin,fileName);
						cout << fileName << endl;
					//	system("pause");
						addNStudentFromFile(temp, fileName);
						break;
					}
					i++;
					temp = temp->Next;
				}
			}
		}
		//if (section == 3)
		//{
		//	changePassword(lst);
		//}
		//changePassword nam trong phien dang nhap cua user, phai dang nhap roi moi doi mat khau duoc
	}
	
}
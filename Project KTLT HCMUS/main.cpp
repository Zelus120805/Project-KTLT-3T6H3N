#include "Class.h"
#include "Course.h"
#include "privateUser.h"
#include "Semester.h"
int main()
{
	int section;
	listUser lst;
	lst.head = nullptr;
	readAccountFile(lst);
	while (true)
	{
		std::cout << "1. Register \n";
		std::cout << "2. SignIn\n";
		//std::cout << "3. ChangePassword\n";
		std::cout << "3. Exit\n";
		std::cin >> section;
		if (section == 1)
		{
			userRegister(lst);
		}
		if (section == 2)
		{
			userLogIn(lst);//Sua tham so ham LogIn de vao phien dang nhap cua user do.
		}
		if (section == 3)
		{
			return 0;
		}
		//if (section == 3)
		//{
		//	changePassword(lst);
		//}
		//changePassword nam trong phien dang nhap cua user, phai dang nhap roi moi doi mat khau duoc
	}
	
}
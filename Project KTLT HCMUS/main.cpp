#include "Class.h"
#include "Course.h"
#include "privateUser.h"
#include "Semester.h"
int main()
{
	int section;
	listUser lst;
	lst.head = nullptr;
	while (true)
	{
		std::cout << "1. Register \n";
		std::cout << "2. SignIn\n";
		std::cout << "3. ChangePassword\n";
		std::cout << "4. Exit\n";
		std::cin >> section;
		if (section == 1)
		{
			userRegister(lst);
		}
		if (section == 2)
		{
			userLogIn();
		}
		if (section == 4)
		{
			return 0;
		}
		if (section == 3)
		{
			changePassword(lst);
		}
	}
	
}
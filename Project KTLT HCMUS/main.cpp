#include "Class.h"
#include "Course.h"
#include "privateUser.h"
#include "Semester.h"
int main()
{
	int section;
	while (true)
	{
		std::cout << "1. Register \n";
		std::cout << "2. SignIn\n";
		std::cout << "3. Exit\n";
		std::cin >> section;
		if (section == 1)
		{
			userRegister();
		}
		if (section == 2)
		{
			userLogIn();
		}
		if (section == 3)
		{
			return 0;
		}
	}
	
}
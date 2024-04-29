#include "User.h"
void userRegister()
{
	std::ofstream account;
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
	account << user.userName << "," << user.passWord << "\n";
	account.close();
}
void userLogIn()
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
		int check = 0;
		getline(account, temp, ',');
		user1.userName = temp;
		getline(account, temp, '\n');
		user1.passWord = temp;
		if (user1.userName == user.userName && user1.passWord == user.passWord)
		{
			std::cout << "Go to home page" << "\n";
			return;
		}
	}
	std::cout << "Account does not exist" << "\n";
	account.close();
}
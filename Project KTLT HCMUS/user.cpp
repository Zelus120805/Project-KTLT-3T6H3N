#include "User.h"
void userRegister(listUser& lst)
{
	std::ofstream account;
	account.open("account.txt", std::ios_base::app);
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
	if (lst.head == nullptr)
	{
		lst.head->user = user;
		lst.head->next = nullptr;
	}
	else
	{
		nodeUser* temp = new nodeUser();
		temp = lst.head;
		while (temp != nullptr)
		{
			temp = temp->next;
		}
		temp->user = user;
		temp->next = nullptr;
	}
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

void changePassword(listUser& lst)
{
	User user;
	std::cout << "Username: ";
	std::cin >> user.userName;
	std::cout << "Password: ";
	std::cin >> user.passWord;

	nodeUser* tempNode = new nodeUser();
	tempNode = lst.head;
	while (tempNode != nullptr)
	{
		if (user.userName == tempNode->user.userName)
		{
			string change;
			std::cout << "New password: ";
			std::cin >> change;
			tempNode->user.passWord = change;
			break;
		}
		tempNode = tempNode->next;
	}
	tempNode = lst.head;
	std::ofstream account;
	account.open("account.txt");
	while (tempNode != nullptr)
	{
		account << tempNode->user.userName << "," << tempNode->user.passWord << "\n";
		tempNode = tempNode->next;
	}
	account.close();
}
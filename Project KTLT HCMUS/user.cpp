#include "User.h"
void userRegister(listUser& lst, const char fileName[])
{
	std::ofstream account;
	account.open(fileName, std::ios_base::app);
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
	nodeUser* newNode = new nodeUser;
	newNode->user = user;
	newNode->next = NULL;
	if (lst.head == NULL)
	{
		lst.head = newNode;
	}
	else
	{
		nodeUser* temp = new nodeUser();
		temp = lst.head;
		while (temp ->next!= nullptr)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	account.close();
}
void userLogIn(listUser& lst)
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
		getline(account, temp, ',');
		user1.userName = temp;
		getline(account, temp, '\n');
		user1.passWord = temp;
		if (user1.userName == user.userName && user1.passWord == user.passWord)
		{
			workSession( user);//Neu ten dang nhap va mat khau dung thi vao phien dang nhap
			return;
		}
	}
	std::cout << "Account does not exist" << "\n";
	system("cls");//Them ham xoa man hinh cho dep
	account.close();
}

#include <iostream>
#include <fstream>
#include <string>

void changePassword(const string userName, const string newPass)
{
	std::ifstream oldFile("account.txt");
	std::ofstream newFile("temp.txt");

	if (!oldFile.is_open() || !newFile.is_open()) {
		std::cout << "Can't open file" << std::endl;
		return;
	}

	std::string name, pass;
	int count = 0;

	while (getline(oldFile, name, ',')) {
		getline(oldFile, pass);
		if (name.empty() || pass.empty()) break;

		if (count == 0)
		{
			if (name == userName)
			{
				newFile << name << "," << newPass << "\n";
				count++;
			}
			else
				newFile << name << "," << pass << "\n";
		}
		else
			newFile << name << "," << pass << "\n";

		name.clear();
		pass.clear();
	}
	oldFile.close();
	newFile.close();
	if (count == 0) std::cout << "Can't find entered username";
	string line;
	std::ifstream new_File("temp.txt");
	std::ofstream old_File("account.txt");

	if (!new_File.is_open() || !old_File.is_open()) {
		std::cout << "Can't change the password" << std::endl;
		return;
	}
	while (getline(new_File, line))
	{
		old_File << line << "\n";
	}
	cout << "Your pass has been changed" << std::endl;
}


void workSession( User& user)
{
	system("cls");
	if (user.userName.length() == 0)
	{
		return;
	}

	int section;
	while (true)
	{
		std::cout << "Hello " << user.userName << "\n";
		std::cout << "1. Change password" << "\n";
		std::cout << "2. Log out" << "\n";
		cin >> section;
		if (section == 1)
		{
			string newPass;
			std::cin >> newPass;
			changePassword(user.userName,newPass);
		}
		if (section == 2)
		{
			system("cls");
			break;
		}
	}
}
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
			workSession(lst, user);//Neu ten dang nhap va mat khau dung thi vao phien dang nhap
			return;
		}
	}
	std::cout << "Account does not exist" << "\n";
	system("cls");//Them ham xoa man hinh cho dep
	account.close();
}

void changePassword(listUser& lst,User user1)
{
	User user;
	std::cout << "Username: ";
	std::cin >> user.userName;
	do {
		std::cout << "Password: ";
		std::cin >> user.passWord;
	} while (user1.passWord != user.passWord);
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
			system("cls");
			std::cout << "Your password has been changed!\n";
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
void readAccountFile(listUser& lst)
{
	std::ifstream account;
	account.open("account.txt");
	if (account.is_open() == false)
	{
		return;
	}
	nodeUser* newNode = new nodeUser();
	string temp;
	getline(account,temp, ',');
	newNode->user.userName = temp;
	getline(account, temp, '\n');
	newNode->user.passWord = temp;
	newNode->next = nullptr;
	lst.head = newNode;
	while (!account.eof())
	{
		nodeUser* temp1 = lst.head;
		while (temp1->next != NULL)
		{
			temp1 = temp1->next;
		}
		newNode = new nodeUser();
		getline(account, temp, ',');
		newNode->user.userName = temp;
		getline(account, temp, '\n');
		newNode->user.passWord = temp;
		newNode->next = nullptr;
		temp1->next = newNode;
	}
}
void workSession(listUser& lst, User& user)
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
			changePassword(lst,user);
		}
		if (section == 2)
		{
			system("cls");
			break;
		}
	}
}
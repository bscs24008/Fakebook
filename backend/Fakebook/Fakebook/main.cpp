#include <iostream>
#include <string>
#include "User.h"
#include "utills.h"
#include <vector>

using namespace std;

int main()
{
	User* users;
	int number_of_users;

	ifstream input_file("Text.txt");

	input_file >> number_of_users;

	users = new User[number_of_users];
	for (int i = 0; i < number_of_users; i++)
	{
		input_file >> users[i];
	}

	input_file.close();
	
	for (int i = 0; i < number_of_users; i++)
	{
		users[i].print();
	}

	save_users(users, number_of_users);
}
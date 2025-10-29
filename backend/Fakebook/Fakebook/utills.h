#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include <vector>

using namespace std;

void load_users(User*& users, int& number_of_users)
{
	ifstream input_file("Text.txt");

	input_file >> number_of_users;

	users = new User[number_of_users];
	for (int i = 0; i < number_of_users; i++)
	{
		input_file >> users[i];
	}

	input_file.close();
}

void save_users(User*& users, const int& number_of_users)
{
	ofstream output_file("Text.txt");

	output_file << number_of_users << endl;
	
	for (int i = 0; i < number_of_users; i++)
	{
		output_file << users[i];
		output_file << endl;
	}

	output_file.close();
}
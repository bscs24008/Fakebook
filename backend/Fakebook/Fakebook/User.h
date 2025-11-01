#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Post;
class User
{
private:
	string username;
	string password;
	string email;
	string Location;
	string gender;
	int age;
	bool is_public;
	vector<Post*> posts;
public:
	User()
	{
		is_public = true;
		age = 18;
	}
	User(string _user, string _pass, string _email, string _loc, string _gender, int _age, bool user_type)
	{
		username = _user;
		password = _pass;
		email = _email;
		Location = _loc;
		gender = _gender;
		age = _age;
		is_public = user_type;
	}
	void operator=(const User& other)
	{
		username = other.username;
		password = other.password;
		email = other.email;
		Location = other.Location;
		gender = other.gender;
		age = other.age;
		is_public = other.is_public;
	}
	User(const User& other)
	{
		username = other.username;
		password = other.password;
		email = other.email;
		Location = other.Location;
		gender = other.gender;
		age = other.age;
		is_public = other.is_public;
	}
	void friend operator>>(ifstream& input, User& other)
	{
		getline(input, other.username, ',');
		getline(input, other.password, ',');
		getline(input, other.email, ',');
		getline(input, other.Location, ',');
		getline(input, other.gender, ',');
		input >> other.age;
		input.ignore();
		input >> other.is_public;
	}
	void friend operator<<(ofstream& output, User& other)
	{
		output << other.username;
		output << ",";
		output << other.password;
		output << ",";
		output << other.email;
		output << ",";
		output << other.Location;
		output << ",";
		output << other.gender;
		output << ",";
		output << other.age;
		output << ",";
		output << other.is_public;
	}
	void print()
	{
		cout << username << endl;
		cout << password << endl;
		cout << email << endl;
		cout << Location << endl;
		cout << gender << endl;
		cout << "Age: " << age << endl;
		cout << "Is public" << is_public << endl;
	}
	string getusername(){
		return username;
	}
	bool check_pswrd(string p) {
		return p == password;
	}
};
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Post.h"
using namespace std;

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
	int num_friends;
	vector<Post*> posts;
	vector<User*> sent_requests;
	vector<User*> recieved_requests;

public:
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
	string getemail() {
		return email;
	}
	bool check_pswrd(string p) {
		return p == password;
	}
	int getNumFriends() {
		return num_friends;
	}
	void add_sent_request(User* usr) {
		for (int i = 0; i < sent_requests.size(); i++) {
			if (usr == sent_requests[i])
				return;
		}
		sent_requests.push_back(usr);
	}
	void add_recieved_request(User* usr) {
		for (int i = 0; i < recieved_requests.size(); i++) {
			if (usr == sent_requests[i])
				return;
		}
		recieved_requests.push_back(usr);
	}
	void remove_sent_request(User* usr) {
		auto it = find(sent_requests.begin(), sent_requests.end(), usr);
		if (it != sent_requests.end())
			sent_requests.erase(it);
	}
	void remove_recieved_request(User* usr) {
		auto it = find(recieved_requests.begin(), recieved_requests.end(), usr);
		if (it != recieved_requests.end())
			recieved_requests.erase(it);
	}
	vector<Post*> getPosts() {
		return posts;
	}
};
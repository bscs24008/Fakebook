#pragma once
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "Database.h"
using namespace std;

class DummyDataGenerator {
private:
	vector<string> usernames;
	vector<string> email;
	vector<string> gender;
	int indexForVisited;
	vector<string> location;
	vector<string> text;
	vector<string> url;
	Database* db;

	string randomPassword() {
		string password = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		string user_password;

		for (int i = 0; i < 8; i++) {
			user_password += password[rand() % password.size()];
		}
		return user_password;
	}

	int randomAge() {
		return 18 + (rand() % 70); // it shoud remain between 18 and 88
	}

	friend class Database;
public:
	DummyDataGenerator(Database* database) {
		db = database;
	}

	void loadFromFile(const string& usersFile, const string& locationsFile, const string& postsFile)
	{
		ifstream user(usersFile);
		ifstream loc(locationsFile);
		ifstream post(postsFile);
		string u, e, g, l, t, ur;

		if (!user.is_open() or !loc.is_open() or !post.is_open()) {
			cout << "Could not open file" << endl;
		}

		while (getline(user, u, '#') and getline(user, e, '#') and getline(user, g) and getline(loc, l, '\n') and getline(post, t, '#') and getline(post, ur)) {
			usernames.push_back(u);
			email.push_back(e);
			gender.push_back(g);
			location.push_back(l);
			text.push_back(t);
			url.push_back(ur);
		}
	}

	void loadIntoDatabase() {
		for (int i = 0; i < usernames.size(); i++) {
			string password = randomPassword();
			int age = randomAge();
			bool status = rand() % 2;
			db->addUser(usernames[i], email[i], password, location[i], gender[i], age, status, string());
		}
		for (int i = 0; i < usernames.size() * 2; i++) {
			int user1 = rand() % db->users.size();
			int user2 = rand() % db->users.size();
			db->addFriendship(db->users[user1], db->users[user2]);
		}

	}

	void testOutput() {
		for (size_t i = 0; i < usernames.size(); i++) {
			cout << "User: " << usernames[i] << "\n"
				<< "Email: " << email[i] << "\n"
				<< "Gender: " << gender[i] << "\n"
				<< "Location: " << location[i] << "\n"
				<< "Post: " << text[i] << "\n"
				<< "URL: " << url[i] << "\n";
		}
	}
};

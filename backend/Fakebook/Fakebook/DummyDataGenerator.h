#pragma once
#include <iostream>
#include <string>
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

public:
	void loadFromFile(const string& usersFile, const string& locationsFile, const string& postsFile)
	{
		ifstream user(usersFile);
		ifstream loc(locationsFile);
		ifstream post(postsFile);
		string u, e, g;
		string l;
		string t, ur;

		while (getline(user, u, '#') and getline(user, e, '#') and getline(user, g) and getline(loc, l, '\n') and getline(post, t, '#') and getline(post, ur)) {
			usernames.push_back(u);
			email.push_back(e);
			gender.push_back(g);
			location.push_back(l);
			text.push_back(t);
			url.push_back(ur);
		}
	}

	void testOutput()  {
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

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "Post.h"
using namespace std;

struct PublicData {
	string username;
	string profile_picture;
	vector<Post*> posts;
	bool is_public;
	PublicData(string _un, string p, bool _is_public, vector<Post*> _posts) : 
		username(_un), profile_picture(p), is_public(_is_public), posts(_posts) {}
	PublicData() {}
};

class User
{
private:
	string username;
	string password;
	string email;
	string Location;
	string gender;
	string profile_picture;
	int age;
	bool is_public;
	vector<Post*> posts;
	vector<User*> sent_requests;
	vector<User*> recieved_requests;

public:
	User(string _user, string _pass, string _email, string _loc, 
		string _gender, int _age, bool user_type, string profile_pic)
	{
		username = _user;
		password = _pass;
		email = _email;
		Location = _loc;
		gender = _gender;
		age = _age;
		profile_picture = profile_pic;
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
	void add_sent_request(User* usr) {
		for (int i = 0; i < sent_requests.size(); i++) {
			if (usr == sent_requests[i])
				return;
		}
		sent_requests.push_back(usr);
	}
	void add_recieved_request(User* usr) {
		for (int i = 0; i < recieved_requests.size(); i++) {
			if (usr == recieved_requests[i])
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
	vector<User*> getSentRequests() {
		return sent_requests;
	}
	vector<User*> getReceivedRequests() {
		return recieved_requests;
	}
	bool get_status() {
		return is_public;
	}
	PublicData getPublicData() {
		if (is_public) {
			return PublicData(username, profile_picture, is_public, posts);
		}
		return PublicData(username, profile_picture, is_public, vector<Post*>());
	}
	void add_post(string text, time_t now_time, string url) {
		posts.push_back(new Post(username, now_time, text, url));
	}
	void delete_post(Post* p) {
		auto it = find(posts.begin(), posts.end(), p);
		if (it != posts.end())
			posts.erase(it);
	}
	string get_profile_pic() {
		return profile_picture;
	}
	void set_profile_picture(string p) {
		profile_picture = p;
	}
	~User() {
		int s = posts.size();
		for (int i = 0; i < s; i++) {
			delete posts[i];
		}
	}
};
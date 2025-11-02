#include <iostream>
#include <string>
#include <vector>
#include "FriendNetwork.h"
#include "Database.h"
#include "FeedManager.h"
#include "User.h"
#include "Post.h"
#include "DummyDataGenerator.h"
using namespace std;

void showMainMenu(Database& db, FeedManager &feed);
void showUserMenu(Database& db, User* user, FeedManager& feed);
void handleSignup(Database& db);
User* handleLogin(Database& db);
void handleViewProfile(Database& db, User* user);
void handleCreatePost(Database& db, User* user);
void handleAddFriend(Database& db, User* user);
void handleRespondRequests(Database& db, User* user);
void handleViewFeed(Database& db, User* user, FeedManager& feed);

int main()
{
	Database db;
	DummyDataGenerator generator(&db);
	generator.loadFromFile("users.txt", "locations.txt", "posts.txt");
	generator.loadIntoDatabase();
	FeedManager feed(&db);
	showMainMenu(db, feed);
	return 0;
}

void showMainMenu(Database &db, FeedManager &feed) {
	int choice = 0;
	do {
		cout << "*** FakeBook *** \n"
			<< "1. Sign Up \n"
			<< "2. Login \n"
			<< "3. Exit \n"
			<< "Enter your choice: ";
		cin >> choice;

		User* loginUser;
		switch (choice) {
		case 1:
			handleSignup(db);
			break;
		case 2:
			loginUser = handleLogin(db);
			if (loginUser) {
				showUserMenu(db, loginUser, feed);
			}
			break;
		case 3:
			cout << "Exiting application...\n";
			break;
		default:
			cout << "Invalid choice. Try again.\n";
		}
	} while (choice != 3);
}

void handleSignup(Database& db) {
	string username, email, password, location, gender;
	int age;
	char privacy;
	bool isPublic;
	cout << "--- Sign Up --- \n";
	cout << "Enter username: "; cin >> username;
	cout << "Enter email: "; cin >> email;
	if (db.getUserUsername(username, "") || db.getUserEmail(email, "")) {
		cout << "Username or email already in use. Try again. \n";
		return;
	}
	cout << "Enter password: "; cin >> password;
	cout << "Enter location: "; cin >> location;
	cout << "Enter gender: "; cin >> gender;
	cout << "Enter age: "; cin >> age;
	cout << "Public Profile? (y/n): "; cin >> privacy;
	isPublic = privacy == 'y';
	db.addUser(username, email, password, location, gender, age, isPublic, " ");
	cout << "User created successfully! \n";
}

User* handleLogin(Database &db) {
	cout << "--- Login --- \n";
	cout << "1. Username \n"
		<< "2. Email \n";
	int choice;
	cin >> choice;

	string info, password;
	if (choice == 1) {
		cout << "Enter username: ";  
		cin >> info;
	}
	else {
		cout << "Enter email: "; 
		cin >> info;
	}
	cout << "Enter password: ";
	cin >> password;

	User* user = nullptr;
	bool succesfulLogin = false;

	if (choice == 1) {
		succesfulLogin = db.getUserUsername(info, password) != nullptr;
		user = db.getUserUsername(info, password);
	}
	else {
		succesfulLogin = db.getUserEmail(info, password) != nullptr;
		user = db.getUserEmail(info, password);
	}
	if (!succesfulLogin) {
		cout << "Invalid credentials. \n";
		return nullptr;
	}

	cout << "Login succesfull! Welcome " << user->getusername() << "! \n";
	return user;
}

void showUserMenu(Database &db, User* user, FeedManager &feed) {
	int choice = 0;
	do {
		cout << "--- User Menu --- \n"
			<< "1. Create Posts \n"
			<< "2. View Profile \n"
			<< "3. View Feed \n"
			<< "4. Add Friend \n"
			<< "5. Respond to Friend Requests \n"
			<< "6. Logout \n"
			<< "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			handleCreatePost(db, user);
			break;
		case 2:
			handleViewProfile(db, user);
			break;
		case 3:
			handleViewFeed(db, user, feed);
			break;
		case 4:
			handleAddFriend(db, user);
			break;
		case 5:
			handleRespondRequests(db, user);
			break;
		case 6:
			cout << "Logging out... \n";
			break;
		default:
			cout << "Invalid choice. Try again. \n";
		}

	} while (choice != 6);
}

void handleViewProfile(Database &db, User* user) {
	cout << " --- Profile --- \n";
	user->print();
	vector<Post*> posts = user->getPosts();

	if (posts.empty()) 
		cout << "No posts yet.\n";
	else {
		cout << " --- Posts --- \n";
		for (auto p : posts) 
			p->display();
	}
}

void handleCreatePost(Database& db, User* user) {
	cout << " --- Create Post --- \n";

	string content;
	cout << "Enter post content: ";
	cin.ignore();
	getline(cin, content);

	time_t time_stamp = time(nullptr);
	user->add_post(content, time_stamp, " ");

	cout << "Post creted succesfully at " << time_stamp << "! \n";
}

void handleAddFriend(Database& db, User* user) {
	cout << " --- Add Friend --- \n";
	string username;
	cout << "Enter username to search: ";
	cin.ignore();
	getline(cin, username);

	User* f = db.isUser(username);						
	if (!f) {
		cout << "User not found. \n";
		return;
	}
	user->add_sent_request(f);
	f->add_recieved_request(user);

	cout << "Friend request sent to " << f->getusername() << endl;
}

void handleRespondRequests(Database& db, User* user) {
	vector<User*> requests = user->getReceivedRequests();
	if (requests.empty()) {
		cout << "No pending friend requests. \n";
		return;
	}

	for (int i = 0; i < requests.size(); i++) {
		cout << i + 1 << ". " << requests[i]->getusername() << endl;
	}
	int choice;
	cout << "Select request to respond to: ";
	cin >> choice;
	User* requestedBy = requests[choice - 1];
	cout << "1. Accept \n"
		<< "2. Decline \n"
		<< "Enter your choice: ";
	cin >> choice;

	switch (choice) {
	case 1:
		db.addFriendship(user, requestedBy);
		cout << "Friend request accepted. \n";
		break;
	case 2:
		user->remove_recieved_request(requestedBy);
		requestedBy->remove_sent_request(user);
		cout << "Friend request declined. \n";
		break;
	}
}

void handleViewFeed(Database& db, User* user, FeedManager& feed) {
	feed.setUser(user);
	feed.refreshFeed();
	while (feed.has_next()) {
		feed.next();
	}
}


#include <iostream>
#include <string>
#include <vector>
#include "FriendNetwork.h"
#include "Database.h"
#include "FeedManager.h"
#include "User.h"
#include "Post.h"
#include "DummyDataGenerator.h"
#include "utills.h"
using namespace std;

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
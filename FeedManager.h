#pragma once
#include <iostream>
#include "Heap.h"
#include "Database.h"
#include "User.h"
#include "Post.h"
#include <functional>
using namespace std;

class FeedManager {
private:
	User* user;
	Database* db;
	function<bool(Post*, Post*)> comparePosts = [](Post* p1, Post* p2) {
		return p1->getTimeStamp() > p2->getTimeStamp();
	};
	Heap<Post*> friendsPosts(comparePosts);
	Heap<Post*> FoFPosts(comparePosts);

public:
	FeedManager(Database *database, User *_user): db(database), user(_user) {}

	void refreshFeed() {
		if (!user or !db) {
			cout << "User or database not available." << endl;
			return;
		}

		vector<Post*> friendsContent = db->getFriendsPosts(user);
		vector<Post*> friendsOfFriendsContent = db->getFoFPosts(user);
		friendsPosts.buildHeap(friendsContent);
		FoFPosts.buildHeap(friendsOfFriendsContent);
	}

	void showFeed() { // for trsting output on console
		if (!user) {
			cout << "Invalid user selected.\n";
			return;
		}
		cout << user->getusername() << "'s Feed" << endl;
		
		Heap<Post*>	f = friendsPosts;
		while (!f.empty()) {
			auto post = f.extract();
			post->display();
		}

		Heap<Post*> fof = FoFPosts;
		while (!fof.empty()) {
			auto post = fof.extract();
			post->display();
		}
	}

	void setUser(User* _user) {
		user = _user;
	}
};
#pragma once
#include <iostream>
#include "Heap.h"
#include "Database.h"
#include "User.h"
#include "Post.h"
#include <functional>
#include <stack>
using namespace std;

class FeedManager {
private:
	User* user;
	Database* db;
	function<bool(Post*, Post*)> comparePosts = [](Post* p1, Post* p2) {
		return p1->getTimeStamp() > p2->getTimeStamp();
	};
	Heap<Post*> Posts(comparePosts);
	stack<Post*> prev_posts;
	Post* current_post;

public:
	FeedManager(Database *database, User *_user): db(database), user(_user), current_post(nullptr) {}

	void refreshFeed() {
		if (!user or !db) {
			cout << "User or database not available." << endl;
			return;
		}
		vector<Post*> friendsContent = db->getFriendsPosts(user);
		vector<Post*> friendsOfFriendsContent = db->getFoFPosts(user);
		for (int i = 0; i < friendsOfFriendsContent.size(); i += 3) {
			friendsContent.push_back(friendsOfFriendsContent[i]);
		}
		Posts.buildHeap(friendsContent);

		if(!Posts.is_empty())
			current_post = Posts.extract();
	}

	Post* get_prev_post() {
		if(!prev_posts.empty())
			return prev_posts.top();
		return nullptr;
	}

	Post* get_current_post() {
		return current_post;
	}

	Post* get_next_post() {
		if (!Posts.is_empty())
			return Posts.peek();
		return nullptr;
	}

	void next() {
		if (!Posts.is_empty()) {
			if (current_post)
				prev_posts.push(current_post);
			current_post = Posts.extract();
		}		
	}

	void prev() {
		if (!prev_posts.empty()) {
			if (current_post)
				Posts.insert(current_post);
			current_post = prev_posts.top();
			prev_posts.pop();
		}
	}
	bool has_next() { 
		return !Posts.is_empty(); 
	}
	bool has_prev() const { 
		return !prev_posts.empty(); 
	}

	void setUser(User* _user) {
		user = _user;
	}
};




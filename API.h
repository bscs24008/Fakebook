#include "Database.h"
#include "FeedManager.h"
#include <chrono>
#include <ctime>

class API {
private:
	User* user;
	Database* db;
	FeedManager fm;
	
public:
	API(Database* _db) : db{ _db }, user{ nullptr }, fm{_db, nullptr} {}

	bool LoginEmail(const string& em, const string& pswrd) {
		user = db->getUserEmail(em, pswrd);
		if (!user)
			return false;
		fm.setUser(user);
		fm.refreshFeed();
		return true;

	}
	bool LoginUsername(const string& un, const string& pswrd) {
		user = db->getUserUsername(un, pswrd);
		if (!user)
			return false;
		fm.setUser(user);
		fm.refreshFeed();
		return true;
	}

	bool SignUp(const string& un, const string& e,
		const string& pswrd, const string& loc, const string& gen,
		int age, const bool& _status, string profile_pic) {
		return db->addUser(un, e, pswrd, loc, gen, age, _status, profile_pic);
	}

	void DeleteAccount() {
		if (user) {
			db->removeUser(user);
		}
	}

	PublicData getPublicData() {
		if (user)
			return user->getPublicData();
	}

	Post* get_current_post() {
		if (user) {
			return fm.get_current_post();
		}
	}
	Post* get_prev_post() {
		if (user) {
			return fm.get_prev_post();
		}
	}
	Post* get_next_post() {
		if (user) {
			return fm.get_next_post();
		}
	}
	void scroll_down() {
		if (user)
			fm.next();
	}
	void scroll_up() {
		if (user)
			fm.prev();
	}
	
	void create_post(string text, string url) {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		if (user)
			user->add_post(text, now_time, url);
	}
	void delete_post(Post* p) {
		if (user) {
			user->delete_post(p);
		}
	}

	vector<Post*> get_User_posts() {
		if (user)
			return user->getPosts();
	}

	vector<PublicData> get_friends_list() {
		if (user) {
			return db->getFriendsList(user);
		}
	}

	PublicData searchUser(string un) {
		if (user)
			return db->searchUserUsername(un);
	}
};








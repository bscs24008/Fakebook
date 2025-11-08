#pragma once
#include "User.h"
#include "FriendNetwork.h"
#include "Post.h"
#include <vector>
#include <algorithm>

class Database {
private:
    FriendNetwork network;
    vector<User*> users; // this should be sorted according to names

    User* find_username(const string& un) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i]->getusername() == un)
                return users[i];
        }
        return nullptr;
    }
    User* find_email(const string& e) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i]->getemail() == e)
                return users[i];
        }
        return nullptr;
    }
    bool check_availability(const string& un, const string& e) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i]->getusername() == un || users[i]->getemail() == e)
                return false;
        }
        return true;
    }
    bool check_pswrd(User* usr, string pswrd){
        return usr->check_pswrd(pswrd);
    }
    bool authUserUsername(const string& un, const string& pswrd, User*& usr) {
        User* u = find_username(un);
        if (u && u->check_pswrd(pswrd)) {
            usr = u;
            return true;
        }
        return false;
    }
    bool authUserEmail(const string& e, const string& pswrd, User*& usr) {
        User* u = find_email(e);
        if (u && u->check_pswrd(pswrd)) {
            usr = u;
            return true;
        }
        return false;
    }
    FriendNode* getfriendshead(User* usr) {
        return network.getfriendshead(usr);
    }
    friend class DummyDataGenerator;
public:

    bool addUser(const string& un, const string& e,
        const string& pswrd, const string& loc, const string& gen,
        int age, const bool& _status, string profile_pic) { 

        if (check_availability(un, e)) {
            auto position = lower_bound(users.begin(), users.end(), un, [](User* p1, const string& p2) { return p1->getusername() < p2; });
            User* usr = new User(un, pswrd, e, loc, gen, age, _status, profile_pic);
            users.insert(position, usr);
            network.add_user(usr);
            return true;
        }
        return false;
    }
    void removeUser(User* usr) {
        network.delete_user(usr);
        auto it = find(users.begin(), users.end(), usr);
        if (it != users.end())
            users.erase(it);
    }
    User* isUser(const string& name) {
        return find_username(name);
    }
    User* getUserUsername(const string& un, const string& pswrd) {
        User* usr = nullptr;
        authUserUsername(un, pswrd, usr);
        return usr;
    }
    User* getUserEmail(const string& un, const string& pswrd) {
        User* usr = nullptr;
        authUserEmail(un, pswrd, usr);
        return usr;
    }

    void addFriendship(User* usr1, User* usr2) { 
        network.add_friendship(usr1, usr2);
    }
    void removeFriendship(User* usr1, User* usr2) { 
        network.delete_friendship(usr1, usr2);
    }
    vector<Post*> getFriendsPosts(User* usr) {
        vector<Post*> posts;
        FriendNode* head = network.getfriendshead(usr);
        while (head) {
            int s = head->friendUser->getPosts().size();
            for (int i = 0; i < s; i++) {
                posts.push_back(head->friendUser->getPosts()[i]);
            }
            head = head->next;
        }
        return posts;
    }
    vector<Post*> getFoFPosts(User* usr) {  
        vector<Post*> posts;
        FriendNode* head1 = network.getfriendshead(usr);
        while (head1) {
            FriendNode* head2 = network.getfriendshead(head1->friendUser);
            while (head2) {
                if (!head2->friendUser->get_status()) {
                    head2 = head2->next;
                    continue;
                }
                int s = head2->friendUser->getPosts().size();
                for (int i = 0; i < s; i++) {
                    posts.push_back(head2->friendUser->getPosts()[i]);
                }
                head2 = head2->next;
            }
            head1 = head1->next;
        }
        return posts;
    }
    vector<PublicData> getFriendsList(User* usr) {
        vector<PublicData> v;
        FriendNode* head = network.getfriendshead(usr);
        while (head) {
            v.push_back(PublicData(head->friendUser->getusername(),
                head->friendUser->get_profile_pic(), head->friendUser->get_status(),
                head->friendUser->getPosts()));
            head = head->next;
        }
        return v;
    }
    PublicData searchUserUsername(string un) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i]->getusername() == un) {
                if (users[i]->get_status()) {
                    return PublicData(users[i]->getusername(), users[i]->get_profile_pic(),
                        users[i]->get_status(), users[i]->getPosts());
                }
                return PublicData(users[i]->getusername(), users[i]->get_profile_pic(),
                    users[i]->get_status(), vector<Post*>());
            }
        }
        return PublicData();
    }
    //void Save_to_file(const string& usersFile, const string& locationsFile, const string& postsFile)
    //{

    //}
    ~Database() { 
        for (auto i = 0; i < users.size(); i++)
            delete users[i];
    }
};



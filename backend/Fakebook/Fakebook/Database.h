#pragma once
#include "User.h"
#include "FriendNetwork.h"
#include "Post.h"
#include <vector>
#include <algorithm>

class Database {
private:
    FriendNetwork network;
    vector<User*> users;

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
        network.getfriendshead(usr);
    }
    friend class DummyDataGenerator;
public:

    void addUser(const string& un, const string& e,
        const string& pswrd, const string& loc, const string& gen,
        int age, const bool& _status) { 
        if (check_availability(un, e)) {
            User* usr = new User(un, pswrd, e, loc, gen, age, _status);
            users.push_back(usr);
            network.add_user(usr);
        }
    }
    void removeUser(User* usr) {
        network.delete_user(usr);
        auto it = find(users.begin(), users.end(), usr);
        if (it != users.end())
            users.erase(it);
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
    ~Database() { 
        for (auto i = 0; i < users.size(); i++)
            delete users[i];
    }
};



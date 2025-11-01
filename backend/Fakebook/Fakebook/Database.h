#pragma once

#include "User.h"
#include "FriendNetwork.h"

class Post;

class Database {
private:
    FriendNetwork network;
    vector<User*> users;

    User* find_username(const string& un) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i]->username == un)
                return users[i];
        }
        return nullptr;
    }
    User* find_email(const string& e) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i]->email == e)
                return users[i];
        }
        return nullptr;
    }
    bool check_availability(const string& un, const string& e) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i]->username == un || users[i]->email == email)
                return false;
        }
        return true;
    }
    bool check_pswrd(User* usr, string pswrd){
        return usr->check_pswrd(pswrd);
    }
    bool authUserUsername(const string& un, const string& pswrd, User*& usr) {
        User* u = find_username(un);
        if (usr->check_pswrd(pswrd)) {
            usr = u;
            return true;
        }
        return false;
    }
    bool authUserEmail(const string& e, const string& pswrd, User*& usr) {
        User* u = find_email(e);
        if (usr->check_pswrd(pswrd)) {
            usr = u;
            return true;
        }
        return false;
    }

public:

    void addUser(const string& un, const string& e,
        const string& pswrd, const string& loc, const string& gen
        int string& age, const bool& _status) { 
        if (check_availability()) {
            User* usr = new User(un, pswrd, e, loc, gen, age, _status);
            users.pushback(usr);
            network.add_user(usr);
        }
    }
    void removeUser(User* usr) {
        network.delete_user(usr);
        auto it = find(users.begin(), users.end(), usr);
        if (it != v.end())
            v.erase(it);
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
    
    void addFriendship(const string& user1, const string& user2) { }
    void removeFriendship(const string& user1, const string& user2) { }
    void vector<User*> getFriends(const string& username) { }
    void ~Database() { }
};



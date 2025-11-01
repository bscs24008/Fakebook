#pragma once
#include "User.h"
#include <iostream>
using namespace std;

struct FriendNode {
    User* friendUser;
    FriendNode* next;
    FriendNode* prev;
};

struct UserNode {
    User* user;
    FriendNode* friendsHead;
    FriendNode* friendsTail;
    UserNode* next;
    UserNode* prev;
};

class FriendNetwork {
private:
    UserNode* head;
    UserNode* tail;

    void add_to_friend_list(UserNode* owner, User* newFriend) {
        if (!owner || !newFriend) return;

        FriendNode* curr = owner->friendsHead;
        if (owner->user == newFriend)
            return;
        while (curr) {
            if (curr->friendUser == newFriend)
                return;
            curr = curr->next;
        }
        FriendNode* f = new FriendNode{ newFriend, nullptr, nullptr };
        if (!owner->friendsHead) {
            owner->friendsHead = owner->friendsTail = f;
        }
        else {
            owner->friendsTail->next = f;
            f->prev = owner->friendsTail;
            owner->friendsTail = f;
        }
    }

    void remove_from_friend_list(UserNode* owner, User* friendUser) {
        if (!owner || !friendUser) 
            return;
        FriendNode* curr = owner->friendsHead;
        while (curr) {
            if (curr->friendUser == friendUser) {
                if (curr->prev)
                    curr->prev->next = curr->next;
                else
                    owner->friendsHead = curr->next;

                if (curr->next)
                    curr->next->prev = curr->prev;
                else
                    owner->friendsTail = curr->prev;

                delete curr;
                return;
            }
            curr = curr->next;
        }
    }


public:
    FriendNetwork() : head(nullptr), tail(nullptr) {}

    void add_user(User* newUser) {
        UserNode* node = new UserNode{ newUser, nullptr, nullptr, nullptr, nullptr };
        if (!head) {
            head = tail = node;
        }
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
       
    UserNode* find_user(User* user) {
        UserNode* curr = head;
        while (curr) {
            if (curr->user == user) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    void add_friendship(User* user1, User* user2) {
        UserNode* u1 = find_user(user1);
        UserNode* u2 = find_user(user2);
        if (!u1 || !u2 || user1 == user2) return;

        add_to_friend_list(u1, user2);
        add_to_friend_list(u2, user1);
    }

    void delete_friendship(User* user1, User* user2) {
        UserNode* u1 = find_user(user1);
        UserNode* u2 = find_user(user2);
        if (!u1 || !u2) return;

        remove_from_friend_list(u1, user2);
        remove_from_friend_list(u2, user1);
    }

    void delete_user(User* user) {
        UserNode* target = find_user(user);
        if (!target) 
            return;

        UserNode* curr = head;
        while (curr) {
            if (curr->user != user)
                remove_from_friend_list(curr, user);
            curr = curr->next;
        }

        if (target->prev)
            target->prev->next = target->next;
        else
            head = target->next;

        if (target->next)
            target->next->prev = target->prev;
        else
            tail = target->prev;

        FriendNode* f = target->friendsHead;
        while (f) {
            FriendNode* t = f;
            f = f->next;
            delete t;
        }

        delete target;
    }

    void display() {
        UserNode* curr = head;
        while (curr) {
            cout << curr->user->getusername() << "'s friends: ";
            FriendNode* f = curr->friendsHead;
            while (f) {
                cout << f->friendUser->getusername() << " ";
                f = f->next;
            }
            cout << endl;
            curr = curr->next;
        }
    }

    ~FriendNetwork() {
        while (head) {
            UserNode* temp = head;
            head = head->next;

            FriendNode* f = temp->friendsHead;
            while (f) {
                FriendNode* t = f;
                f = f->next;
                delete t;
            }

            delete temp;
        }
    }
};

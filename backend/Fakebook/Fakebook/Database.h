class User;

struct FriendNode {
    User* friendUser;
    FriendNode* next; 
};

struct UserNode {
    User* user;       
    FriendNode* friendsHead; 
    UserNode* next;          
};

class Network {
private:
    UserNode* head;

public:
    Network() : head(nullptr) {}

    void add_user(User* newUser) {
        UserNode* node = new UserNode{ newUser, nullptr, nullptr };
        node->next = head;
        head = node;
    }

    UserNode* findUserNode(User* user) {
        UserNode* curr = head;
        while (curr) {
            if (curr->user == user) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    void delete_user(User* user) {
        UserNode* curr = head;
        while (curr) {
            if (curr->user != user)
                delete_friend(curr->user, user);
            curr = curr->next;
        }

        UserNode** ptr = &head;
        while (*ptr) {
            if ((*ptr)->user == user) {
                UserNode* temp = *ptr;
                *ptr = (*ptr)->next;

                FriendNode* f = temp->friendsHead;
                while (f) {
                    FriendNode* t = f;
                    f = f->next;
                    delete t;
                }
                delete temp->user;
                delete temp;
                return;
            }
            ptr = &((*ptr)->next);
        }
    }

    void add_friend(User* user, User* friendUser) {
        UserNode* uNode = findUserNode(user);
        UserNode* fNode = findUserNode(friendUser);
        if (!uNode || !fNode) return;

        FriendNode* f1 = new FriendNode{ friendUser, uNode->friendsHead };
        uNode->friendsHead = f1;

        FriendNode* f2 = new FriendNode{ user, fNode->friendsHead };
        fNode->friendsHead = f2;
    }

    void delete_friend(User* user, User* friendUser) {
        UserNode* uNode = findUserNode(user);
        UserNode* fNode = findUserNode(friendUser);
        if (!uNode || !fNode) return;

        FriendNode** curr = &uNode->friendsHead;
        while (*curr) {
            if ((*curr)->friendUser == friendUser) {
                FriendNode* temp = *curr;
                *curr = (*curr)->next;
                delete temp;
                break;
            }
            curr = &((*curr)->next);
        }

        curr = &fNode->friendsHead;
        while (*curr) {
            if ((*curr)->friendUser == user) {
                FriendNode* temp = *curr;
                *curr = (*curr)->next;
                delete temp;
                break;
            }
            curr = &((*curr)->next);
        }
    }

    void display() {
        UserNode* curr = head;
        while (curr) {
            std::cout << curr->user->username << "'s friends: ";
            FriendNode* f = curr->friendsHead;
            while (f) {
                std::cout << f->friendUser->username << " ";
                f = f->next;
            }
            std::cout << "\n";
            curr = curr->next;
        }
    }

    ~Network() {
        while (head) {
            UserNode* temp = head;
            head = head->next;

            FriendNode* f = temp->friendsHead;
            while (f) {
                FriendNode* t = f;
                f = f->next;
                delete t;
            }
            delete temp->user;
            delete temp;
        }
    }
};








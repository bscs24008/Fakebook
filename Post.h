#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

class Post {
private:
    string author;
    time_t timestamp;
    string text;
    string url;

public:
    Post(string _a, time_t _timestamp, string _t, string _u) {
        author = _a;
        timestamp = _timestamp;
        text = _t;
        url = _u;
    }

    string getText() { return text; }
    string getUrl() { return url; }
    time_t getTimeStamp() { return timestamp; }

    void setText(const string& _t) { text = _t; }
    void setUrl(const string& _u) { url = _u; }

    void display() {
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &timestamp);  

        cout << "Author: " << author << ", Time: " << buffer;
        cout << "Text: " << text << endl;
        cout << "Photo / Video: " << url << endl;
    }

    void saveToFile(const string& filename) {
        ofstream out(filename, ios::app);
        if (out.is_open()) {
            out << author << "#" << text << "#" << timestamp << "#" << url << endl;
        }
        out.close();
    }

    void readFromFile(const string& filename) {
        ifstream in(filename);
        if (!in.is_open()) return;

        getline(in, author, '#');
        getline(in, text, '#');
        string time;
        getline(in, time, '#');
        timestamp = stol(time);
        getline(in, url);
        in.close();
    }
};

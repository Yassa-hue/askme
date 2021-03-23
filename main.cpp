#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>
#include <cmath>
#include <map>
#include <iomanip>
#include <chrono>
#include <set>
#include <queue>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdio>
#include <stack>
#include <regex>
using namespace std;
#define ll long long int
#define pii pair<int, int>
#define psi pair<string, int>
#define pss pair<string, string>
#define vi vector <int>
#define vll vector <ll>
#define vd vector <double>
#define vs vector <string>
#define vpii vector <pii>
#define vpsi vector <psi>
#define vpss vector <pss>
#define ull unsigned long long
#define fff(itr, lim) for (int itr = 0; itr < int(lim); ++itr)
#define ffff(itr, lim) for (int itr = 1; itr <= int(lim); ++itr)
#define rrr(itr, lim) for (int itr = int(lim)-1; itr > -1; --itr)
const unsigned ll oo = 1e9 +5;
const int mx = 55;


struct reply {
    int id, user_id, question_id;
    string body;
    reply (int _id, int _user_id, int _question_id, string _body) {
        body = _body;
        user_id = _user_id;
        id = _id;
        question_id = _question_id;
    }
};


struct question {
    int id, user_id;
    string subject, body;
    vector<reply> replies;
    question(int _id, int _user_id, string _subject, string _body) {
        subject = _subject;
        body = _body;
        user_id = _user_id;
        id = _id;
    }
    ~question() {
//        fff(i, replies.size())
//            delete replies[i];
    }
};

struct user {
    int id;
    string name, email, password;
    vector <question> questions;
    user(){
        name = "not found";
        email = "undefined";
        password = "***";
        id = -1;
    }
    user(int _id, string _name, string _email, string _password) {
        name = _name;
        email = _email;
        password = _password;
        id = _id;
    }
    ~user() {
//        fff(i, questions.size())
//            delete questions[i];
    }
};


class contaner {
public:
    user user_on;
    contaner () {
        user_on = user();
        char c{};
        do {
            cout << "===================================================>>>>" << endl;
            cout << "q: quit\n" << ((user_on.id != -1) ?
            "f: myfeed\np: specific feed\na: add question\nr: reply to\nm: remove reply\nt: remove thred\ng: get all feed\no: log out"
            : "l: login\ns: sin up") << "\n>> ";
            cin >> c;
            if (user_on.id != -1) {
                if (c == 'f')
                    show_my_feed(1);
                else if (c == 'p')
                    show_my_feed(0);
                else if (c == 'a')
                    add_question();
                else if (c == 'g')
                    show_all_feed();
                else if (c == 'o')
                    logout();
                else if (c == 'r')
                    reply_to();
                else if (c == 'm')
                    remove_reply();
                else if (c == 't')
                    remove_thred();
            } else {
                if (c == 'l')
                    user_on = login();
                else if (c == 's')
                    user_on = sign_up();
            }
            cout << "===================================================>>>>" << endl;
        } while (c != 'q');
    }
    user login () {
        string email, password, name, line, _email, _password; int id;
        while (true) {
            cout << "inter your email & password ?> ";
            cin >> _email >> _password;
            ifstream users; users.open("files/users.txt");
            while (getline(users, line)) {
                istringstream str(line);
                str >> id >> name >> email >> password;
                if (email == _email && _password == password) {
                    user _on_user(id, name, email, password);
                    cout << "********************" << endl;
                    cout << "****you loged in****" << endl;
                    cout << "********************" << endl;
                    users.close();
                    return _on_user;
                }
            }
            users.close();
            cout << "Not found son of a bitch .. try fuckin' again" << endl;
        }
    }

    void logout () {
        user_on.id = -1;
        cout << "*********************" << endl;
        cout << "****you loged out****" << endl;
        cout << "*********************" << endl;
    }

    user sign_up () {
        string email, password, name, line, _email, _password; int id;
        cout << "inter your name, email & password ?> ";
        cin >> name >> email >> password;
        ifstream uid("files/user_id.txt"); uid >> id; uid.close();
        user _user_on(id, name, email, password);
        cout << "you are on ___ welcome :-)" << endl;
        fstream _uid("files/user_id.txt", (ios::out | ios::trunc)); _uid << id+1; _uid.close();
        ofstream users("files/users.txt", (ios::out | ios::app));
        users << _user_on.id << ' ' << _user_on.name << ' ' << _user_on.email << ' ' << _user_on.password << '\n';
        users.close();
        cout << _user_on.id << ' ' << _user_on.name << ' ' << _user_on.email << ' ' << _user_on.password << '\n';
        return _user_on;
    }

    void show_all_feed () {
        string line; ifstream questions("files/questions.txt");
        int q_id, r_id, u_id, in_q;
        while (getline(questions, line)) {
            cout << "+++----question-----+++" << endl;
            istringstream qu(line); qu >> q_id >> u_id;
            cout << ">>> q: " << line << endl;
            ifstream replies("files/replies.txt");
            cout << "-------replies--------" << endl;
            while (getline(replies, line)) {
                istringstream re(line); re >> r_id >> u_id >> in_q;
                if (in_q == q_id) cout << "> r: " << line << endl;
            }
            replies.close();
            cout << endl;
        }
        questions.close();
    }


    void show_my_feed (int f) {
        string line; ifstream questions("files/questions.txt");
        int q_id, r_id, u_id, in_q, _u_id;
        if (f == 0) { //spacific
            cout << "enter a user id ?> ";
            cin >> _u_id;
        } else _u_id = user_on.id;
        while (getline(questions, line)) {
            istringstream qu(line); qu >> q_id >> u_id;
            if (u_id == _u_id) {
                cout << "+++----question-----+++" << endl;
                cout << ">>> q: " << line << endl;
                ifstream replies("files/replies.txt");
                cout << "-------replies--------" << endl;
                while (getline(replies, line)) {
                    istringstream re(line); re >> r_id >> u_id >> in_q;
                    if (in_q == q_id) cout << "> r: " << line << endl;
                }
                replies.close();
            }
            cout << endl;
        }
        questions.close();
    }



    void add_question() {
        string q_sub, q_body;
        cout << "enter your question_subject & question_body ?> "; cin >> q_sub >> q_body;
        ofstream ques("files/questions.txt", (ios::out | ios::app)); int q_id;
        ifstream ques_id("files/question_id.txt"); ques_id >> q_id; ques_id.close();
        ques << q_id << ' ' << user_on.id << ' ' << q_sub << ' ' << q_body << '\n';
        ques.close();
        fstream _qid("files/question_id.txt", (ios::out | ios::trunc)); _qid << q_id+1; _qid.close();
        cout << "added q (" << q_id << ") : " << q_sub << endl;
    }

    void reply_to() {
        int q_id, r_id; ifstream id("files/reply_id.txt"); id >> r_id; id.close();
        string r_body;
        cout << "enter your question_id & question_reply ?> "; cin >> q_id >> r_body;
        ofstream replies("files/replies.txt", (ios::out | ios::app));
        replies << r_id << ' ' << user_on.id << ' ' << q_id << ' ' << r_body << '\n';
        replies.close();
        fstream _rid("files/reply_id.txt", (ios::out | ios::trunc)); _rid << r_id+1; _rid.close();
        cout << "+++----you added comment of id " << r_id << " to question id " << q_id << "-----+++" << endl;
    }


    void remove_reply() {
        int r_id, u_id, _id; string line; vector<string> reps;
        cout << "enter your reply id ?> "; cin >> r_id;
        ifstream replies("files/replies.txt");
        while (getline(replies, line)) {
            istringstream s(line); s >> _id >> u_id;
            if (_id == r_id) {
                if (u_id != user_on.id) {
                    cout << "*********************" << endl;
                    cout << "****not yours ;*)****" << endl;
                    cout << "*********************" << endl;
                    replies.close();
                    return;
                }
            } else reps.push_back(line);
        }
        replies.close();
        fstream _rid("files/replies.txt", (ios::out | ios::trunc));
        fff(i, reps.size()) {
            _rid << reps[i];
            _rid << '\n';
        }
        _rid.close();
        cout << "*****you removed reply " << r_id << "******" << endl;
    }



    void remove_thred() {
        int q_id, u_id, _id; string line; vector<string> ques;
        cout << "enter your thred id ?> "; cin >> q_id;
        ifstream questions("files/questions.txt");
        while (getline(questions, line)) {
            istringstream s(line); s >> _id >> u_id;
            if (_id == q_id) {
                if (u_id != user_on.id) {
                    cout << "*********************" << endl;
                    cout << "****not yours ;*)****" << endl;
                    cout << "*********************" << endl;
                    questions.close();
                    return;
                }
            } else ques.push_back(line);
        }
        questions.close();
        fstream _rid("files/questions.txt", (ios::out | ios::trunc));
        fff(i, ques.size()) {
            _rid << ques[i];
            _rid << '\n';
        }
        _rid.close();
        int _id_; ques.clear();
        ifstream replies("files/replies.txt");
        while (getline(replies, line)) {
            istringstream s(line); s >> _id >> u_id >> _id_;
            if (_id_ != q_id)  ques.push_back(line);
        }
        replies.close();
        fstream _rid_("files/replies.txt", (ios::out | ios::trunc));
        fff(i, ques.size()) {
            _rid_ << ques[i];
            _rid_ << '\n';
        }
        _rid_.close();

        cout << "*****you removed thred " << q_id << "******" << endl;
    }

};

int main() {
    cout << "                     welcome"  << endl;
    contaner st;
    return 0;
}

/*
 *
 * ifstream file; file.open("input.txt");
    vector<string> v;
    string line;
    while (getline(file, line)) {
        if (line[0] != 2)
            v.push_back(line);
    }
    file.close();
    string path2 {"input.txt"};
    fstream in(path2.c_str(), (ios::out | ios::trunc));
//    fstream in(path2.c_str(), (ios::in | ios::app | ios::out));
    cout << boolalpha << in.is_open() << endl;
    fff(i, v.size()) {
        cout << v[i] << endl;
        if (v[i][0] != '3')
            in << v[i] << '\n';
    }
    in.close();
 *
 *
 *
ifstream file; file.open("input.txt");
    vector<string> v;
    string line;
    while (getline(file, line)) {
        if (line[0] != 2)
            v.push_back(line);
    }
    file.close();
    ofstream in; in.open("input.txt", ios::out | ios::trunc);
    fff(i, v.size()) in << v[i] << '\n';
    in.close();
 *
 *
 *
string path1 {"input.txt"}, line, path2{"swap.txt"};
    fstream out(path1.c_str(), (ios::in | ios::app | ios::out));
    fstream in(path2.c_str(), (ios::in | ios::app | ios::out));
    while (getline(out, line)) {
        if (line[0] != '2')
            in << line << '\n';
    }
    out.close(); in.close();
    rename("input.txt", "swap_.txt");
    rename("swap.txt", "input.txt");
    rename("swap_.txt", "swap.txt");
 */

/*
    ifstream fin("input.txt"); ofstream fout("output.txt");
    freopen("./input.txt", "rt", stdin);
    freopen("./output.txt", "wt", stdout);
    string path {"input.txt"};
    fstream file(path.c_str(), (ios::in | ios::app | ios::out));
    cout << boolalpha << fin.is_open(); fin.close(); fout.close();
    freopen("input.txt","r", stdin);
    freopen("output.txt","w", stdout);
 */



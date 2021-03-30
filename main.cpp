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


string path_of(int id) {
    return ("files/" + to_string(id) + ".txt");
}



pss find(string &s) {
    int f;
    fff(i, s.length()){
        if (s[i] == ';'){
            f = i;
            break;
        }
    }
    return make_pair(s.substr(0, f), s.substr(f+2, s.length()-f-2));
}

void append_to (string path, vs &lines) {
    ofstream file(path, (ios::out | ios::app));
    fff(i, lines.size()) {
        file << lines[i];
        file << '\n';
    }
    file.close();
}

int get_id (string path) {
    int id;
    ifstream id_file(path); id_file >> id; id_file.close();
    fstream _uid(path, (ios::out | ios::trunc)); _uid << id+1; _uid.close();
    return id;
}


//bool remove_from(string _path, int pos, int _id, int _uid/*int _id, int pos, int _uid*/) {
//    ifstream file_to_in(_path); int id, uid; string line; vs lines;
//    while (getline(file_to_in, line)) {
//        istringstream s(line);
//        if (pos == 1) {
//            s >> id >> uid;
//            if (id == _id) {
//                if (uid != _uid) {
//                    cout << "*********************" << endl;
//                    cout << "****not yours ;*)****" << endl;
//                    cout << "*********************" << endl;
//                    file_to_in.close();
//                    return false;
//                }
//            } else {
//                lines.push_back(line);
//            }
//        } else {
//            fff(i, 3) s >> id;
//            if (id != _id) lines.push_back(line);
//        }
//    }
//    file_to_in.close();
//    fstream file_to_out(_path, (ios::out | ios::trunc));
//    fff(i, lines.size()) {
//        file_to_out << lines[i];
//        file_to_out << '\n';
//    }
//    file_to_out.close();
//    return true;
//}

bool belong_to(string path, int id, int u_id, bool skip_fr) {
    ifstream file(path);
    string line;
    int _id, _u_id;
    if (skip_fr) getline(file, line);
    while (getline(file, line)) {
        istringstream s(line); s >> _id >> _u_id;
        if (id == _id) {
            file.close();
            return (u_id == _u_id);
        }
    }
    if (file.is_open()) file.close();
    return false;
}


void remove_from(string path, int id, bool skip_fr) {
    ifstream file(path); string line; int _id; vs lines;
    if (skip_fr) {
        getline(file, line);
        lines.push_back(line);
    }
    while (getline(file, line)) {
        istringstream s(line); s >> _id;
        if (id != _id) lines.push_back(line);
    }
    file.close();
    fstream file_to_out(path, (ios::out | ios::trunc));
    fff(i, lines.size()) {
        file_to_out << lines[i];
        file_to_out << '\n';
    }
    file_to_out.close();
}



void put_to (string path, string line) {
    ofstream file(path);
    file << line;
    file << '\n';
    file.close();
}

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
    question() {
        id = -1;
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
    user(string _name, string _email, string _password) {
        name = _name;
        email = _email;
        password = _password;
    }
    void save() {
        id = get_id("files/user_id.txt");
        vs lines; string line;
        line = to_string(id) + ' ' + name + ' ' + email + ' ' + password;
        lines.push_back(line);
        append_to("files/users.txt", lines);
    }
    bool log_in(string _email, string _password) {
        ifstream file("files/users.txt"); string line;
        while (getline(file, line)) {
            istringstream str(line);
            str >> id >> name >> email >> password;
            if (email == _email && password == _password) return true;
        }
        return false;
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
            cout << "0: quit\n" << ((user_on.id != -1) ?
            "1: myfeed\n2: specific feed\n3: ask question\n4: reply to\n5: remove reply\n6: remove thred\n7: get all feed\n8: log out"
            : "1: log in\n2: sign up") << "\n>> ";
            cin >> c;
            if (user_on.id != -1) {
                if (c == '1')
                    show_my_feed(0);
                else if (c == '2')
                    show_my_feed(-1);
                else if (c == '3')
                    add_question();
                else if (c == '4')
                    reply_to();
                else if (c == '5')
                    remove_reply();
                else if (c == '6')
                    remove_thred();
                else if (c == '7')
                    show_all_feed();
                else if (c == '8')
                    logout();
            } else {
                if (c == '1')
                    user_on = login();
                else if (c == '2')
                    user_on = sign_up();
            }
            cout << "===================================================>>>>" << endl;
        } while (c != '0');
    }

private:

    user login () {
        string _email, _password;
        user _user_on;
        while (true) {
            cout << "inter your email & password ?> ";
            cin >> _email >> _password;
            if (_user_on.log_in(_email, _password)) {
                cout << "**>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                cout << "****hello " << _user_on.name << " your id is "  << _user_on.id << "****" << endl;
                cout << "**>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                return _user_on;
            }
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
        string email, password, name;
        cout << "inter your name, email & password ?> ";
        cin >> name >> email >> password;
        user _user_on(name, email, password);
        _user_on.save();
        cout << "**>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        cout << "****hello " << _user_on.name << " your id is "  << _user_on.id << "****" << endl;
        cout << "**>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        return _user_on;
    }

    void show_all_feed () {
        string line; ifstream questions("files/questions.txt");
        int q_id, u_id, ann;
        while (getline(questions, line)) {
            istringstream s(line); s >> q_id >> u_id >> ann;
            if (ann == 0 || u_id == user_on.id || ann == user_on.id) {
                ifstream ques(path_of(q_id)); getline(ques, line);
                cout << "+++----question-----+++" << endl;
                cout << ">>> " << line << endl;
                cout << "-------replies--------" << endl;
                while (getline(ques, line)) cout << "> " << line << endl;
                ques.close();
                cout << "\n\n" << endl;
            }
        }
        questions.close();
    }


    void show_my_feed (int f) {
        string line; ifstream questions("files/questions.txt");
        int q_id, u_id, _u_id;
        if (f == 0) _u_id = user_on.id;
        else {
            cout << "enter a user id ?> ";
            cin >> _u_id;
        }
        while (getline(questions, line)) {
            istringstream s(line); s >> q_id >> u_id;
            if (_u_id == u_id) {
                ifstream ques(path_of(q_id)); getline(ques, line);
                cout << "+++----question-----+++" << endl;
                cout << ">>> " << line << endl;
                cout << "-------replies--------" << endl;
                while (getline(ques, line)) cout << "> " << line << endl;
                ques.close();
                cout << "\n\n" << endl;
            }
        }
        questions.close();
//        string line; ifstream questions("files/questions.txt");
//        int q_id, r_id, u_id, in_q, _u_id;
//        if (f == 0) { //spacific
//            cout << "enter a user id ?> ";
//            cin >> _u_id;
//        } else _u_id = user_on.id;
//        while (getline(questions, line)) {
//            istringstream qu(line); qu >> q_id >> u_id;
//            if (u_id == _u_id) {
//                cout << "+++----question-----+++" << endl;
//                cout << ">>> q: " << line << endl;
//                ifstream replies("files/replies.txt");
//                cout << "-------replies--------" << endl;
//                while (getline(replies, line)) {
//                    istringstream re(line); re >> r_id >> u_id >> in_q;
//                    if (in_q == q_id) cout << "> r: " << line << endl;
//                }
//                replies.close();
//            }
//            cout << endl;
//        }
//        questions.close();
    }



    void add_question() {
        string ques, path; int id, ann;
        id = get_id("files/question_id.txt");
        cout << "enter id for ann 0 for all then your question_subject; question_body ?> ";
        cin >> ann;
        getline(cin, ques);
        vs lins; lins.push_back(to_string(id) + " " + to_string(user_on.id) + " " + to_string(ann));
        append_to("files/questions.txt", lins);
        ques = to_string(id) + " " + to_string(user_on.id) + " " + to_string(ann) + ' ' + ques;
        path = path_of(id);
        put_to(path, ques);
        cout << ">>>>> you added question of id " << id << " <<<<<<<" << endl;
    }

    void reply_to() {
        string rep; int id = get_id("files/reply_id.txt"), q_id;
        cout << "enter your question_id & question_reply ?> ";
        cin >> q_id;
        getline(cin, rep);
        vs lines; lines.push_back(to_string(id) + " " + to_string(user_on.id) + " " + to_string(q_id) + rep);
        rep = path_of(q_id);
        append_to(rep, lines);
        cout << "+++----you added comment of id " << id << " to question id " << q_id << "-----+++" << endl;
    }


    void remove_reply() {
        int r_id, q_id;
        cout << "to remove reply enter your question id & reply id ?> ";
        cin >> q_id >> r_id;
        string path = path_of(q_id);
        char c;
        if (belong_to(path, r_id, user_on.id, true)) {
            cout << "line 390 >> ";
            cin >> c;
            remove_from(path, r_id, true);
            cout << "*****you removed reply " << r_id << "******" << endl;
        } else {
            cout << "line 395 >> ";
            cin >> c;
            cout << "*********************" << endl;
            cout << "****not yours ;*)****" << endl;
            cout << "*********************" << endl;
        }
//        if (remove_from("files/replies.txt", 1, id, user_on.id))
//            cout << "*****you removed reply " << id << "******" << endl;

//        int id;
//        cout << "enter your reply id ?> "; cin >> id;
//        if (remove_from("files/replies.txt", 1, id, user_on.id))
//            cout << "*****you removed reply " << id << "******" << endl;
    }



    void remove_thred() {
        int q_id;
        cout << "enter your thred id ?> "; cin >> q_id;
        string path = path_of(q_id);
        if (belong_to("files/questions.txt", q_id, user_on.id, false)) {
            remove(path.c_str());
            remove_from("files/questions.txt", q_id, false);
            cout << "*****you removed thred " << q_id << "******" << endl;
        } else {
            cout << "*********************" << endl;
            cout << "****not yours ;*)****" << endl;
            cout << "*********************" << endl;
        }
//        int q_id;
//        cout << "enter your thred id ?> "; cin >> q_id;
//        if (remove_from("files/questions.txt", 1, q_id, user_on.id)) {
//            remove_from("files/replies.txt", 3, q_id, -1);
//            cout << "*****you removed thred " << q_id << "******" << endl;
//        }
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



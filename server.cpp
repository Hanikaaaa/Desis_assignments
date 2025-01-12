#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <unordered_map>
#include <fstream>
using namespace std;

vector<int> cl;
unordered_map<int, string> cn;
unordered_map<string, int> us;

void log_msg(const string &msg) {
    ofstream f("chat_history.txt", ios::app);
    f << msg << endl;
}

void handle_cl(int cs) {
    char buf[1024];
    
    send(cs, "Enter username: ", 17, 0);
    memset(buf, 0, sizeof(buf));
    recv(cs, buf, sizeof(buf), 0);
    string un = string(buf);
    cn[cs] = un;
    us[un] = cs;

    string wm = un + " joined!";
    log_msg(wm);

    for (int c : cl) {
        if (c != cs) {
            send(c, wm.c_str(), wm.length(), 0);
        }
    }

    while (true) {
        memset(buf, 0, sizeof(buf));
        int r = recv(cs, buf, sizeof(buf), 0);
        
        if (r == 0) {
            break;
        }
        
        string msg = string(buf);

        if (msg.substr(0, 4) == "/dm ") {
            size_t p = msg.find(' ', 4);
            string rec = msg.substr(4, p - 4);
            string dm = msg.substr(p + 1);

            if (us.find(rec) != us.end()) {
                int rs = us[rec];
                string dm_msg = "DM from " + un + ": " + dm;
                send(rs, dm_msg.c_str(), dm_msg.length(), 0);
                log_msg("DM from " + un + " to " + rec + ": " + dm);
            } else {
                string err = "User not found: " + rec;
                send(cs, err.c_str(), err.length(), 0);
            }
        } else {
            string brd_msg = un + ": " + msg;
            log_msg(brd_msg);
            for (int c : cl) {
                if (c != cs) {
                    send(c, brd_msg.c_str(), brd_msg.length(), 0);
                }
            }
        }
    }

    cn.erase(cs);
    us.erase(cn[cs]);
    close(cs);
}

int main() {
    int ss = socket(AF_INET, SOCK_STREAM, 0);  
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.s_addr = INADDR_ANY;
    bind(ss, (struct sockaddr*)&sa, sizeof(sa));
    listen(ss, 5);
    while (true) {
        int cs = accept(ss, nullptr, nullptr);
        cl.push_back(cs);
        thread(handle_cl, cs).detach();
    }

    close(ss);
    return 0;
}

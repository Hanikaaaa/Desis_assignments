#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <unordered_map>
using namespace std;

int cs;
string un;
unordered_map<string, int> users;  
void recv_msg() {
    char buf[1024];
    
    while (true) {
        memset(buf, 0, sizeof(buf));
        int r = recv(cs, buf, sizeof(buf), 0);
        
        if (r > 0) {
            cout << buf << endl;
        }
    }
}

void send_msg() {
    string msg;
    while (true) {
        cout << "> ";
        getline(cin, msg);
        if (msg.substr(0, 4) == "/dm ") {
            size_t space_pos = msg.find(' ', 4);
            if (space_pos != string::npos) {
                string recipient = msg.substr(4, space_pos - 4); 
                string dm_msg = msg.substr(space_pos + 1); 
                if (users.find(recipient) != users.end()) {
                    int recipient_socket = users[recipient];
                    string dm = "DM from " + un + ": " + dm_msg;
                    send(recipient_socket, dm.c_str(), dm.length(), 0);
                } else {
                    cout << "User not found: " << recipient << endl;
                }
            }
        } else {
            send(cs, msg.c_str(), msg.length(), 0);
        }
    }
}

void connect_to_svr() {
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.s_addr = INADDR_ANY;

    cs = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(cs, (struct sockaddr*)&sa, sizeof(sa)) < 0) {
        cerr << "Connection failed!" << endl;
        exit(1);
    }
    cout << "Enter username: ";
    cin >> un;
    cin.ignore();
    send(cs, un.c_str(), un.length(), 0);
    users[un] = cs;  
    thread(recv_msg).detach();
    send_msg();
}

int main() {
    connect_to_svr();
    
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    close(cs);
    return 0;
}

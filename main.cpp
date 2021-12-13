#include "Password.hpp"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    string choice1;
    string service;
    string username;
    string password;
    string notes;
    vector<Password> passwords;

    if (argc != 2) {
        cout << "usage: superlumic [password file]" << "\n";
        return 0;
    }

    ifstream infile(argv[1]);
    while (getline(infile, service)) {
        getline(infile, username);
        getline(infile, password);
        getline(infile, notes);
        passwords.push_back(Password(service, username, password, notes));
    }
    infile.close();

    while (choice1 != "q") {
        for (int i = 0; i < passwords.size(); i++) {
            cout << "Entry: " << i << "\n";
            cout << "Service: " << passwords[i].getService() << "\n";
            cout << "Username: " << passwords[i].getUsername() << "\n";
            cout << "Password: " << passwords[i].getPassword() << "\n";
            cout << "Notes: " << passwords[i].getNotes() << "\n";
            time_t edited = passwords[i].getEdited();
            cout << "Edited: " << put_time(localtime(&edited), "%Y-%m-%d %H:%M:%S") << "\n";
            cout << "\n";
        }
        cout << "[E]dit, [S]ave, [Q]uit: " << "\n";
        cin >> choice1;
        transform(choice1.begin(), choice1.end(), choice1.begin(), ::tolower);
    }
}

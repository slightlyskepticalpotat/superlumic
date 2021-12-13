#include "Password.hpp"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    string choice1;
    string choice2;
    string choice4;
    string service;
    string username;
    string password;
    string notes;
    string buffer;
    vector<Password> passwords;
    int choice3;

    if (argc < 2) {
        cout << "Creating new password file\n";
    } else {
        ifstream infile(argv[1]);
        getline(infile, buffer);
        if (buffer == "fhcreyhzvp") {
            while (getline(infile, service)) {
                getline(infile, username);
                getline(infile, password);
                getline(infile, notes);
                passwords.push_back(Password(service, username, password, notes));
            }
            cout << "Password file loaded\n";
        } else {
            cout << "Could not load file\n";
        }
        infile.close();
    }

    while (true) {
        cout << "--------------------------------------------------------------------------------\n";
        for (int i = 0; i < passwords.size(); i++) {
            cout << "Number: " << i << "\n";
            cout << "Service: " << passwords[i].getService() << "\n";
            cout << "Username: " << passwords[i].getUsername() << "\n";
            cout << "Password: " << passwords[i].getPassword() << "\n";
            cout << "Notes: " << passwords[i].getNotes() << "\n";
            time_t edited = passwords[i].getEdited();
            cout << "Edited: " << put_time(localtime(&edited), "%Y-%m-%d %H:%M:%S") << "\n";
            cout << "--------------------------------------------------------------------------------\n";
        }
        cout << "[E]dit, [S]ave, [Q]uit: \n";
        cin >> choice1;
        transform(choice1.begin(), choice1.end(), choice1.begin(), ::tolower);

        if (choice1 == "e") {
            cout << "[C]reate, [M]odify, [D]elete: \n";
            cin >> choice2;
            transform(choice2.begin(), choice2.end(), choice2.begin(), ::tolower);
            if (choice2 == "c") {
                cout << "Service: \n";
                cin >> service;
                cout << "Username: \n";
                cin >> username;
                cout << "Password: \n";
                cin >> password;
                cout << "Notes: \n";
                cin >> notes;
                passwords.push_back(Password(service, username, password, notes));
                cout << "Password created\n";
            } else if (choice2 == "m") {
                cout << "Number: \n";
                cin >> choice3;
                cout << "[S]ervice, [U]sername, [P]assword, [N]otes: \n";
                cin >> choice4;
                transform(choice4.begin(), choice4.end(), choice4.begin(), ::tolower);
                if (choice4 == "s" || choice4 == "u" || choice4 == "p" || choice4 == "n") {
                    if (choice4 == "s") {
                        cout << "Service: \n";
                        cin >> service;
                        passwords[choice3].setService(service);
                    } else if (choice4 == "u") {
                        cout << "Username: \n";
                        cin >> username;
                        passwords[choice3].setUsername(username);
                    } else if (choice4 == "p") {
                        cout << "Password: \n";
                        cin >> password;
                        passwords[choice3].setPassword(password);
                    } else if (choice4 == "n") {
                        cout << "Notes: \n";
                        cin >> notes;
                        passwords[choice3].setNotes(notes);
                    }
                    cout << "Password modified\n";
                } else {
                    cout << "Invalid operation\n";
                }
            } else if (choice2 == "d") {
                cout << "Number: \n";
                cin >> choice3;
                passwords.erase(passwords.begin() + choice3);
                cout << "Password deleted\n";
            } else {
                cout << "Invalid operation\n";
            }
        } else if (choice1 == "s") {
            cout << "Password file name: \n";
            cin >> choice2;
            ofstream outfile(choice2);
            outfile << "fhcreyhzvp\n";
            for (auto password: passwords) {
                outfile << password.getService() << "\n";
                outfile << password.getUsername() << "\n";
                outfile << password.getPassword() << "\n";
                outfile << password.getNotes() << "\n";
            }
            outfile.close();
            cout << "Password file saved\n";
        } else if (choice1 == "q") {
            return 0;
        } else {
            cout << "Invalid operation\n";
        }
    }
}

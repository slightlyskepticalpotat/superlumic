// Use CTR and AES-128
#define CTR 1
#define AES128 1

// Include needed headers
#include "Password.hpp"
#include "tiny-AES-c-master/aes.hpp"
#include "tiny-AES-c-master/aes.c"
#include <bits/stdc++.h>

using namespace std;

// Encryption and decryption helper
string aes_ctr(string plaintext, AES_ctx ctx) {
    vector<uint8_t> buffer;
    buffer.resize(plaintext.size());
    memcpy(buffer.data(), plaintext.data(), plaintext.size());
    AES_CTR_xcrypt_buffer(&ctx, buffer.data(), plaintext.size());
    return string((char *)buffer.data(), buffer.size());
}

int main(int argc, char *argv[]) {
    string choice1;
    string choice2;
    string choice4;
    string service;
    string username;
    string password;
    string notes;
    string signature;
    vector<Password> passwords;
    int choice3;
    uint8_t key[16] = {};
    uint8_t iv[16];
    char buffer;

    // todo: implement proper hkdf
    cout << "Password (max 16 characters):\n";
    cin >> key;
    struct AES_ctx ctx;

    // Load save if present
    if (argc < 2) {
        cout << "Creating new password file\n";
    } else {
        ifstream infile(argv[1]);
        getline(infile, signature);
        if (signature == "fhcreyhzvp") {
            // Get IV and restore AES
            for (int i = 0; i < 16; i++) {
                infile.get(buffer);
                iv[i] = buffer;
            }
            infile.get(buffer);
            AES_init_ctx_iv(&ctx, key, iv);
            // Decrypt the password file
            while (getline(infile, service)) {
                getline(infile, username);
                getline(infile, password);
                getline(infile, notes);
                passwords.push_back(Password(aes_ctr(service, ctx), aes_ctr(username, ctx), aes_ctr(password, ctx), aes_ctr(notes,ctx)));
            }
            cout << "Password file loaded\n";
        } else {
            cout << "Could not load file\n";
        }
        infile.close();
    }
    // Sets new random iv
    uniform_int_distribution<char> dist(0, 255);
    random_device urandom("/dev/urandom");
    for (int i = 0; i < 16; i++) {
        iv[i] = dist(urandom);
    }
    AES_init_ctx_iv(&ctx, key, iv);

    // Main program loop
    while (true) {
        // List each individual password
        cout << "--------------------------------------------------------------------------------\n";
        for (int i = 0; i < passwords.size(); i++) {
            cout << "Number: " << i << "\n";
            cout << "Service: " << passwords[i].getService() << "\n";
            cout << "Username: " << passwords[i].getUsername() << "\n";
            cout << "Password: " << passwords[i].getPassword() << "\n";
            cout << "Notes: " << passwords[i].getNotes() << "\n";
            // time_t edited = passwords[i].getEdited();
            // cout << "Edited: " << put_time(localtime(&edited), "%Y-%m-%d %H:%M:%S") << "\n";
            // time_t created = passwords[i].getCreated();
            // cout << "Created: " << put_time(localtime(&created), "%Y-%m-%d %H:%M:%S") << "\n";
            cout << "--------------------------------------------------------------------------------\n";
        }
        cout << "[E]dit, [S]ave, [Q]uit:\n";
        cin >> choice1;
        transform(choice1.begin(), choice1.end(), choice1.begin(), ::tolower);

        // Standard CRUD operations
        if (choice1 == "e") {
            cout << "[C]reate, [M]odify, [D]elete:\n";
            cin >> choice2;
            transform(choice2.begin(), choice2.end(), choice2.begin(), ::tolower);
            if (choice2 == "c") {
                cout << "Service:\n";
                cin >> service;
                cout << "Username:\n";
                cin >> username;
                cout << "Password:\n";
                cin >> password;
                cout << "Notes:\n";
                cin >> notes;
                passwords.push_back(Password(service, username, password, notes));
                cout << "Password created\n";
            } else if (choice2 == "m") {
                cout << "Number:\n";
                cin >> choice3;
                cout << "[S]ervice, [U]sername, [P]assword, [N]otes:\n";
                cin >> choice4;
                transform(choice4.begin(), choice4.end(), choice4.begin(), ::tolower);
                if (choice4 == "s" || choice4 == "u" || choice4 == "p" || choice4 == "n") {
                    if (choice4 == "s") {
                        cout << "Service:\n";
                        cin >> service;
                        passwords[choice3].setService(service);
                    } else if (choice4 == "u") {
                        cout << "Username:\n";
                        cin >> username;
                        passwords[choice3].setUsername(username);
                    } else if (choice4 == "p") {
                        cout << "Password:\n";
                        cin >> password;
                        passwords[choice3].setPassword(password);
                    } else if (choice4 == "n") {
                        cout << "Notes:\n";
                        cin >> notes;
                        passwords[choice3].setNotes(notes);
                    }
                    cout << "Password modified\n";
                } else {
                    cout << "Invalid operation\n";
                }
            } else if (choice2 == "d") {
                cout << "Number:\n";
                cin >> choice3;
                passwords.erase(passwords.begin() + choice3);
                cout << "Password deleted\n";
            } else {
                cout << "Invalid operation\n";
            }
        } else if (choice1 == "s") {
            cout << "Password file name:\n";
            cin >> choice2;
            ofstream outfile(choice2);
            // Store IV for next use
            outfile << "fhcreyhzvp\n";
            for (int i = 0; i < 16; i++) {
                outfile << iv[i];
            }
            outfile << "\n";
            // Encrypt saved passwords
            for (auto password: passwords) {
                outfile << aes_ctr(password.getService(), ctx) << "\n";
                outfile << aes_ctr(password.getUsername(), ctx) << "\n";
                outfile << aes_ctr(password.getPassword(), ctx) << "\n";
                outfile << aes_ctr(password.getNotes(), ctx) << "\n";
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

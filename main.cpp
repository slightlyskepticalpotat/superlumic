// Use CTR and AES-256
#define CTR 1
#define AES256 1

// Include needed headers
#include "Password.hpp"
#include "tiny-AES-c/aes.hpp"
#include "tiny-AES-c/aes.c"
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
    string choice3;
    string service;
    string username;
    string password;
    string notes;
    string signature;
    vector<Password> passwords;
    int number;
    uint8_t key[32] = {};
    uint8_t iv[16];
    char buffer;

    // todo: implement proper hkdf
    cout << "Password (max 32 characters)\n> ";
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
    #ifdef WINDOWS
        random_device urandom("rand_s");
    #else
        random_device urandom("/dev/urandom");
    #endif
    for (int i = 0; i < 16; i++) {
        iv[i] = dist(urandom);
    }
    AES_init_ctx_iv(&ctx, key, iv);

    while (true) {
        // List all individual passwords
        cout << "--------------------------------------------------------------------------------\n";
        for (int i = 0; i < passwords.size(); i++) {
            cout << "Number: " << i << "\n";
            cout << "Service: " << passwords[i].getService() << " | " << "Username: " << passwords[i].getUsername() << " | " << "Password: " << passwords[i].getPassword() << "\n";
            cout << "Notes: " << passwords[i].getNotes() << "\n";
            // time_t edited = passwords[i].getEdited();
            // cout << "Edited: " << put_time(localtime(&edited), "%Y-%m-%d %H:%M:%S") << "\n";
            cout << "--------------------------------------------------------------------------------\n";
        }
        cout << "[E]dit, [S]ave, [Q]uit\n> ";
        cin >> choice1;
        transform(choice1.begin(), choice1.end(), choice1.begin(), ::tolower);

        // Standard CRUD operations
        if (choice1 == "e") {
            cout << "[C]reate, [R]ead, [U]pdate, [D]elete, [S]hift\n> ";
            cin >> choice2;
            transform(choice2.begin(), choice2.end(), choice2.begin(), ::tolower);
            if (choice2 == "c") {
                cout << "Service\n> ";
                getline(cin >> ws, service);
                cout << "Username\n> ";
                getline(cin >> ws, username);
                cout << "Password\n> ";
                getline(cin >> ws, password);
                cout << "Notes\n> ";
                getline(cin >> ws, notes);
                passwords.push_back(Password(service, username, password, notes));
                cout << "Password created\n";
            } else if (choice2 == "u") {
                // Multi-platform screen clear
                #ifdef WINDOWS
                    system("cls");
                #else
                    system("clear");
                #endif
            } else if (choice2 == "u") {
                cout << "Number\n> ";
                cin >> number;
                cout << "[S]ervice, [U]sername, [P]assword, [N]otes\n> ";
                cin >> choice3;
                transform(choice3.begin(), choice3.end(), choice3.begin(), ::tolower);
                if (choice3 == "s" || choice3 == "u" || choice3 == "p" || choice3 == "n") {
                    if (choice3 == "s") {
                        cout << "Service\n> ";
                        cin >> service;
                        passwords[number].setService(service);
                    } else if (choice3 == "u") {
                        cout << "Username\n> ";
                        cin >> username;
                        passwords[number].setUsername(username);
                    } else if (choice3 == "p") {
                        cout << "Password\n> ";
                        cin >> password;
                        passwords[number].setPassword(password);
                    } else if (choice3 == "n") {
                        cout << "Notes\n> ";
                        cin >> notes;
                        passwords[number].setNotes(notes);
                    }
                    cout << "Password modified\n";
                } else {
                    cout << "Invalid operation\n";
                }
            } else if (choice2 == "d") {
                cout << "Number\n> ";
                cin >> number;
                passwords.erase(passwords.begin() + number);
                cout << "Password deleted\n";
            } else if (choice2 == "s") {
                cout << "Number\n> ";
                cin >> number;
                cout << "[U]p, [D]own\n> ";
                cin >> choice3;
                transform(choice3.begin(), choice3.end(), choice3.begin(), ::tolower);
                if (choice3 == "u" || choice3 == "d") {
                    if (choice3 == "u") {
                        if (&passwords[number] != &passwords.front()) {
                            swap(passwords[number], passwords[number - 1]);
                        }
                    } else if (choice3 == "d") {
                        if (&passwords[number] != &passwords.back()) {
                            swap(passwords[number], passwords[number + 1]);
                        }
                    }
                    cout << "Password shifted";
                } else {
                    cout << "Invalid operation\n";
                }
            } else {
                cout << "Invalid operation\n";
            }
        } else if (choice1 == "s") {
            cout << "Password file name\n> ";
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
                outfile << aes_ctr(password.getService(), ctx) << "\n" << aes_ctr(password.getUsername(), ctx) << "\n" << aes_ctr(password.getPassword(), ctx) << "\n" << aes_ctr(password.getNotes(), ctx) << "\n";
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

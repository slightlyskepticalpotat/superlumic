#include "Password.hpp"
#include <bits/stdc++.h>

using namespace std;

Password::Password(string newType, string newService, string newUsername, string newPassword, string newNote) {
    // type not currently exposed
    type = newType;
    service = newService;
    username = newUsername;
    password = newPassword;
    note = newNote;
}

string Password::getType() {
    return type;
}

string Password::getService() {
    return service;
}

string Password::getUsername() {
    return username;
}

string Password::getPassword() {
    return password;
}

string Password::getNote() {
    return note;
}

void Password::setType(string newType) {
    type = newType;
}

void Password::setService(string newService) {
    service = newService;
}

void Password::setUsername(string newUsername) {
    password = newUsername;
}

void Password::setPassword(string newPassword) {
    password = newPassword;
}

void Password::setNote(string newNote) {
    note = newNote;
}

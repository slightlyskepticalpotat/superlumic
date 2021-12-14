#include "Password.hpp"
#include <bits/stdc++.h>

using namespace std;

Password::Password(string newService, string newUsername, string newPassword, string newNotes) {
    service = newService;
    username = newUsername;
    password = newPassword;
    notes = newNotes;
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

string Password::getNotes() {
    return notes;
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

void Password::setNotes(string newNotes) {
    notes = newNotes;
}

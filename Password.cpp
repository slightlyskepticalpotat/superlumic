#include "Password.hpp"
#include <bits/stdc++.h>

using namespace std;

Password::Password(string newService, string newUsername, string newPassword, string newNotes) {
    service = newService;
    username = newUsername;
    password = newPassword;
    notes = newNotes;
    edited = time(NULL);
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

time_t Password::getEdited() {
    return edited;
}

void Password::setService(string newService) {
    service = newService;
    edited = time(NULL);
}

void Password::setUsername(string newUsername) {
    password = newUsername;
    edited = time(NULL);
}

void Password::setPassword(string newPassword) {
    password = newPassword;
    edited = time(NULL);
}

void Password::setNotes(string newNotes) {
    notes = newNotes;
    edited = time(NULL);
}

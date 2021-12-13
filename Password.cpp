#include "Password.hpp"
#include <bits/stdc++.h>

using namespace std;

Password::Password(string newService, string newPassword, string newNotes) {
    service = newService;
    password = newPassword;
    notes = newNotes;
    created = time(NULL);
    modified = time(NULL);
}

string Password::getService() {
    return service;
}

string Password::getPassword() {
    return password;
}

string Password::getNotes() {
    return notes;
}

time_t Password::getCreated() {
    return created;
}

time_t Password::getModified() {
    return modified;
}

void Password::setService(string newService) {
    service = newService;
    modified = time(NULL);
}

void Password::setPassword(string newPassword) {
    password = newPassword;
    modified = time(NULL);
}

void Password::setNotes(string newNotes) {
    notes = newNotes;
    modified = time(NULL);
}

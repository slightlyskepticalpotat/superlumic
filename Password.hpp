#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <bits/stdc++.h>

class Password {
    private:
        std::string service;
        std::string username;
        std::string password;
        std::string notes;
    public:
        Password(std::string newService, std::string newUsername, std::string newPassword, std::string newNotes);
        std::string getService();
        std::string getUsername();
        std::string getPassword();
        std::string getNotes();
        void setService(std::string newService);
        void setUsername(std::string setUsername);
        void setPassword(std::string newPassword);
        void setNotes(std::string newNotes);
};

#endif

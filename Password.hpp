#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <bits/stdc++.h>

class Password {
    private:
        std::string type;
        std::string service;
        std::string username;
        std::string password;
        std::string note;
    public:
        Password(std::string newType, std::string newService, std::string newUsername, std::string newPassword, std::string newNote);
        std::string getType();
        std::string getService();
        std::string getUsername();
        std::string getPassword();
        std::string getNote();
        void setType(std::string newType);
        void setService(std::string newService);
        void setUsername(std::string setUsername);
        void setPassword(std::string newPassword);
        void setNote(std::string newNote);
};

#endif

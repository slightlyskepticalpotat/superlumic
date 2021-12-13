#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <bits/stdc++.h>

class Password {
    private:
        std::string service;
        std::string password;
        std::string notes;
        time_t created;
        time_t modified;
    public:
        Password(std::string newService, std::string newPassword, std::string newNotes);
        std::string getService();
        std::string getPassword();
        std::string getNotes();
        time_t getCreated();
        time_t getModified();
        void setService(std::string newService);
        void setPassword(std::string newPassword);
        void setNotes(std::string newNotes);
};

#endif

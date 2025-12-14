#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include <fstream>
using namespace std;

class Admin {
private:
    string username;
    string password;

public:
    Admin();
    Admin(string user, string pass);
    bool login(string user, string pass);
    string getUsername() const;
    void save(ofstream& out) const;
};

#endif
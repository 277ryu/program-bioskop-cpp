#include "admin.h"
#include <fstream>
#include <string>
using namespace std;

Admin::Admin() {
    username = "";
    password = "";
}

Admin::Admin(string user, string pass) {
    username = user;
    password = pass;
}

bool Admin::login(string user, string pass) {
    return (username == user && password == pass);
}

string Admin::getUsername() const {
    return username;
}

void Admin::save(ofstream& out) const {
    out << username << endl;
    out << password << endl;
}



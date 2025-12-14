#ifndef MEMBER_H
#define MEMBER_H
#include <fstream>
#include <string>
using namespace std;

class Member {
private:
    string username;
    string password;
    double saldo;

public:
    Member();
    Member(string user,string pass, double sal);
    bool login(string user, string pass);
    void addSaldo(double amount);
    bool beliTiket(double price);
    double getSaldo() const;
    string getUsername() const;
    void save(ofstream& out) const;
};

#endif
#include "member.h"
#include <iostream>
using namespace std;

Member::Member() {
    username = "";
    password = "";
    saldo = 0.0;
}

Member::Member(string user,string pass, double sal) {
    username = user;
    password = pass;
    saldo = sal;
}

bool Member::login(string user, string pass) {
    return (username == user && password == pass);
}


void Member::addSaldo(double amount) {
    saldo += amount;
    cout << "\nSaldo berhasil ditambahkan!" << endl;
    cout << "Saldo saat ini: " << saldo << endl;
}

bool Member::beliTiket(double price) {
    double finalPrice = price;
    
    if (saldo >= finalPrice) {
        saldo -= finalPrice;
        cout << "Berhasil membeli tiket! Saldo tersisa: " << saldo << endl;
        return true;
    } else {
        cout << "Saldo tidak mencukupi! Butuh: " << finalPrice << ", Saldo Anda: " << saldo << endl;
        return false;
    }
}

double Member::getSaldo() const {
    return saldo;
}

string Member::getUsername() const {
    return username;
}

void Member::save(ofstream& out) const {
    out << username << endl;
    out << password << endl;
    out << saldo << endl;
}
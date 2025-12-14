#ifndef BIOSKOP_H
#define BIOSKOP_H
#include <string>
#include <vector>
#include <fstream>
#include "member.h"
#include "admin.h"
#include "film.h"
using namespace std;

class Bioskop {
private:
    vector<Film> movies;
    vector<Member> members;
    Admin admin;

public:
    // Konstruktor
    Bioskop();
    void loadData();
    void saveData();
    void buatStruk(const string &type, const string &content);
    
    // Fungsi admin
    void tambahFilm();
    void hapusFilm();
    void listFilm();
    void listMember();
    void hapusMember();
    void setHargaTiket();
    
    // Fungsi member
    void registerMember();
    void addMember(const string &username, const string &password, double saldo);
    Member* cariMember(string username);
    Film* cariFilm(int filmID);
    void buyTicketProcess(Member* Member);
    
    // Admin getter
    Admin* getAdmin();
};

#endif

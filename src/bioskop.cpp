#include "bioskop.h"
#include <iostream>
#include <fstream> // untuk file input/output
#include <iomanip> // untuk manipulasi output
#include <limits> // untuk numeric_limits
#include <algorithm> // untuk remove_if
using namespace std;

// Konstruktor Bioskop
Bioskop::Bioskop() : admin("friz", "friz123") {}

// Getter untuk Admin
Admin* Bioskop::getAdmin() {
    return &admin;
}
// Load data dari file input.txt
void Bioskop::loadData() {
    ifstream file("data/input.txt");
    if (!file.is_open()) {
        cout << "File data tidak ditemukan." << endl;
        return;
    }

    movies.clear();
    members.clear();

    string line;

    // Parsing
    // ==== MOVIES =====
    auto getline_nonempty = [&](string &out) -> bool {
        while (getline(file, out)) {
            if (!out.empty()) return true;
        }
        return false;
    };

    getline_nonempty(line);
    while (getline_nonempty(line)) {
        if (line == "=== MEMBERS ===") break;

        Film film;
        try {
            film.filmID = stoi(line);
        } catch (...) {
            continue;
        }

        // judul
        if (!getline_nonempty(film.judul)) break;
        if (film.judul == "=== MEMBERS ===") break;

        // genre
        if (!getline_nonempty(film.genre)) break;
        if (film.genre == "=== MEMBERS ===") break;

        // durasi
        if (!getline_nonempty(line)) break;
        try {
            film.durasi = stoi(line);
        } catch (...) {
            continue;
        }

        // harga tiket
        if (!getline_nonempty(line)) break;
        try {
            film.hargaTiket = stod(line);
        } catch (...) {
            continue;
        }

        movies.push_back(film);
    }

    // ===== MEMBERS =====
    while (getline_nonempty(line)) {
        if (line == "=== ADMIN ===") break;

        string username = line;
        string password;
        double saldo = 0.0;

        if (!getline_nonempty(password)) break;
        if (password == "=== ADMIN ===") break;

        if (!getline_nonempty(line)) break;
        try {
            saldo = stod(line);
        } catch (...) {
            saldo = 0.0;
        }

        members.emplace_back(username, password, saldo);
    }

    // ===== ADMIN =====
    string adminUser, adminPass;
    getline(file, adminUser);
    getline(file, adminPass);

    admin = Admin(adminUser, adminPass);

    file.close();
    cout << "Data berhasil dimuat dari input.txt." << endl;
}

// Fungsi save data ke file input.txt (persistent storage)
void Bioskop::saveData() {
    ofstream file("data/input.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan data." << endl;
        return;
    }

    // ===== MOVIES =====
    file << "=== MOVIES ===" << endl;
    for (const auto& film : movies) {
        file << film.filmID << endl;
        file << film.judul << endl;
        file << film.genre << endl;
        file << film.durasi << endl;
        file << film.hargaTiket << endl;
    }

    // ===== MEMBERS =====
    file << "=== MEMBERS ===" << endl;
    for (const auto& member : members) {
        member.save(file);
    }

    // ===== ADMIN =====
    file << "=== ADMIN ===" << endl;
    admin.save(file);

    file.close();
    cout << "Data berhasil disimpan ke input.txt." << endl;
}

// Membuat struk pembelian tiket ke output.txt
void Bioskop::buatStruk(const string &type, const string &content) {
    ofstream file("data/output.txt", ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan struk." << endl;
        return;
    }

    file << "\n===== STRUK " << type << " =====" << endl;
    file << content << endl;
    file << "===========================" << endl;

    file.close();
}

// Mencari member berdasarkan username
Member* Bioskop::cariMember(string username) {
    for (auto& member : members) {
        if (member.getUsername() == username) {
            return &member;
        }
    }
    return nullptr;
}

// Fungsi untuk mencari Film berdasarkan filmID
Film* Bioskop::cariFilm(int filmID) {
    for (auto& film : movies) {
        if (film.filmID == filmID) {
            return &film;
        }
    }
    return nullptr;
}

// Menampilkan daftar film dengan format tabel
void Bioskop::listFilm() {
    cout << "\n=== Daftar Film Absolute Cinema ===" << endl;
    cout << setw(5) << left << "ID" << " | " 
         << setw(25) << left << "Judul" << " | "
         << setw(20) << left << "Genre" << " | "
         << setw(15) << left << "Durasi (menit)" << " | "
         << "Harga" << endl;
    cout << string(85, '-') << endl;
    for (const auto& film : movies) {
        cout << setw(5) << left << film.filmID << " | " 
             << setw(25) << left << film.judul << " | "
             << setw(20) << left << film.genre << " | "
             << setw(15) << left << film.durasi << " | "
             << film.hargaTiket << endl;
    }
}

// Proses pembelian tiket oleh member
void Bioskop::buyTicketProcess(Member* member) {
    listFilm();
    int filmID;
    cout << "\nMasukkan ID film: ";
    cin >> filmID;

    Film* film = cariFilm(filmID);
    if (film) {
        cout << "Harga tiket untuk " << film->judul << " adalah " << film->hargaTiket << endl;
        if (member->beliTiket(film->hargaTiket)) {
            cout << "Tiket untuk " << film->judul << " berhasil dibeli!" << endl;
            
            // Generate struk ke output.txt
            string receipt = "Member: " + member->getUsername() + "\n";
            receipt += "Film: " + film->judul + "\n";
            receipt += "Harga: Rp" + to_string((long long)film->hargaTiket) + "\n";
            receipt += "Saldo tersisa: Rp" + to_string((long long)member->getSaldo());
            buatStruk("PEMBELIAN TIKET", receipt);
        } else {
            cout << "Gagal membeli tiket. Saldo tidak mencukupi." << endl;
        }
    } else {
        cout << "Film dengan ID tersebut tidak ditemukan." << endl;
    }
}

// Mendaftarkan member baru kalau belum ada di input.txt
void Bioskop::registerMember() {
    string username, password;
    double saldo;

    cout << "\n=== Registrasi Member Baru ===" << endl;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    cout << "Masukkan saldo awal: ";
    cin >> saldo;

    members.emplace_back(username, password, saldo);
    cout << "Registrasi berhasil! Selamat datang, " << username << "!" << endl;
}

void Bioskop::addMember(const string &username, const string &password, double saldo) {
    members.emplace_back(username, password, saldo);
}

// Menampilkan daftar member
void Bioskop::listMember() {
    cout << "\n=== Daftar Member Absolute Cinema ===" << endl;
    for (const auto& member : members) {
        cout << "Username: " << member.getUsername() 
             << ", Saldo: " << member.getSaldo() << endl;
    }
}

// Menghapus member berdasarkan username
void Bioskop::hapusMember() {
    string username;
    cout << "\nMasukkan username member yang akan dihapus: ";
    cin >> username;

    auto it = remove_if(members.begin(), members.end(), [&](const Member& member) {
        return member.getUsername() == username;
    });

    if (it != members.end()) {
        members.erase(it, members.end());
        cout << "Member dengan username " << username << " telah dihapus." << endl;
    } else {
        cout << "Member dengan username " << username << " tidak ditemukan." << endl;
    }
}

// Mengatur harga tiket film
void Bioskop::setHargaTiket() {
    listFilm();
    
    int filmID;
    double hargaTiket;
    cout << "\nMasukkan ID film yang ingin diubah harganya: ";
    cin >> filmID;
    
    Film* film = cariFilm(filmID);
    if (film) {
        cout << "Harga tiket saat ini: Rp" << film->hargaTiket << endl;
        cout << "Masukkan harga tiket baru: ";
        cin >> hargaTiket;
        film->hargaTiket = hargaTiket;
        cout << "Harga tiket untuk " << film->judul << " berhasil diubah menjadi Rp" << hargaTiket << "." << endl;
    } else {
        cout << "Film dengan ID " << filmID << " tidak ditemukan." << endl;
    }
}

// Menambahkan film baru
void Bioskop::tambahFilm() {
    Film film;
    cout << "ID Film: ";
    cin >> film.filmID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Judul: ";
    getline(cin, film.judul);
    cout << "Genre: ";
    getline(cin, film.genre);
    cout << "Durasi (menit): ";
    cin >> film.durasi;
    cout << "Harga tiket: ";
    cin >> film.hargaTiket;
    movies.push_back(film);
    cout << "Film berhasil ditambahkan!" << endl;
}

// Fungsi untuk menghapus film berdasarkan filmID
void Bioskop::hapusFilm() {
    int filmID;
    cout << "Masukkan ID film yang akan dihapus: ";
    cin >> filmID;

    auto it = remove_if(movies.begin(), movies.end(), [&](const Film& film) {
        return film.filmID == filmID;
    });

    if (it != movies.end()) {
        movies.erase(it, movies.end());
        cout << "Film dengan ID " << filmID << " telah dihapus." << endl;
    } else {
        cout << "Film dengan ID " << filmID << " tidak ditemukan." << endl;
    }
}


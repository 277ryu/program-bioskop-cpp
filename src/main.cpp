#include <iostream>
#include "bioskop.h"
using namespace std;

void adminMenu(Bioskop& cinema) {
    int choice;
    while (true) {
        cout << "\n========== MENU ADMIN ==========\n";
        cout << "1. Tambah Film\n";
        cout << "2. Hapus Film\n";
        cout << "3. Lihat Daftar Film\n";
        cout << "4. Lihat Daftar Member\n";
        cout << "5. Hapus Member\n";
        cout << "6. Ubah Harga Tiket\n";
        cout << "7. Logout\n";
        cout << "================================\n";
        cout << "Pilihan: ";
        cin >> choice;
        
        switch (choice) {
            case 1: cinema.tambahFilm(); break;
            case 2: cinema.hapusFilm(); break;
            case 3: cinema.listFilm(); break;
            case 4: cinema.listMember(); break;
            case 5: cinema.hapusMember(); break;
            case 6: cinema.setHargaTiket(); break;
            case 7: 
                cout << "\n>>> Logout berhasil!\n";
                return;
            default: 
                cout << "\n>>> Pilihan tidak valid!\n";
        }
    }
}

void memberMenu(Bioskop& cinema, Member* member) {
    int choice;
    
    while (true) {
        cout << "\n========== MENU PELANGGAN ==========\n";
        cout << "Username: " << member->getUsername() << endl;
        cout << "Saldo: Rp " << member->getSaldo() << endl;
        cout << "===================================\n";
        cout << "1. Lihat Daftar Film\n";
        cout << "2. Beli Tiket\n";
        cout << "3. Tambah Saldo\n";
        cout << "4. Logout\n";
        cout << "===================================\n";
        cout << "Pilihan: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cinema.listFilm();
                break;
            case 2:
                cinema.buyTicketProcess(member);
                break;
            case 3: {
                double amount;
                cout << "\nJumlah saldo (Rp): ";
                cin >> amount;
                member->addSaldo(amount);
                break;
            }
            case 4:
                cout << "\n>>> Logout berhasil!\n";
                return;
            default: 
                cout << "\n>>> Pilihan tidak valid!\n";
        }
    }
}

// Fungsi main
int main() {
    Bioskop cinema;
    cinema.loadData();
    
    int mainChoice;
    
    while (true) {
        cout << "\n";
        cout << "==========================================" << endl;
        cout << "    SELAMAT DATANG DI ABSOLUTE CINEMA" << endl;
        cout << "=========================================="<< endl;
        cout << "Masuk sebagai?"<< endl;
        cout << "1. Admin" << endl;
        cout << "2. Member" << endl;
        cout << "3. Keluar" << endl;
        cout << "=========================================="<< endl;
        cout << "Pilihan: ";
        cin >> mainChoice;
        
        if (mainChoice == 1) {
            string username, password;
            cout << "\n========== LOGIN MENU: ADMIN ==========\n";
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            
            if (cinema.getAdmin()->login(username, password)) {
                cout << "\n>>> Selamat datang Admin " << username << "!\n";
                adminMenu(cinema);
            } else {
                cout << "\n>>> Username atau password salah!\n";
            }
            
        } else if (mainChoice == 2) {
            {
                string username, password;
                cout << "\n========== LOGIN MENU: MEMBER =========="<< endl;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                Member* member = cinema.cariMember(username);
                if (member != nullptr) {
                    if (member->login(username, password)) {
                        cout << ">>> Selamat datang " << username << "!\n";
                        memberMenu(cinema, member);
                    } else {
                        cout << ">>> Password salah!" << endl;
                    }
                } else {
                    cout << ">>> Username tidak ditemukan. Buat akun baru dengan username ini? (y/n): ";
                    char ch; cin >> ch;
                    if (ch == 'y' || ch == 'Y') {
                        double saldo = 0.0;
                        cout << "Masukkan saldo awal: ";
                        cin >> saldo;
                        cinema.addMember(username, password, saldo);
                        Member* newMember = cinema.cariMember(username);
                        if (newMember) {
                            cout << ">>> Akun berhasil dibuat. Selamat datang " << username << "!\n";
                            memberMenu(cinema, newMember);
                        }
                    } else {
                        cout << ">>> Pembuatan akun dibatalkan." << endl;
                    }
                }
            }
            
        } else if (mainChoice == 3) {
            cinema.saveData();
            cout << "\n>>> Terima kasih telah menggunakan sistem bioskop Absolute Cinema!\n";
            cout << ">>> Sampai jumpa!\n\n";
            break;
            
        } else {
            cout << "\n>>> Pilihan tidak valid!\n";
        }
    }
    
    return 0;
}

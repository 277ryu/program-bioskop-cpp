# Program Bioskop (C++)
Pengembangan aplikasi pemesanan tiket bioskop yang dibuat menggunakan bahasa C++. <br/>
Proyek untuk mata kuliah Pemrograman Dasar di semester 1.

## 🛠️ Cara menjalankan
Compile dan jalankan program (Windows):
```bash
g++ -Iinclude .\src\admin.cpp .\src\bioskop.cpp .\src\main.cpp .\src\member.cpp -o cinema
.\cinema.exe
```

## 🔍 Fitur Program
### Admin
-  Tambah film (ID, judul, genre, durasi, harga tiket)
-  Hapus film berdasarkan ID
-  Lihat daftar film
-  Lihat daftar member
-  Hapus member berdasarkan username
-  Ubah harga tiket (berlaku untuk semua film)

### Member
-  Login dengan username & password
-  Buat akun baru otomatis saat login
-  Lihat daftar film
-  Beli tiket film
-  Tambah saldo

## 📁 Struktur File

```
program-bioskop-cpp/
├── data/
│   ├── input.txt
│   └── output.txt
├── include/
│   ├── admin.h
│   ├── bioskop.h
│   ├── film.h
│   └── member.h
├── src/
│   ├── admin.cpp
│   ├── bioskop.cpp
│   ├── main.cpp
│   └── member.cpp
├── cinema.exe
└── README.md
```

## 📄 Format File Data

### input.txt

```
=== MOVIES ===
1
Dead Poets Society
Drama
129
50000
2
Good Will Hunting
Drama
126
30000
...
=== MEMBERS ===
joni
joni67
350000
waltuh
walt66
150000
=== ADMIN ===
friz
friz123
```

### output.txt

```
===== STRUK PEMBELIAN TIKET =====
Member: joni
Film: Dead Poets Society
Harga: Rp50000
Saldo tersisa: Rp250000
===========================
```

## Techstack

- **Bahasa**            : C++
- **Code Editor**       : Visual Studio Code
- **Compiler**          : G++ via MSYS2 (MinGW-w64)
- **Sistem Operasi**    : Windows 11

---

**ABSOLUTE CINEMA**

> Muhammad Affriza Ayman Nashmi
> 25/559828/TK/63201

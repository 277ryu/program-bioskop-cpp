#ifndef FILM_H
#define FILM_H
#include <string>
#include <vector>
using namespace std;

struct Film {
    int filmID;
    string judul;
    string genre;
    int durasi; // dalam menit
    double hargaTiket;
};

#endif
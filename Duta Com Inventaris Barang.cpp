#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

struct Barang {
    string id, nama, tanggal;  
    int    jumlah;
    Barang* next{};
};

Barang* head = nullptr;     

bool validDate(const string& s) {
    if (s.size() != 10 || s[2] != '/' || s[5] != '/') return false;
    for (int i : {0,1,3,4,6,7,8,9})
        if (!isdigit(s[i])) return false;

    int dd = stoi(s.substr(0,2));
    int mm = stoi(s.substr(3,2));
    int yy = stoi(s.substr(6,4));
    return dd >= 1 && dd <= 31 && mm >= 1 && mm <= 12 &&
           yy >= 1900 && yy <= 2100;
}

int dateKey(const string& s) {
    return stoi(s.substr(6,4) + s.substr(3,2) + s.substr(0,2));
}


void tambahBarang() {
    Barang* node = new Barang();
    cout << "\n>> Tambah Barang Baru <<\n";
    cout << "ID Barang        : "; getline(cin, node->id);
    cout << "Nama Barang      : "; getline(cin, node->nama);
    cout << "Jumlah Barang    : "; cin >> node->jumlah; cin.ignore();

    string tgl;
    do {
        cout << "Tanggal Masuk (DD/MM/YYYY) : ";
        getline(cin, tgl);
        if (!validDate(tgl))
            cout << ">> Format salah! Cobalah lagi.\n";
    } while (!validDate(tgl));
    node->tanggal = tgl;

    if (!head) head = node;
    else {
        Barang* tail = head;
        while (tail->next) tail = tail->next;
        tail->next = node;
    }
    cout << ">> Barang berhasil ditambahkan!\n";
}

void headerTabel() {
    cout << left << setw(4) << "No" << setw(12) << "ID"
         << setw(20) << "Nama" << setw(7)  << "Qty"
         << "Tanggal" << '\n';
    cout << string(50,'-') << '\n';
}

void tampilkanBarang() {
    if (!head) { cout << "\n>> Tidak ada data barang.\n"; return; }
    cout << "\n>> Daftar Seluruh Barang (FIFO) <<\n";
    headerTabel();
    int no = 1;
    for (Barang* p=head; p; p=p->next)
        cout << setw(4)<<no++<<setw(12)<<p->id
             << setw(20)<<p->nama.substr(0,18)
             << setw(7) <<p->jumlah
             << p->tanggal << '\n';
}

void cariBarang() {
    string key;
    cout << "\n>> Cari Barang Berdasarkan ID <<\nMasukkan ID: ";
    getline(cin, key);
    for (Barang* p=head; p; p=p->next)
        if (p->id == key) {
            cout << "\n>> Barang ditemukan:\n"
                 << "   ID      : " << p->id << '\n'
                 << "   Nama    : " << p->nama << '\n'
                 << "   Jumlah  : " << p->jumlah << '\n'
                 << "   Tanggal : " << p->tanggal << '\n';
            return;
        }
    cout << "\n>> Barang tidak ditemukan.\n";
}

void hapusBarang() {
    string key;
    cout << "\n>> Hapus Barang Berdasarkan ID <<\nMasukkan ID: ";
    getline(cin, key);
    Barang *cur=head, *prev=nullptr;
    while (cur && cur->id != key) { prev = cur; cur = cur->next; }
    if (!cur) { cout << ">> Barang tidak ditemukan.\n"; return; }
    if (!prev) head = cur->next; else prev->next = cur->next;
    delete cur;
    cout << ">> Barang berhasil dihapus.\n";
}

void tampilUrutTanggal() {
    if (!head) { cout << "\n>> Tidak ada data barang.\n"; return; }


    vector<Barang*> v;
    for (Barang* p=head; p; p=p->next) v.push_back(p);
    sort(v.begin(), v.end(),
         [](Barang* a, Barang* b){ return dateKey(a->tanggal) < dateKey(b->tanggal); });

    cout << "\n>> Daftar Barang (Urut Tanggal Masuk) <<\n";
    headerTabel();
    for (size_t i=0;i<v.size();++i)
        cout << setw(4)<<i+1<<setw(12)<<v[i]->id
             << setw(20)<<v[i]->nama.substr(0,18)
             << setw(7) <<v[i]->jumlah
             << v[i]->tanggal << '\n';
}

void menuUtama() {
    int pil;
    do {
        cout << "\n================ MENU UTAMA ================\n"
             << "1. Tambah Barang Baru\n"
             << "2. Tampilkan Semua Data Barang\n"
             << "3. Cari Barang Berdasarkan ID\n"
             << "4. Tampilkan Berdasarkan Tanggal Masuk\n"
             << "5. Hapus Barang Berdasarkan ID\n"
             << "0. Keluar Aplikasi\n"
             << "============================================\n"
             << "Pilih menu (0-5): ";
        cin >> pil; cin.ignore();

        switch (pil) {
            case 1: tambahBarang();          break;
            case 2: tampilkanBarang();       break;
            case 3: cariBarang();            break;
            case 4: tampilUrutTanggal();     break;
            case 5: hapusBarang();           break;
            case 0: cout << "\n>> Terima kasih!\n"; break;
            default: cout << "\n>> Pilihan tidak valid.\n";
        }
    } while (pil != 0);
}

int main() {
    cout << "======================================================\n"
         << "===>> Selamat Datang di Sistem Inventaris Barang <<===\n"
         << "======================================================\n"
         << "            _____________________________\n"
         << "           |                             |\n"
         << "           |         DutaComputer        |\n"
         << "           |_____________________________|\n\n"
         << "======================================================\n"
         << "             Dibuat oleh Kelompok 4\n"
         << "======================================================\n"
         << "\nTekan ENTER untuk masuk ke Menu Utama...";

    cin.get();
    menuUtama();
    return 0;
}
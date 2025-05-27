#include <iostream>
#include <string>

using namespace std;
class MataKuliah {
public:
    string kode;
    string nama;
    int sks;
    string jadwal;
    char nilai;

    MataKuliah() {
        kode = "";
        nama = "";
        sks = 0;
        jadwal = "";
        nilai = '-';
    }
};

class Mahasiswa {
public:
    string nim;
    string username;
    string nama;
    string prodi;
    string fakultas;
    string MataKuliah krs;
    int jumlahKRS;
    bool beasiswa;
    string metodePembayaran;

    Mahasiswa() {
        nim = "";
        username = "";
        nama = "";
        prodi = "";
        fakultas = "";
        jumlahKRS = 0;
        beasiswa = false;
        metodePembayaran = "";
    }

    void tampilkanInfoPribadi() {
        cout << "\n=== Informasi Pribadi ===\n";
        cout << "NIM       : " << nim << "\n";
        cout << "Nama      : " << nama << "\n";
        cout << "Prodi     : " << prodi << "\n";
        cout << "Fakultas  : " << fakultas << "\n";
        cout << "Beasiswa  : " << (beasiswa ? "Ya" : "Tidak") << "\n";
    }

    bool sudahAmbilMatkul(string kode) {
        for(int i = 0; i < jumlahKRS; i++) {
            if(krs[i].kode == kode) return true;
        }
        return false;
    }

    void tambahMatkul(MataKuliah matkul) {
        if(jumlahKRS) {
            cout << "KRS sudah penuh, tidak dapat menambah mata kuliah.\n";
            return;
        }
        if(sudahAmbilMatkul(matkul.kode)) {
            cout << "Mata kuliah sudah diambil di KRS.\n";
            return;
        }
        krs[jumlahKRS++] = matkul;
        cout << "Mata kuliah " << matkul.nama << " berhasil ditambahkan ke KRS.\n";
    }

    void hapusMatkul(int index) {
        if(index < 0 || index >= jumlahKRS) {
            cout << "Index tidak valid.\n";
            return;
        }
        cout << "Mata kuliah " << krs[index].nama << " dihapus dari KRS.\n";
        for(int i = index; i < jumlahKRS - 1; i++) {
            krs[i] = krs[i+1];
        }
        jumlahKRS--;
    }

    void tampilkanKRS() {
        cout << "\n=== Kartu Rencana Studi (KRS) ===\n";
        if(jumlahKRS == 0) {
            cout << "Belum ada mata kuliah yang diambil.\n";
            return;
        }
        int totalSKS = 0;
        for(int i=0; i < jumlahKRS; i++) {
            cout << (i+1) << ". " << krs[i].kode << " - " << krs[i].nama << " (" << krs[i].sks << " SKS), Jadwal: " << krs[i].jadwal << "\n";
            totalSKS += krs[i].sks;
        }
        cout << "Total SKS: " << totalSKS << "\n";
    }

    void tampilkanJadwal() {
        cout << "\n=== Jadwal Kuliah ===\n";
        if(jumlahKRS == 0) {
            cout << "Belum ada mata kuliah yang diambil.\n";
            return;
        }
        for(int i=0; i < jumlahKRS; i++) {
            cout << krs[i].jadwal << " - " << krs[i].nama << "\n";
        }
    }

    void tampilkanNilai() {
        cout << "\n=== Nilai Mata Kuliah ===\n";
        if(jumlahKRS == 0) {
            cout << "Belum ada nilai karena belum mengambil mata kuliah.\n";
            return;
        }
        for(int i=0; i < jumlahKRS; i++) {
            cout << krs[i].kode << " - " << krs[i].nama << ": " << krs[i].nilai << "\n";
        }
    }

    void ajukanBeasiswa() {
        if(beasiswa) {
            cout << "Anda sudah mengajukan beasiswa.\n";
        } else {
            beasiswa = true;
            cout << "Pengajuan beasiswa berhasil. Anda akan mendapatkan potongan biaya SPP.\n";
        }
    }

    int hitungSPP() {
        int tarifPerSKS = 200000;
        int totalSKS = 0;
        for(int i=0; i < jumlahKRS; i++)
            totalSKS += krs[i].sks;
        int total = totalSKS * tarifPerSKS;
    
        return total;
    }

    void pembayaranSPP() {
        int pilih;
        cout << "\n=== Pembayaran SPP ===\n";
        cout << "Total biaya SPP (setelah potongan jika ada): Rp " << hitungSPP() << "\n";
        cout << "Pilih metode pembayaran:\n1. Transfer Bank\n2. Kartu Kredit\n3. Tunai\n";
        cout << "Pilihan: "; cin >> pilih;
        if(pilih == 1) metodePembayaran = "Transfer Bank";
        else if(pilih == 2) metodePembayaran = "Kartu Kredit";
        else if(pilih == 3) metodePembayaran = "Tunai";
        else {
            cout << "Pilihan tidak valid.\n";
            metodePembayaran = "";
            return;
        }
        cout << "Metode pembayaran " << metodePembayaran << " dipilih.\n";
    }

    void unduhPembayaran() {
        string filename = nim + "_SPP.txt";
        ofstream file(filename.c_str());
        if(!file) {
            cout << "Gagal membuat file pembayaran.\n";
            return;
        }
        file << "== Portal UAD - Bukti Pembayaran SPP ==\n";
        file << "Nama     : " << nama << "\n";
        file << "NIM      : " << nim << "\n";
        file << "Prodi    : " << prodi << "\n";
        file << "Fakultas : " << fakultas << "\n";
        file << "---------------------------------------\n";
        file << "Mata Kuliah yang diambil:\n";
        int totalSKS = 0;
        for(int i=0; i < jumlahKRS; i++) {
            file << krs[i].kode << " - " << krs[i].nama << " (" << krs[i].sks << " SKS)\n";
            totalSKS += krs[i].sks;
        }
        file << "Total SKS: " << totalSKS << "\n";
        file << "Beasiswa : " << (beasiswa ? "Ya (diskon 15%)" : "Tidak") << "\n";
        file << "Metode Pembayaran: " << metodePembayaran << "\n";
        file << "Total Pembayaran SPP: Rp " << hitungSPP() << "\n";
        file.close();
        cout << "Bukti pembayaran berhasil diunduh ke file '" << filename << "'.\n";
    }
};

MataKuliah daftarMatkul[MAX_MATKUL] = {
    {"IF101", "Algoritma", 3, "Senin 08:00-10:00", 'A'},
    {"IF102", "Struktur Data", 3, "Selasa 10:00-12:00", 'B'},
    {"IF103", "Basis Data", 3, "Rabu 13:00-15:00", 'A'},
    {"IF104", "Pemrograman", 4, "Kamis 08:00-11:00", 'C'},
    {"IF105", "Jaringan Komputer", 3, "Jumat 09:00-11:00", 'B'}
};

Mahasiswa daftarMahasiswa[MAX_MHS] = {
    {"123456", "aldi", "Aldi Saputra", "Teknik Informatika", "Fakultas Teknik"},
    {"654321", "sari", "Sari Nur", "Sistem Informasi", "Fakultas Teknik"}
};

Mahasiswa* currentUser = NULL;

bool login() {
    string username, nim;
    cout << "== Login Mahasiswa ==\n";
    cout << "Username: "; cin >> username;
    cout << "NIM: "; cin >> nim;

    for(int i=0; i < MAX_MHS; i++) {
        if(daftarMahasiswa[i].username == username && daftarMahasiswa[i].nim == nim) {
            currentUser = &daftarMahasiswa[i];
            cout << "Login berhasil! Selamat datang, " << currentUser->nama << ".\n";
            return true;
        }
    }
    cout << "Login gagal! Username atau NIM salah.\n";
    return false;
}

void tampilkanDaftarMatkul() {
    cout << "\nKode\tNama Mata Kuliah\tSKS\tJadwal\n";
    for(int i=0; i < MAX_MATKUL; i++) {
        cout << daftarMatkul[i].kode << "\t" << daftarMatkul[i].nama << "\t" << daftarMatkul[i].sks << "\t" << daftarMatkul[i].jadwal << "\n";
    }
}

void menuKRS() {
    int choice;
    do {
        cout << "\n--- Menu KRS ---\n";
        cout << "1. Tambah Mata Kuliah\n2. Hapus Mata Kuliah\n3. Tampilkan KRS\n4. Kembali ke Menu Utama\n";
        cout << "Pilih menu: ";
        cin >> choice;
        if(choice == 1) {
            tampilkanDaftarMatkul();
            cout << "Masukkan kode mata kuliah yang ingin diambil: ";
            string kode; cin >> kode;
            bool found = false;
            for(int i=0; i < MAX_MATKUL; i++) {
                if(daftarMatkul[i].kode == kode) {
                    currentUser->tambahMatkul(daftarMatkul[i]);
                    found = true;
                    break;
                }
            }
            if(!found) cout << "Kode mata kuliah tidak ditemukan.\n";
        }
        else if(choice == 2) {
            currentUser->tampilkanKRS();
            if(currentUser->jumlahKRS == 0) continue;
            cout << "Masukkan nomor mata kuliah yang ingin dihapus: ";
            int idx; cin >> idx;
            currentUser->hapusMatkul(idx-1);
        }
        else if(choice == 3) {
            currentUser->tampilkanKRS();
        }
        else if(choice != 4) {
            cout << "Pilihan tidak valid.\n";
        }
    } while(choice != 4);
}

void mainMenu() {
    int choice;
    do {
        cout << "\n=== Portal UAD - Menu Utama ===\n";
        cout << "1. Informasi Pribadi\n2. KRS\n3. Lihat Jadwal Kuliah\n4. Lihat Nilai\n5. Ajukan Beasiswa\n";
        cout << "6. Pembayaran SPP\n7. Unduh Bukti Pembayaran SPP\n8. Logout\n";
        cout << "Pilih menu: ";
        cin >> choice;

        if(choice == 1) currentUser->tampilkanInfoPribadi();
        else if(choice == 2) menuKRS();
        else if(choice == 3) currentUser->tampilkanJadwal();
        else if(choice == 4) currentUser->tampilkanNilai();
        else if(choice == 5) currentUser->ajukanBeasiswa();
        else if(choice == 6) currentUser->pembayaranSPP();
        else if(choice == 7) currentUser->unduhPembayaran();
        else if(choice == 8) {
            cout << "Logout berhasil.\n";
            currentUser = NULL;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } while(choice != 8);
}

int main() {
    cout << "===== Selamat datang di Portal Mahasiswa UAD =====\n";
    while(!login()) {
        cout << "Silakan coba login kembali.\n";
    }
    mainMenu();
    cout << "Terima kasih telah menggunakan Portal UAD.\n";
    return 0;
}


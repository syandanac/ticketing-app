#include <stdio.h>
#include <string.h>

#define MAX_KERETA 3
#define MAX_KURSI 100
#define MAX_PENUMPANG 10

typedef struct {
    char nama[50];
    char kelas[20];
    char rute[50];
    int kapasitas;
    float tarif;
} Kereta;

typedef struct {
    char nama[50];
    char id[20];
    char noTelp[15];
    int nomorKursi;
} Penumpang;

int login() {
    char username[20], password[20];
    char validUsername[] = "mahasiswa";
    char validPassword[] = "12345";

    puts("===== Login =====");
    puts("Username: ");
    gets(username);
    puts("Password: ");
    gets(password);

    if (strstr(username, validUsername) && strstr(password, validPassword)) {
        puts("Login Berhasil !\n");
        return 1;
    } else {
        puts("Username atau password anda salah!.\n");
        return 0;
    }
}

void pilihanKereta(Kereta kereta[], int count) {
    puts("===== Pilihan Kereta =====");
    for (int i = 0; i < count; i++) {
        printf("%d. Nama: %s, Kelas: %s, Rute: %s, Kapasitas: %d, Tarif: %.2f\n", 
                i + 1, kereta[i].nama, kereta[i].kelas, kereta[i].rute, kereta[i].kapasitas, kereta[i].tarif);
    }
}

int main() {
    Kereta kereta[MAX_KERETA] = {
        {"Kereta A", "Eksekutif", "Jakarta - Bandung", 50, 150000.0},
        {"Kereta B", "Bisnis", "Bandung - Yogyakarta", 60, 120000.0},
        {"Kereta C", "Ekonomi", "Yogyakarta - Surabaya", 80, 90000.0}
    };

    Penumpang penumpang[MAX_PENUMPANG];
    int chosenKereta, jumlahPenumpang;
    char buffer[10];

    if (!login()) {
        return 1;
    }

    pilihanKereta(kereta, MAX_KERETA);

    puts("\nPilih kereta yang ingin dipesan (1-3): ");
    gets(buffer);
    sscanf(buffer, "%d", &chosenKereta);
    chosenKereta--;

    puts("Masukkan jumlah penumpang: ");
    gets(buffer);
    sscanf(buffer, "%d", &jumlahPenumpang);

    for (int i = 0; i < jumlahPenumpang; i++) {
        printf("\nPenumpang %d\n", i + 1);
        puts("Nama: ");
        gets(penumpang[i].nama);
        puts("Nomor Identitas: ");
        gets(penumpang[i].id);
        puts("Nomor Telepon: ");
        gets(penumpang[i].noTelp);
        puts("Nomor Kursi: ");
        gets(buffer);
        sscanf(buffer, "%d", &penumpang[i].nomorKursi);
    }

    puts("\n===== Detail Pesanan =====");
    printf("Kereta: %s, Rute: %s\n", kereta[chosenKereta].nama, kereta[chosenKereta].rute);
    printf("Jumlah Penumpang: %d\n", jumlahPenumpang);
    for (int i = 0; i < jumlahPenumpang; i++) {
        printf("Penumpang %d: %s, ID: %s, Phone: %s, Seat: %d\n", 
                i + 1, penumpang[i].nama, penumpang[i].id, penumpang[i].noTelp, penumpang[i].nomorKursi);
    }
    printf("Total Tarif: %.2f\n", kereta[chosenKereta].tarif * jumlahPenumpang);

    return 0;
}

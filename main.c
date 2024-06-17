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
    char validUsername[] = "user";
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
        printf("%d. Nama: %s, Kelas: %s, Rute: %s, Kapasitas: %d, Tarif: %.3f\n", 
                i + 1, kereta[i].nama, kereta[i].kelas, kereta[i].rute, kereta[i].kapasitas, kereta[i].tarif);
    }
}

void simpanPesanan(Kereta kereta, Penumpang penumpang[], int jumlahPenumpang, float totalTarif) {
    char filename[20];
    FILE *file;
    int counter = 0;

    do {
        if (counter == 0) {
            sprintf(filename, "pesanan.txt");
        } else {
            sprintf(filename, "pesanan%d.txt", counter);
        }
        file = fopen(filename, "r");
        if (file != NULL) {
            fclose(file);
            counter++;
        }
    } while (file != NULL && counter < 100);

    file = fopen(filename, "a");

    if (file == NULL) {
        printf("Gagal membuka file %s.\n", filename);
        return;
    }

    fprintf(file, "\t===== STRUK BUKTI PEMESANAN TIKET =====\n");
    fprintf(file, "Kereta: %s, Rute: %s\n", kereta.nama, kereta.rute);
    fprintf(file, "Jumlah Penumpang: %d\n", jumlahPenumpang);
    for (int i = 0; i < jumlahPenumpang; i++) {
        fprintf(file, "Penumpang %d: %s, ID: %s, No. Telp: %s, No. Kursi: %d\n\n", 
                i + 1, penumpang[i].nama, penumpang[i].id, penumpang[i].noTelp, penumpang[i].nomorKursi);
    }
    fprintf(file, "Total Tarif: %.3f\n", totalTarif);

    fprintf(file, "\n");
    fclose(file);

    printf("Pesanan berhasil disimpan di %s.\n", filename);
}

int main() {
    Kereta kereta[MAX_KERETA] = {
        {"Argo Parahyangan", "Eksekutif", "Jakarta - Bandung", 50, 150.000},
        {"Brantas", "Bisnis", "Malang - Jakarta", 60, 120.000},
        {"Sancaka", "Ekonomi", "Yogyakarta - Surabaya", 80, 90.000}
    };

    Penumpang penumpang[MAX_PENUMPANG];
    int keretaDipilih, jumlahPenumpang;
    char buffer[10];

    if (!login()) {
        return 1;
    }

    pilihanKereta(kereta, MAX_KERETA);

    puts("\nPilih kereta yang ingin dipesan (1-3): ");
    gets(buffer);
    sscanf(buffer, "%d", &keretaDipilih);
    keretaDipilih--;

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

    float totalTarif = kereta[keretaDipilih].tarif * jumlahPenumpang;

    puts("\n===== Detail Pesanan =====");
    printf("Kereta: %s, Rute: %s\n", kereta[keretaDipilih].nama, kereta[keretaDipilih].rute);
    printf("Jumlah Penumpang: %d\n", jumlahPenumpang);
    for (int i = 0; i < jumlahPenumpang; i++) {
        printf("Penumpang %d: %s, ID: %s, No. Telp: %s, No. Kursi: %d\n\n", 
                i + 1, penumpang[i].nama, penumpang[i].id, penumpang[i].noTelp, penumpang[i].nomorKursi);
    }
    printf("Total Tarif: %.3f\n", totalTarif);
    
    simpanPesanan(kereta[keretaDipilih], penumpang, jumlahPenumpang, totalTarif);

    return 0;
}

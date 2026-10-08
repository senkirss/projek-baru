#include <stdio.h>
#include <string.h>

#define MAX_ORANG 10

// Fungsi buat bulatin ke ribuan KE ATAS
// Contoh: 25321 -> 26000, 25000 -> 25000
int bulatkanKeRibuan(double nominal) {
    int n = (int)nominal;
    if (nominal > n) {
        n = n + 1;
    }
    if (n % 1000 == 0) {
        return n;
    } else {
        return (n / 1000 + 1) * 1000;
    }
}

// Buang sisa ketikan di keyboard biar scanf berikutnya tidak error
void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void tekanEnter() {
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

int main() {
    // Data awal (contoh bawaan biar langsung bisa dicoba)
    char nama[MAX_ORANG][30] = {"Budi", "Ani", "Cici"};
    double belanja[MAX_ORANG] = {35000, 28000, 15000};
    int jumlahOrang = 3;
    double persenPajak = 10.0;
    double persenServis = 5.0;
    int dataPernahDiisi = 1; // 1 = sudah ada contoh bawaan

    int pilihan = 0;

    do {
        printf("\n==============================\n");
        printf("  KALKULATOR PATUNGAN KAFE\n");
        printf("==============================\n");
        printf("1. Isi nama teman & belanjaan\n");
        printf("2. Atur pajak & servis\n");
        printf("3. Hitung & tampilkan struk\n");
        printf("4. Lihat data saat ini\n");
        printf("0. Keluar\n");
        printf("------------------------------\n");
        printf("Pilih menu (0-4): ");

        if (scanf("%d", &pilihan) != 1) {
            printf("\nInput tidak valid! Masukkan angka 0-4.\n");
            bersihkanBuffer();
            tekanEnter();
            continue;
        }
        bersihkanBuffer();

        if (pilihan == 1) {
            int n = 0;
            printf("\n--- ISI DATA TEMAN ---\n");
            printf("Berapa orang yang ikut makan? (1-%d): ", MAX_ORANG);
            if (scanf("%d", &n) != 1) {
                printf("Input harus angka!\n");
                bersihkanBuffer();
                tekanEnter();
                continue;
            }
            bersihkanBuffer();

            if (n < 1 || n > MAX_ORANG) {
                printf("Jumlah harus antara 1 sampai %d!\n", MAX_ORANG);
                tekanEnter();
                continue;
            }

            jumlahOrang = n;
            for (int i = 0; i < jumlahOrang; i++) {
                printf("\nTeman ke-%d\n", i + 1);

                printf("  Nama: ");
                if (fgets(nama[i], sizeof(nama[i]), stdin) == NULL) {
                    strcpy(nama[i], "Teman");
                } else {
                    nama[i][strcspn(nama[i], "\n")] = '\0';
                    if (strlen(nama[i]) == 0) {
                        sprintf(nama[i], "Teman-%d", i + 1);
                    }
                }

                printf("  Total belanjaan %s (Rp): ", nama[i]);
                if (scanf("%lf", &belanja[i]) != 1) {
                    printf("  Input tidak valid, dianggap Rp 0.\n");
                    belanja[i] = 0;
                    bersihkanBuffer();
                } else {
                    bersihkanBuffer();
                    if (belanja[i] < 0) {
                        printf("  Belanja tidak boleh minus, dianggap Rp 0.\n");
                        belanja[i] = 0;
                    }
                }
            }
            dataPernahDiisi = 1;
            printf("\nData berhasil disimpan!\n");
            tekanEnter();

        } else if (pilihan == 2) {
            double pjk, srv;
            printf("\n--- ATUR PAJAK & SERVIS ---\n");
            printf("Pajak saat ini: %.1f%%\n", persenPajak);
            printf("Masukkan pajak baru (%%, 0-100): ");
            if (scanf("%lf", &pjk) != 1) {
                printf("Input tidak valid!\n");
                bersihkanBuffer();
                tekanEnter();
                continue;
            }
            bersihkanBuffer();

            printf("Servis saat ini: %.1f%%\n", persenServis);
            printf("Masukkan servis baru (%%, 0-100): ");
            if (scanf("%lf", &srv) != 1) {
                printf("Input tidak valid!\n");
                bersihkanBuffer();
                tekanEnter();
                continue;
            }
            bersihkanBuffer();

            if (pjk < 0 || pjk > 100 || srv < 0 || srv > 100) {
                printf("Pajak & servis harus 0-100!\n");
                tekanEnter();
                continue;
            }

            persenPajak = pjk;
            persenServis = srv;
            printf("\nPajak & servis berhasil diubah!\n");
            tekanEnter();

        } else if (pilihan == 3) {
            if (dataPernahDiisi == 0 || jumlahOrang == 0) {
                printf("\nBelum ada data! Pilih menu 1 dulu.\n");
                tekanEnter();
                continue;
            }

            double totalKotor = 0;
            for (int i = 0; i < jumlahOrang; i++) {
                totalKotor += belanja[i];
            }

            if (totalKotor <= 0) {
                printf("\nTotal belanja masih Rp 0. Isi dulu di menu 1.\n");
                tekanEnter();
                continue;
            }

            double nominalPajak = totalKotor * persenPajak / 100.0;
            double nominalServis = totalKotor * persenServis / 100.0;
            double totalBersih = totalKotor + nominalPajak + nominalServis;

            printf("\n===== STRUK PATUNGAN KAFE =====\n");
            printf("Total makanan (kotor) : Rp %.0f\n", totalKotor);
            printf("Pajak (%.1f%%)          : Rp %.0f\n", persenPajak, nominalPajak);
            printf("Servis (%.1f%%)         : Rp %.0f\n", persenServis, nominalServis);
            printf("Total harus dibayar   : Rp %.0f\n", totalBersih);
            printf("===============================\n\n");

            int bayarAkhir[MAX_ORANG];
            for (int i = 0; i < jumlahOrang; i++) {
                double bagianAdil = belanja[i] + (belanja[i] / totalKotor) * (nominalPajak + nominalServis);
                bayarAkhir[i] = bulatkanKeRibuan(bagianAdil);

                printf("%s:\n", nama[i]);
                printf("  Belanja asli                : Rp %.0f\n", belanja[i]);
                printf("  + pajak+servis proporsional : Rp %.0f\n", bagianAdil);
                printf("  => Harus bayar (dibulatkan) : Rp %d\n\n", bayarAkhir[i]);
            }

            printf("--- RINGKASAN TRANSFER ---\n");
            for (int i = 0; i < jumlahOrang; i++) {
                printf("%s bayar Rp %d\n", nama[i], bayarAkhir[i]);
            }

            tekanEnter();

        } else if (pilihan == 4) {
            printf("\n--- DATA SAAT INI ---\n");
            printf("Pajak: %.1f%% | Servis: %.1f%%\n", persenPajak, persenServis);
            for (int i = 0; i < jumlahOrang; i++) {
                printf("%d. %s - Rp %.0f\n", i + 1, nama[i], belanja[i]);
            }
            tekanEnter();

        } else if (pilihan == 0) {
            printf("\nMakasih udah nongkrong bareng! Dadah!\n");

        } else {
            printf("\nPilihan tidak ada! Pilih 0-4.\n");
            tekanEnter();
        }

    } while (pilihan != 0);

    return 0;
}

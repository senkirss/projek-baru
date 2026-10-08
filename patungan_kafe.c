#include <stdio.h>
#include <string.h>

#define MAX_ORANG 10

// Bulatkan ke ribuan KE ATAS
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

// Buang sisa ketikan biar scanf berikutnya aman
void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main() {
    char nama[MAX_ORANG][30];
    double belanja[MAX_ORANG] = {0};
    int bayarAkhir[MAX_ORANG] = {0};
    int jumlahOrang = 0;
    double persenPajak = 0;

    printf("==============================\n");
    printf("  PATUNGAN KAFE - SPLIT BILL\n");
    printf("==============================\n");

    // ALUR 1: Siapa aja yang ikut makan?
    while (1) {
        printf("\nBerapa orang yang ikut makan? (1-%d): ", MAX_ORANG);
        if (scanf("%d", &jumlahOrang) != 1) {
            printf("Harus masukkan angka!\n");
            bersihkanBuffer();
            continue;
        }
        bersihkanBuffer();
        if (jumlahOrang < 1 || jumlahOrang > MAX_ORANG) {
            printf("Harus antara 1 sampai %d!\n", MAX_ORANG);
            continue;
        }
        break;
    }

    for (int i = 0; i < jumlahOrang; i++) {
        printf("\n--- Teman ke-%d ---\n", i + 1);

        printf("Nama: ");
        if (fgets(nama[i], sizeof(nama[i]), stdin) == NULL) {
            strcpy(nama[i], "Teman");
        } else {
            nama[i][strcspn(nama[i], "\n")] = '\0';
            if (strlen(nama[i]) == 0) {
                sprintf(nama[i], "Teman-%d", i + 1);
            }
        }

        while (1) {
            printf("Total belanjaan %s (Rp): ", nama[i]);
            if (scanf("%lf", &belanja[i]) != 1) {
                printf("Harus masukkan angka! Coba lagi.\n");
                bersihkanBuffer();
                continue;
            }
            bersihkanBuffer();
            if (belanja[i] < 0) {
                printf("Tidak boleh minus! Coba lagi.\n");
                continue;
            }
            break;
        }
    }

    // ALUR 2: Hitung total semuanya (contoh: 100000)
    double totalKotor = 0;
    for (int i = 0; i < jumlahOrang; i++) {
        totalKotor += belanja[i];
    }

    if (totalKotor <= 0) {
        printf("\nTotal belanja Rp 0, tidak ada yang perlu dibagi.\n");
        return 0;
    }

    printf("\n------------------------------\n");
    printf("Total semuanya : Rp %.0f\n", totalKotor);
    printf("------------------------------\n");

    // ALUR 3: Masukkan pajak, lalu tampilkan total + pajak
    while (1) {
        printf("\nMasukkan pajak (%%, 0-100, contoh 10): ");
        if (scanf("%lf", &persenPajak) != 1) {
            printf("Harus masukkan angka! Coba lagi.\n");
            bersihkanBuffer();
            continue;
        }
        bersihkanBuffer();
        if (persenPajak < 0 || persenPajak > 100) {
            printf("Pajak harus 0-100! Coba lagi.\n");
            continue;
        }
        break;
    }

    double nominalPajak = totalKotor * persenPajak / 100.0;
    double totalPlusPajak = totalKotor + nominalPajak;

    printf("\n------------------------------\n");
    printf("Total awal     : Rp %.0f\n", totalKotor);
    printf("Pajak (%.1f%%)    : Rp %.0f\n", persenPajak, nominalPajak);
    printf("Total + pajak  : Rp %.0f\n", totalPlusPajak);
    printf("------------------------------\n");

    // ALUR 4: Split bill dari total itu secara adil + dibulatkan
    printf("\n===== STRUK SPLIT BILL =====\n");
    for (int i = 0; i < jumlahOrang; i++) {
        // Yang pesen mahal nanggung pajak lebih gede
        double bagianAdil = belanja[i] + (belanja[i] / totalKotor) * nominalPajak;
        bayarAkhir[i] = bulatkanKeRibuan(bagianAdil);

        printf("\n%s:\n", nama[i]);
        printf("  Belanja asli : Rp %.0f\n", belanja[i]);
        printf("  + bagian pajak : Rp %.0f\n", bagianAdil);
        printf("  => Bayar (dibulatkan ke ribuan) : Rp %d\n", bayarAkhir[i]);
    }

    printf("\n--- RINGKASAN TRANSFER ---\n");
    for (int i = 0; i < jumlahOrang; i++) {
        printf("%s transfer Rp %d\n", nama[i], bayarAkhir[i]);
    }
    printf("--------------------------\n");

    return 0;
}

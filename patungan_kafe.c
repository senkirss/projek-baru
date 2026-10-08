#include <stdio.h>

#define JUMLAH_ORANG 3

// Fungsi buat bulatin ke ribuan KE ATAS
// Contoh: 25321 -> 26000, 25000 -> 25000
// Tanpa math.h biar compile gampang: gcc patungan_kafe.c -o patungan_kafe
int bulatkanKeRibuan(double nominal) {
    int n = (int)nominal;   // buang koma dulu, misal 40250.0 -> 40250
    // kalau ada sisa koma (misal 40250.5), anggap naik 1 biar aman
    if (nominal > n) {
        n = n + 1;
    }
    if (n % 1000 == 0) {
        return n;
    } else {
        return (n / 1000 + 1) * 1000;
    }
}

int main() {
    // LANGKAH 1: Siapin "kotak" (array)
    // Kotak pertama: nama orang yang ikut makan
    char nama[JUMLAH_ORANG][20] = {"Budi", "Ani", "Cici"};

    // Kotak kedua: total belanjaan makanan asli masing-masing (belum pajak/servis)
    double belanja[JUMLAH_ORANG] = {35000, 28000, 15000};

    // Pajak dan servis (bisa diganti-ganti)
    double persenPajak = 10.0;  // 10%
    double persenServis = 5.0;  // 5%

    // LANGKAH 2: Hitung pajak dan biaya servis secara adil (proporsional)
    double totalKotor = 0;
    for (int i = 0; i < JUMLAH_ORANG; i++) {
        totalKotor += belanja[i];
    }

    double nominalPajak = totalKotor * persenPajak / 100.0;
    double nominalServis = totalKotor * persenServis / 100.0;
    double totalBersih = totalKotor + nominalPajak + nominalServis;

    // Kotak ketiga: tagihan akhir tiap orang (sesudah pajak + dibulatkan)
    int bayarAkhir[JUMLAH_ORANG];

    printf("===== STRUK PATUNGAN KAFE =====\n");
    printf("Total makanan (kotor) : Rp %.0f\n", totalKotor);
    printf("Pajak (%.0f%%)           : Rp %.0f\n", persenPajak, nominalPajak);
    printf("Servis (%.0f%%)          : Rp %.0f\n", persenServis, nominalServis);
    printf("Total harus dibayar   : Rp %.0f\n", totalBersih);
    printf("===============================\n\n");

    for (int i = 0; i < JUMLAH_ORANG; i++) {
        // Biar adil: yang pesen mahal nanggung pajak lebih gede.
        // Rumus: (belanja orang / total kotor) * (pajak + servis)
        // Sederhananya = belanja * (1 + pajak% + servis%)
        double bagianAdil = belanja[i] + (belanja[i] / totalKotor) * (nominalPajak + nominalServis);

        // LANGKAH 3: Bulatin biar gampang transfer (ke ribuan terdekat ke atas)
        bayarAkhir[i] = bulatkanKeRibuan(bagianAdil);

        // LANGKAH 4: Bagiin tagihan akhirnya
        printf("%s:\n", nama[i]);
        printf("  Belanja asli : Rp %.0f\n", belanja[i]);
        printf("  + Pajak+servis proporsional : Rp %.0f\n", bagianAdil);
        printf("  => Harus bayar (dibulatkan) : Rp %d\n\n", bayarAkhir[i]);
    }

    printf("--- RINGKASAN TRANSFER ---\n");
    for (int i = 0; i < JUMLAH_ORANG; i++) {
        printf("%s bayar Rp %d\n", nama[i], bayarAkhir[i]);
    }

    return 0;
}

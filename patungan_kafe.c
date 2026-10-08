#include <stdio.h>
#include <string.h>

#define MAKS_ORANG 10

int bulatRibuan(double nominal) {
    int n = (int)nominal;
    if (nominal > n) n++;
    if (n % 1000 == 0) return n;
    return (n / 1000 + 1) * 1000;
}

void buangEnter() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    char nama[MAKS_ORANG][30];
    double makan[MAKS_ORANG] = {0};
    int harusBayar[MAKS_ORANG] = {0};
    int orang = 0;
    double pajakPersen = 0;

    printf("=== PATUNGAN KAFE ===\n");

    /* 1. Siapa aja yang ikut? */
    while (1) {
        printf("\nJumlah orang (1-%d): ", MAKS_ORANG);
        if (scanf("%d", &orang) != 1) {
            printf("Masukkan angka!\n");
            buangEnter();
            continue;
        }
        buangEnter();
        if (orang < 1 || orang > MAKS_ORANG) {
            printf("Antara 1-%d!\n", MAKS_ORANG);
            continue;
        }
        break;
    }

    for (int i = 0; i < orang; i++) {
        printf("\nOrang ke-%d\n", i + 1);
        printf("Nama: ");
        if (fgets(nama[i], sizeof nama[i], stdin) == NULL) {
            strcpy(nama[i], "Teman");
        } else {
            nama[i][strcspn(nama[i], "\n")] = 0;
            if (strlen(nama[i]) == 0) sprintf(nama[i], "Teman-%d", i + 1);
        }
        while (1) {
            printf("Belanja %s (Rp): ", nama[i]);
            if (scanf("%lf", &makan[i]) != 1) {
                printf("Masukkan angka!\n");
                buangEnter();
                continue;
            }
            buangEnter();
            if (makan[i] < 0) {
                printf("Tidak boleh minus!\n");
                continue;
            }
            break;
        }
    }

    /* 2. Total semuanya */
    double total = 0;
    for (int i = 0; i < orang; i++) total += makan[i];
    if (total <= 0) {
        printf("\nTotal Rp 0, selesai.\n");
        return 0;
    }
    printf("\nTotal semuanya: Rp %.0f\n", total);

    /* 3. Pajak -> total + pajak */
    while (1) {
        printf("Pajak %% (0-100): ");
        if (scanf("%lf", &pajakPersen) != 1) {
            printf("Masukkan angka!\n");
            buangEnter();
            continue;
        }
        buangEnter();
        if (pajakPersen < 0 || pajakPersen > 100) {
            printf("Harus 0-100!\n");
            continue;
        }
        break;
    }

    double rpPajak = total * pajakPersen / 100.0;
    double totalPajak = total + rpPajak;
    printf("Pajak (%.1f%%): Rp %.0f\n", pajakPersen, rpPajak);
    printf("Total + pajak: Rp %.0f\n", totalPajak);

    /* 4. Split bill adil + bulatkan */
    printf("\n=== SPLIT BILL ===\n");
    for (int i = 0; i < orang; i++) {
        double adil = makan[i] + (makan[i] / total) * rpPajak;
        harusBayar[i] = bulatRibuan(adil);
        printf("%s: Rp %.0f + pajak = Rp %.0f -> bayar Rp %d\n",
               nama[i], makan[i], adil, harusBayar[i]);
    }

    printf("\n--- TRANSFER ---\n");
    for (int i = 0; i < orang; i++) {
        printf("%s transfer Rp %d\n", nama[i], harusBayar[i]);
    }

    return 0;
}

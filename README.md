# Patungan Kafe — Split Bill

Program C sederhana buat patungan bill kafe ala nongkrong bareng teman.
Input nama + belanjaan tiap orang, hitung total, tambah pajak,
lalu split bill secara adil + dibulatkan ke ribuan biar gampang transfer.

## Alur Program

1. Input jumlah orang (1–10)
2. Input nama + total belanjaan tiap orang
3. Program hitung dan tampilkan **total semuanya** (misal Rp 100.000)
4. Input pajak % (misal 10%)
5. Program tampilkan **total + pajak** (misal Rp 110.000)
6. Split bill proporsional:
   yang pesen mahal nanggung pajak lebih besar
7. Bulatkan ke ribuan ke atas (misal Rp 38.500 → Rp 39.000)
8. Tampilkan struk + ringkasan transfer

## Cara Compile & Run

```bash
gcc patungan_kafe.c -o patungan_kafe
./patungan_kafe
```

Di Windows (PowerShell):

```powershell
gcc patungan_kafe.c -o patungan_kafe
.\patungan_kafe.exe
```

## Contoh

```
Jumlah orang (1-10): 3

Orang ke-1
Nama: Budi
Belanja Budi (Rp): 40000

Orang ke-2
Nama: Ani
Belanja Ani (Rp): 35000

Orang ke-3
Nama: Cici
Belanja Cici (Rp): 25000

Total semuanya: Rp 100000
Pajak % (0-100): 10
Pajak (10.0%): Rp 10000
Total + pajak: Rp 110000

=== SPLIT BILL ===
Budi: Rp 40000 + pajak = Rp 44000 -> bayar Rp 44000
Ani: Rp 35000 + pajak = Rp 38500 -> bayar Rp 39000
Cici: Rp 25000 + pajak = Rp 27500 -> bayar Rp 28000

--- TRANSFER ---
Budi transfer Rp 44000
Ani transfer Rp 39000
Cici transfer Rp 28000
```

## File

- `patungan_kafe.c` — kode utama (flow, tanpa menu)

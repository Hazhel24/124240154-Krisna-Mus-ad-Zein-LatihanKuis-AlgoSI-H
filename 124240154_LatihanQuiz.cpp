#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

struct data_buku
{
    char ID[20];       // size maksimal char ID adalah 20
    char judul[100];   // size maksimal char judul adalah 100
    char penulis[100]; // size maksimal char penulis adalah 100
    int stok;
};

data_buku buku[100];
int jumlah_buku = 0;
void simpan_ke_file()
{
    FILE *fptr = fopen("data.dat", "w");
    if (fptr == NULL)
    {
        printf("Error !");
        exit(1);
    }
    for (int i = 0; i < jumlah_buku; i++)
    {
        fprintf(fptr, "%s\n%s\n%s\n%d\n", buku[i].ID, buku[i].judul, buku[i].penulis, buku[i].stok);
    }
    fclose(fptr);
}
void sort_data_buku() // mengurutkan secara asc
{
    for (int i = 0; i < jumlah_buku - 1; i++)
    {
        for (int j = 0; j < jumlah_buku - i - 1; j++)
        {
            if (strcmp(buku[j].ID, buku[j + 1].ID) > 0)
            {
                swap(buku[j], buku[j + 1]);
            }
        }
    }
    simpan_ke_file();
}
void cari_buku()
{
    bool found = false;
    char cari_nama[100];
    int urutan = 0;
    cout << "Masukkan kata kunci dari judul buku yang dicari : ";
    cin.ignore();
    cin.getline(cari_nama, 100);

    for (int i = 0; i < jumlah_buku; i++)
    {
        if (strstr(buku[i].judul, cari_nama) != NULL)
        {
            urutan = i;
            found = true;
            break;
        }
    }
    if (found)
    {
        cout << "Buku ditemukan!" << '\n';
        cout << "ID : " << buku[urutan].ID << endl;
        cout << "Judul : " << buku[urutan].judul << '\n';
        cout << "Penulis : " << buku[urutan].penulis << '\n';
        cout << "Stok : " << buku[urutan].stok << '\n';
        system("pause");
    }
    else
    {
        cout << "Tidak ada buku dengan judul \"" << cari_nama << "\" dalam database" << endl;
    }
}

void baca_dari_file()
{
    FILE *fptr = fopen("data.dat", "r");
    if (fptr == NULL)
    {
        return;
    }
    jumlah_buku = 0;
    while (fscanf(fptr, "%s", buku[jumlah_buku].ID) != EOF)
    {
        fscanf(fptr, " %[^\n]", buku[jumlah_buku].judul);
        fscanf(fptr, " %[^\n]", buku[jumlah_buku].penulis);
        fscanf(fptr, "%d", &buku[jumlah_buku].stok);
        jumlah_buku++;
    }
    fclose(fptr);
}

void tambah_data_buku()
{
    char kembali;
    do
    {
        cout << "\n===== Tambah data buku =====\n";
        cout << "ID buku: (disarankan pengisian kombinasi berjumlah 5 dari gabungan huruf/angka) : ";
        cin >> buku[jumlah_buku].ID;
        cout << "Judul buku: ";
        cin.ignore();
        cin.getline(buku[jumlah_buku].judul, 100);
        cout << "Penulis: ";
        cin.getline(buku[jumlah_buku].penulis, 100);
        cout << "Stok: ";
        cin >> buku[jumlah_buku].stok;
        jumlah_buku++;
        simpan_ke_file();
        sort_data_buku();
        cout << "\nBuku berhasil ditambahkan!\n";
        cout << "Balik ke menu? (Y/N): " << '\n';
        cout << ">> ";
        cin >> kembali;
    } while (kembali == 'N' || kembali == 'n');
}

void tampilkan_data_buku()
{
    char choice;
    do
    {
        cout << "======================================================================================\n";
        cout << left << setw(10) << "ID"
             << setw(35) << "Judul"
             << setw(30) << "Penulis"
             << right << setw(10) << "Stok\n";
        cout << "======================================================================================\n";

        for (int i = 0; i < jumlah_buku; i++)
        {
            cout << left << setw(10) << buku[i].ID
                 << setw(35) << buku[i].judul
                 << setw(30) << buku[i].penulis
                 << right << setw(7) << buku[i].stok << '\n';
        }
        cout << "======================================================================================\n";
        cout << "Balik ke menu? (Y/N): " << '\n';
        cout << ">> ";
        cin >> choice;
    } while (choice == 'N' || choice == 'n');
}
void hapus_data_buku()
{
    cout << "======================================================================================\n";
    cout << left << setw(10) << "ID"
         << setw(35) << "Judul"
         << setw(30) << "Penulis"
         << right << setw(10) << "Stok\n";
    cout << "======================================================================================\n";

    for (int i = 0; i < jumlah_buku; i++)
    {
        cout << left << setw(10) << buku[i].ID
             << setw(35) << buku[i].judul
             << setw(30) << buku[i].penulis
             << right << setw(7) << buku[i].stok << '\n';
    }

    cout << "======================================================================================\n";

    char choice;
    char ID_hapus[20];
    bool found = false;
    do
    {

        cout << "Masukkan ID buku yang ingin dihapus: ";
        cin >> ID_hapus;
        for (int i = 0; i < jumlah_buku; i++)
        {
            if (strcmp(ID_hapus, buku[i].ID) == 0)
            {
                found = true;
                for (int j = i; j < jumlah_buku - 1; j++)
                {
                    buku[j] = buku[j + 1];
                }
                jumlah_buku--;
                break;
            }
        }
        if (found)
        {
            simpan_ke_file(); // memperbarui data yang tersimpan
            sort_data_buku(); // mengurutkan data setelah data dihapus
            cout << "Buku dengan ID" << ID_hapus << " berhasil dihapus!\n";
            cout << "======================================================================================\n";
            cout << left << setw(10) << "ID"
                 << setw(35) << "Judul"
                 << setw(30) << "Penulis"
                 << right << setw(10) << "Stok\n"; // Mengubah kembali ke right sebelum mencetak stok
            cout << "======================================================================================\n";

            for (int i = 0; i < jumlah_buku; i++)
            {
                cout << left << setw(10) << buku[i].ID
                     << setw(35) << buku[i].judul
                     << setw(30) << buku[i].penulis
                     << right << setw(7) << buku[i].stok << '\n';
            }

            cout << "======================================================================================\n";
        }
        else
        {
            cout << "Buku dengan ID " << ID_hapus << " tidak ditemukan!\n";
        }
        cout << "Balik ke menu? (Y/N): " << '\n';
        cout << ">> ";
        cin >> choice;
    } while (choice == 'N' || choice == 'n');
}
void menu(const string &username)
{
    int pilih;
    do
    {
        cout << "\nHalo, " << username << "! SELAMAT DATANG DI DATABASE PERPUSTAKAAN INFORMATIKA\n";
        cout << "1. Tambah data buku\n";
        cout << "2. Tampilkan daftar buku\n";
        cout << "3. Cari buku\n";
        cout << "4. Hapus buku\n";
        cout << "5. Keluar\n";
        cout << ">> ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            tambah_data_buku();
            break;
        case 2:
            tampilkan_data_buku();
            break;
        case 3:
            cari_buku();
            break;
        case 4:
            hapus_data_buku();
            break;
        case 5:
            cout << "Program akan ditutup." << '\n';
            break;
        default:
            cout << "\nPilihan tidak valid!\n";
        }
    } while (pilih != 5);
}
int main()
{
    baca_dari_file();
    const string correctUsername = "krisna";
    const string correctPassword = "154";
    string username, password;

    while (true)
    {
        cout << "\nLOGIN KE DATABASE PERPUSTAKAAN INFORMATIKA\n";
        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;

        if (username == correctUsername && password == correctPassword) // mengecek username dan password jika benar maka akan masuk ke menu
        {
            break;
        }
        else
        {
            cout << "\nUsername atau password salah, harap masukkan ulang\n";
        }
    }

    menu(username);
    return 0;
}
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_ORDERS = 100; // Maksimum jumlah pesanan
const int MAX_MENU_ITEMS = 10; // Maksimum jumlah item dalam menu

// Struktur untuk menyimpan informasi pesanan
struct Order {
    int orderID;
    string customerName;
    double totalCost;
    string status;
    string specialRequest;
    string items[MAX_MENU_ITEMS]; // Maksimum 10 item per pesanan
    int itemCount; // Jumlah item dalam pesanan
};

// Struktur untuk menyimpan performa menu
struct MenuPerformance {
    string itemName;
    int soldCount;
};

// Struktur untuk menyimpan penggunaan topping
struct ToppingUsage {
    string toppingName;
    int usageCount;
};

// Array untuk menyimpan daftar pesanan
Order orders[MAX_ORDERS];
int totalOrders = 0;
MenuPerformance menuPerformance[3] = {
    {"Martabak Kacang", 0},
    {"Martabak Coklat", 0},
    {"Martabak Keju", 0}
};

// Array untuk menyimpan penggunaan topping
ToppingUsage toppingUsage[3] = {
    {"Topping Kacang", 0},
    {"Topping Coklat", 0},
    {"Topping Keju", 0}
};

// Array untuk menyimpan estimasi adonan harian
int dailyDoughEstimate[3] = {0, 0, 0}; // Indeks 0 = Martabak Kacang, 1 = Martabak Coklat, 2 = Martabak Keju

// Fungsi untuk menghitung total biaya pesanan
double calculateTotalCost(string items[], int itemCount) {
    double cost = 0.0;
    for (int i = 0; i < itemCount; ++i) {
        if (items[i] == "Martabak Kacang") cost += 65000;
        else if (items[i] == "Martabak Coklat") cost += 70000;
        else if (items[i] == "Martabak Keju") cost += 65000;
        else if (items[i] == "Topping Kacang") cost += 6000;
        else if (items[i] == "Topping Coklat") cost += 10000;
        else if (items[i] == "Topping Keju") cost += 8000;
    }
    return cost;
}

// Fungsi untuk memeriksa apakah item valid
bool isValidItem(string item) {
    string validItems[] = {"Martabak Kacang", "Martabak Coklat", "Martabak Keju", "Topping Kacang", "Topping Coklat", "Topping Keju"};
    for (int i = 0; i < 6; ++i) {
        if (validItems[i] == item) return true;
    }
    return false;
}

// Fungsi untuk mengambil pesanan
void takeOrder() {
    if (totalOrders >= MAX_ORDERS) {
        cout << "Tidak dapat menerima pesanan lebih banyak.\n";
        return;
    }

    int orderID;
    string customerName, specialRequest;
    string item;
    int itemCount = 0;

    cout << "Masukkan ID Pesanan: ";
    cin >> orderID;
    cin.ignore(); // Untuk membersihkan buffer
    cout << "Masukkan Nama Pelanggan: ";
    getline(cin, customerName);

    cout << "Masukkan item pesanan (ketik 'selesai' untuk berhenti):\n";
    while (true) {
        cout << "Item: ";
        getline(cin, item);
        if (item == "selesai") break;
        if (!isValidItem(item)) {
            cout << "Item tidak valid, coba lagi!" << endl;
            continue;
        }
        orders[totalOrders].items[itemCount] = item;
        itemCount++;
    }

    cout << "Masukkan permintaan khusus (atau ketik 'tidak' jika tidak ada): ";
    getline(cin, specialRequest);
    if (specialRequest == "tidak") {
        specialRequest = "Tidak ada permintaan khusus";
    }

    double totalCost = calculateTotalCost(orders[totalOrders].items, itemCount);

    // Menyimpan pesanan dalam array
    orders[totalOrders].orderID = orderID;
    orders[totalOrders].customerName = customerName;
    orders[totalOrders].totalCost = totalCost;
    orders[totalOrders].status = "Menunggu";
    orders[totalOrders].specialRequest = specialRequest;
    orders[totalOrders].itemCount = itemCount;

    // Update penggunaan topping
    for (int i = 0; i < itemCount; i++) {
        if (orders[totalOrders].items[i] == "Topping Kacang") toppingUsage[0].usageCount++;
        else if (orders[totalOrders].items[i] == "Topping Coklat") toppingUsage[1].usageCount++;
        else if (orders[totalOrders].items[i] == "Topping Keju") toppingUsage[2].usageCount++;
    }

    totalOrders++;

    cout << "Pesanan berhasil dibuat!\n";
    cout << "Total Biaya Pesanan: Rp" << fixed << setprecision(2) << totalCost << endl;
}

// Fungsi untuk melihat pesanan aktif
void viewActiveOrders() {
    if (totalOrders == 0) {
        cout << "Tidak ada pesanan aktif saat ini.\n";
        return;
    }

    cout << "\nDaftar Pesanan Aktif:\n";
    cout << left << setw(10) << "ID Pesanan"
         << setw(20) << "Nama Pelanggan"
         << setw(15) << "Total Biaya"
         << setw(15) << "Status"
         << "Items" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < totalOrders; i++) {
        cout << left << setw(10) << orders[i].orderID
             << setw(20) << orders[i].customerName
             << setw(15) << fixed << setprecision(2) << orders[i].totalCost
             << setw(15) << orders[i].status;

        for (int j = 0; j < orders[i].itemCount; ++j) {
            cout << orders[i].items[j];
            if (j != orders[i].itemCount - 1) cout << ", ";
        }
        cout << endl;
        cout << "   Permintaan Khusus: " << orders[i].specialRequest << endl;
    }
}

// Fungsi untuk memperbarui status pesanan
void updateOrderStatus() {
    int orderID;
    cout << "Masukkan ID Pesanan yang ingin diperbarui: ";
    cin >> orderID;
    cin.ignore(); // Untuk membersihkan buffer

    bool found = false;
    for (int i = 0; i < totalOrders; i++) {
        if (orders[i].orderID == orderID) {
            string newStatus;
            cout << "Masukkan Status Baru (Menunggu, Dalam Proses, Selesai): ";
            getline(cin, newStatus);

            if (newStatus != "Menunggu" && newStatus != "Dalam Proses" && newStatus != "Selesai") {
                cout << "Status tidak valid! Harus 'Menunggu', 'Dalam Proses', atau 'Selesai'.\n";
                return;
            }

            orders[i].status = newStatus;
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Status pesanan berhasil diperbarui!\n";
    } else {
        cout << "Pesanan tidak ditemukan!\n";
    }
}

// Fungsi untuk melihat laporan pendapatan harian
void viewDailySalesReport() {
    double totalSales = 0.0;
    for (int i = 0; i < totalOrders; i++) {
        totalSales += orders[i].totalCost;
    }
    cout << "Laporan Pendapatan Hari Ini: Rp" << fixed << setprecision(2) << totalSales << endl;
}

// Fungsi untuk melihat penggunaan topping
void viewToppingUsage() {
    cout << "Penggunaan Topping:\n";
    for (int i = 0; i < 3; i++) {
        cout << toppingUsage[i].toppingName << ": " << toppingUsage[i].usageCount << " kali digunakan\n";
    }
}

// Fungsi untuk melihat performa menu
void viewMenuPerformance() {
    for (int i = 0; i < totalOrders; i++) {
        for (int j = 0; j < orders[i].itemCount; j++) {
            if (orders[i].items[j] == "Martabak Kacang") menuPerformance[0].soldCount++;
            else if (orders[i].items[j] == "Martabak Coklat") menuPerformance[1].soldCount++;
            else if (orders[i].items[j] == "Martabak Keju") menuPerformance[2].soldCount++;
        }
    }

    // Sorting berdasarkan jumlah yang terjual
    for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (menuPerformance[i].soldCount < menuPerformance[j].soldCount) {
                MenuPerformance temp = menuPerformance[i];
                menuPerformance[i] = menuPerformance[j];
                menuPerformance[j] = temp;
            }
        }
    }

    cout << "Ranking Penjualan Menu:\n";
    for (int i = 0; i < 3; i++) {
        cout << menuPerformance[i].itemName << ": " << menuPerformance[i].soldCount << " pesanan" << endl;
    }
}

// Fungsi untuk menginput estimasi adonan harian
void inputDailyDoughEstimate() {
    cout << "\nInput Estimasi Adonan Harian:\n";
    cout << "Masukkan estimasi adonan untuk Martabak Kacang: ";
    cin >> dailyDoughEstimate[0];
    cout << "Masukkan estimasi adonan untuk Martabak Coklat: ";
    cin >> dailyDoughEstimate[1];
    cout << "Masukkan estimasi adonan untuk Martabak Keju: ";
    cin >> dailyDoughEstimate[2];

    cout << "\nEstimasi Adonan Harian:\n";
    cout << "Martabak Kacang: " << dailyDoughEstimate[0] << " adonan\n";
    cout << "Martabak Coklat: " << dailyDoughEstimate[1] << " adonan\n";
    cout << "Martabak Keju: " << dailyDoughEstimate[2] << " adonan\n";
}

// Fungsi untuk menu Owner
void ownerMenu() {
    int choice;
    do {
        cout << "\nMenu Owner:\n";
        cout << "1. Kitchen Management\n";
        cout << "2. Sales Analysis\n";
        cout << "3. Kembali ke Menu Awal\n";
        cout << "Pilih menu (1-3): ";
        cin >> choice;
        cin.ignore(); // Untuk membersihkan buffer

        switch (choice) {
            case 1:
                int kitchenChoice;
                do {
                    cout << "\nKitchen Management:\n";
                    cout << "1. Input Estimasi Adonan Harian\n";
                    cout << "2. Lihat Penggunaan Topping\n";
                    cout << "3. Kembali ke Menu Awal\n";
                    cout << "Pilih menu (1-3): ";
                    cin >> kitchenChoice;
                    cin.ignore();

                    switch (kitchenChoice) {
                        case 1:
                            inputDailyDoughEstimate();
                            break;
                        case 2:
                            viewToppingUsage();
                            break;
                        case 3:
                            return; // Kembali ke menu utama
                            break;
                        default:
                            cout << "Pilihan tidak valid, coba lagi.\n";
                    }
                } while (kitchenChoice != 3);
                break;

            case 2:
                int salesChoice;
                do {
                    cout << "\nSales Analysis:\n";
                    cout << "1. Lihat Ranking Penjualan Menu\n";
                    cout << "2. Lihat Laporan Pendapatan Harian\n";
                    cout << "3. Kembali ke Menu Awal\n";
                    cout << "Pilih menu (1-3): ";
                    cin >> salesChoice;
                    cin.ignore();

                    switch (salesChoice) {
                        case 1:
                            viewMenuPerformance();
                            break;
                        case 2:
                            viewDailySalesReport();
                            break;
                        case 3:
                            return; // Kembali ke menu utama
                            break;
                        default:
                            cout << "Pilihan tidak valid, coba lagi.\n";
                    }
                } while (salesChoice != 3);
                break;

            case 3:
                return; // Kembali ke menu utama
                break;

            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (choice != 3);
}

// Fungsi untuk menu Staff
void staffMenu() {
    int choice;
    do {
        cout << "\nMenu Staff:\n";
        cout << "1. Input Pesanan\n";
        cout << "2. Lihat Pesanan Aktif\n";
        cout << "3. Perbarui Status Pesanan\n";
        cout << "4. Lihat Laporan Pendapatan Harian\n";
        cout << "5. Kembali ke Menu Awal\n";
        cout << "Pilih opsi (1-5): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                takeOrder();
                break;
            case 2:
                viewActiveOrders();
                break;
            case 3:
                updateOrderStatus();
                break;
            case 4:
                viewDailySalesReport();
                break;
            case 5:
                return; // Kembali ke menu utama
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (choice != 5);
}

// Fungsi utama
int main() {
    int role;
    do {
        cout << "Masukkan peran (1 untuk Owner, 2 untuk Staff): ";
        cin >> role;
        cin.ignore(); // Untuk membersihkan buffer

        if (role == 1) {
            ownerMenu(); // Arahkan ke menu Owner
        } else if (role == 2) {
            staffMenu(); // Arahkan ke menu Staff
        } else {
            cout << "Peran tidak valid, coba lagi.\n";
        }
    } while (role != 1 && role != 2); // Tetap memilih peran yang valid

    return 0;
}

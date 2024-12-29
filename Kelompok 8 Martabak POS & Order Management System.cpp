// Kelompok 8 Martabak POS & Order Management System Final Project Implementasi Alprog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Order {
    int orderID;
    string customerName;
    string items[10];   
    double totalCost;
    string status;           
    string specialRequest;   
};

double calculateTotalCost(const string items[], int itemCount) {
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

bool isValidItem(const string& item) {
    string validItems[6] = {
        "Martabak Kacang", "Martabak Coklat", "Martabak Keju",
        "Topping Kacang", "Topping Coklat", "Topping Keju"
    };

    for (int i = 0; i < 6; ++i) {
        if (validItems[i] == item) {
            return true;
        }
    }
    return false;
}

void takeOrder(Order orders[], int& orderCount) {
    int orderID;
    string customerName, specialRequest;
    string items[10];
    string item;
    int itemCount = 0;

    cout << "Masukkan ID Pesanan: ";
    cin >> orderID;
    cin.ignore(); 
    cout << "Masukkan Nama Pelanggan: ";
    getline(cin, customerName);

    cout << "Masukkan item pesanan (ketik 'selesai' untuk berhenti):" << endl;
    while (true) {
        cout << "Item: ";
        getline(cin, item);
        if (item == "selesai") break;
        if (!isValidItem(item)) {
            cout << "Item tidak valid, coba lagi!" << endl;
            continue;
        }
        items[itemCount++] = item;
    }

    cout << "Masukkan permintaan khusus (atau ketik 'tidak' jika tidak ada): ";
    getline(cin, specialRequest);
    if (specialRequest == "tidak") {
        specialRequest = "Tidak ada permintaan khusus";
    }

    double totalCost = calculateTotalCost(items, itemCount);
    orders[orderCount++] = { orderID, customerName, {}, totalCost, "Menunggu", specialRequest };

    for (int i = 0; i < itemCount; ++i) {
        orders[orderCount - 1].items[i] = items[i];
    }

    cout << "Pesanan berhasil dibuat!" << endl;
    cout << "Total Biaya Pesanan: Rp" << fixed << setprecision(2) << totalCost << endl;
}

void viewActiveOrders(const Order orders[], int orderCount) {
    if (orderCount == 0) {
        cout << "Tidak ada pesanan aktif saat ini." << endl;
        return;
    }

    cout << "\nDaftar Pesanan Aktif:" << endl;
    cout << left << setw(10) << "ID Pesanan"
        << setw(20) << "Nama Pelanggan"
        << setw(15) << "Total Biaya"
        << setw(15) << "Status"
        << "Items" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < orderCount; ++i) {
        cout << left << setw(10) << orders[i].orderID
            << setw(20) << orders[i].customerName
            << setw(15) << fixed << setprecision(2) << orders[i].totalCost
            << setw(15) << orders[i].status;

        for (int j = 0; j < 10 && !orders[i].items[j].empty(); ++j) {
            cout << orders[i].items[j];
            if (j != 9 && !orders[i].items[j + 1].empty()) cout << ", ";
        }
        cout << endl;
        cout << "   Permintaan Khusus: " << orders[i].specialRequest << endl;
    }
}

void updateOrderStatus(Order orders[], int orderCount) {
    int orderID;
    string newStatus;

    cout << "Masukkan ID Pesanan yang ingin diperbarui: ";
    cin >> orderID;
    cin.ignore(); 
    cout << "Masukkan Status Baru (Menunggu, Dalam Proses, Selesai): ";
    getline(cin, newStatus);

    if (newStatus != "Menunggu" && newStatus != "Dalam Proses" && newStatus != "Selesai") {
        cout << "Status tidak valid! Harus 'Menunggu', 'Dalam Proses', atau 'Selesai'." << endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i].orderID == orderID) {
            orders[i].status = newStatus;
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Status pesanan berhasil diperbarui!" << endl;
    }
    else {
        cout << "Pesanan tidak ditemukan!" << endl;
    }
}

void viewToppingUsage(const Order orders[], int orderCount) {
    int kacang = 0, coklat = 0, keju = 0;

    for (int i = 0; i < orderCount; ++i) {
        for (int j = 0; j < 10 && !orders[i].items[j].empty(); ++j) {
            if (orders[i].items[j] == "Topping Kacang") kacang++;
            else if (orders[i].items[j] == "Topping Coklat") coklat++;
            else if (orders[i].items[j] == "Topping Keju") keju++;
        }
    }

    cout << "Laporan Penggunaan Topping:" << endl;
    cout << "Topping Kacang: " << kacang << " porsi" << endl;
    cout << "Topping Coklat: " << coklat << " porsi" << endl;
    cout << "Topping Keju: " << keju << " porsi" << endl;
}

void viewDailySalesReport(const Order orders[], int orderCount) {
    double totalSales = 0.0;
    for (int i = 0; i < orderCount; ++i) {
        totalSales += orders[i].totalCost;
    }

    cout << "Laporan Pendapatan Hari Ini: Rp" << fixed << setprecision(2) << totalSales << endl;
}

void viewMenuPerformance(const Order orders[], int orderCount) {
    int martabakKacang = 0, martabakCoklat = 0, martabakKeju = 0;

    for (int i = 0; i < orderCount; ++i) {
        for (int j = 0; j < 10 && !orders[i].items[j].empty(); ++j) {
            if (orders[i].items[j] == "Martabak Kacang") martabakKacang++;
            else if (orders[i].items[j] == "Martabak Coklat") martabakCoklat++;
            else if (orders[i].items[j] == "Martabak Keju") martabakKeju++;
        }
    }

    cout << "Ranking Penjualan Menu:" << endl;
    cout << "Martabak Kacang: " << martabakKacang << " pesanan" << endl;
    cout << "Martabak Coklat: " << martabakCoklat << " pesanan" << endl;
    cout << "Martabak Keju: " << martabakKeju << " pesanan" << endl;
}

void inputProductionPlanning() {
    int martabakKacangQty, martabakCoklatQty, martabakKejuQty;

    cout << "Masukkan estimasi jumlah Martabak Kacang yang terjual: ";
    cin >> martabakKacangQty;
    cout << "Masukkan estimasi jumlah Martabak Coklat yang terjual: ";
    cin >> martabakCoklatQty;
    cout << "Masukkan estimasi jumlah Martabak Keju yang terjual: ";
    cin >> martabakKejuQty;

    int totalAdonan = martabakKacangQty + martabakCoklatQty + martabakKejuQty;
    cout << "Total estimasi adonan yang diperlukan: " << totalAdonan << " martabak." << endl;
}

int main() {
    Order orders[100];  
    int orderCount = 0;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Input Pesanan\n";
        cout << "2. Lihat Pesanan Aktif\n";
        cout << "3. Perbarui Status Pesanan\n";
        cout << "4. Lihat Penggunaan Topping\n";
        cout << "5. Lihat Laporan Pendapatan Harian\n";
        cout << "6. Lihat Performa Menu\n";
        cout << "7. Input Estimasi Adonan Harian\n";
        cout << "8. Keluar\n";
        cout << "Pilih opsi (1-8): ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            takeOrder(orders, orderCount);
            break;
        case 2:
            viewActiveOrders(orders, orderCount);
            break;
        case 3:
            updateOrderStatus(orders, orderCount);
            break;
        case 4:
            viewToppingUsage(orders, orderCount);
            break;
        case 5:
            viewDailySalesReport(orders, orderCount);
            break;
        case 6:
            viewMenuPerformance(orders, orderCount);
            break;
        case 7:
            inputProductionPlanning();
            break;
        case 8:
            cout << "Keluar dari program...\n";
            return 0;  
        default:
            cout << "Opsi tidak valid, coba lagi!" << endl;
        }
    }

    return 0;
}
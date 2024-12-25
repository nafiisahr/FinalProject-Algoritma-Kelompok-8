#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Order {
    int orderID;
    string customerName;
    vector<string> items;
    double totalCost;
    string status;           
    string specialRequest;   
};

double calculateTotalCost(const vector<string>& items) {
    double cost = 0.0;
    for (const auto& item : items) {
        if (item == "Martabak Kacang") cost += 65000;
        else if (item == "Martabak Coklat") cost += 70000;
        else if (item == "Martabak Keju") cost += 65000;
        else if (item == "Topping Kacang") cost += 6000;
        else if (item == "Topping Coklat") cost += 10000;
        else if (item == "Topping Keju") cost += 8000;
    }
    return cost;
}

bool isValidItem(const string& item) {
    vector<string> validItems = {
        "Martabak Kacang", "Martabak Coklat", "Martabak Keju",
        "Topping Kacang", "Topping Coklat", "Topping Keju"
    };
    return find(validItems.begin(), validItems.end(), item) != validItems.end();
}

void takeOrder(vector<Order>& orders) {
    int orderID;
    string customerName, specialRequest;
    vector<string> items;
    string item;

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
        items.push_back(item);
    }

    cout << "Masukkan permintaan khusus (atau ketik 'tidak' jika tidak ada): ";
    getline(cin, specialRequest);
    if (specialRequest == "tidak") {
        specialRequest = "Tidak ada permintaan khusus";
    }

    double totalCost = calculateTotalCost(items);
    orders.push_back({ orderID, customerName, items, totalCost, "Menunggu", specialRequest });

    cout << "Pesanan berhasil dibuat!" << endl;
    cout << "Total Biaya Pesanan: Rp" << fixed << setprecision(2) << totalCost << endl;
}

void viewActiveOrders(const vector<Order>& orders) {
    if (orders.empty()) {
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

    for (const auto& order : orders) {
        cout << left << setw(10) << order.orderID
            << setw(20) << order.customerName
            << setw(15) << fixed << setprecision(2) << order.totalCost
            << setw(15) << order.status;

        for (size_t i = 0; i < order.items.size(); ++i) {
            cout << order.items[i];
            if (i != order.items.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "   Permintaan Khusus: " << order.specialRequest << endl;
    }
}

void updateOrderStatus(vector<Order>& orders) {
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
    for (auto& order : orders) {
        if (order.orderID == orderID) {
            order.status = newStatus;
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

void viewToppingUsage(const vector<Order>& orders) {
    int kacang = 0, coklat = 0, keju = 0;

    for (const auto& order : orders) {
        for (const auto& item : order.items) {
            if (item == "Topping Kacang") kacang++;
            else if (item == "Topping Coklat") coklat++;
            else if (item == "Topping Keju") keju++;
        }
    }

    cout << "Laporan Penggunaan Topping:" << endl;
    cout << "Topping Kacang: " << kacang << " porsi" << endl;
    cout << "Topping Coklat: " << coklat << " porsi" << endl;
    cout << "Topping Keju: " << keju << " porsi" << endl;
}

void viewDailySalesReport(const vector<Order>& orders) {
    double totalSales = 0.0;
    for (const auto& order : orders) {
        totalSales += order.totalCost;
    }

    cout << "Laporan Pendapatan Hari Ini: Rp" << fixed << setprecision(2) << totalSales << endl;
}

void viewMenuPerformance(const vector<Order>& orders) {
    int martabakKacang = 0, martabakCoklat = 0, martabakKeju = 0;

    for (const auto& order : orders) {
        for (const auto& item : order.items) {
            if (item == "Martabak Kacang") martabakKacang++;
            else if (item == "Martabak Coklat") martabakCoklat++;
            else if (item == "Martabak Keju") martabakKeju++;
        }
    }

    vector<pair<string, int>> menuSales = {
        {"Martabak Kacang", martabakKacang},
        {"Martabak Coklat", martabakCoklat},
        {"Martabak Keju", martabakKeju}
    };

    sort(menuSales.begin(), menuSales.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
        });

    cout << "Ranking Penjualan Menu:" << endl;
    for (const auto& menu : menuSales) {
        cout << menu.first << ": " << menu.second << " pesanan" << endl;
    }
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
    vector<Order> orders;
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
            takeOrder(orders);
            break;
        case 2:
            viewActiveOrders(orders);
            break;
        case 3:
            updateOrderStatus(orders);
            break;
        case 4:
            viewToppingUsage(orders);
            break;
        case 5:
            viewDailySalesReport(orders);
            break;
        case 6:
            viewMenuPerformance(orders);
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
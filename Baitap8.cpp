#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <ctime>

using namespace std;

class SavingsAccount {
public:
    string accountCode;
    string accountType;
    string customerName;
    string idNumber;
    string openingDate;
    double depositAmount;

    SavingsAccount(string code, string type, string name, string id, string date, double amount)
        : accountCode(code), accountType(type), customerName(name), idNumber(id), openingDate(date), depositAmount(amount) {}

    void printInfo() const {
        cout << "Ma so: " << accountCode << "\n"
             << "Loai tiet kiem: " << accountType << "\n"
             << "Ho ten khach hang: " << customerName << "\n"
             << "Chung minh nhan dan: " << idNumber << "\n"
             << "Ngay mo so: " << openingDate << "\n"
             << "So tien gui: " << depositAmount << "\n";
    }
};

// Kiem tra ma so co dung khong
bool isValidAccountCode(const string& code) {
    return regex_match(code, regex("^[A-Za-z0-9]{1,5}$"));
}

// Kiem tra loai tiet kiem co dung khong
bool isValidAccountType(const string& type) {
    return regex_match(type, regex("^[A-Za-z\\s]{1,10}$"));
}
// Kiem tra ho ten khach hang co dung khong
bool isValidCustomerName(const string& name) {
    return regex_match(name, regex("^[A-Za-z\\s]{1,30}$"));
}

// Kiem tra CMND co dung khong
bool isValidIDNumber(const string& id) {
    return regex_match(id, regex("^\\d{9}$|^\\d{12}$"));
}

// Kiem tra ngay mo so co dung khong
bool isValidDate(const string& date) {
    return regex_match(date, regex("^\\d{2}/\\d{2}/\\d{4}$"));
}

// Kiem tra so tien gui co dung khong
bool isValidAmount(double amount) {
    return amount > 0;
}

// Nhap thong tin 
void inputAccountInfo(vector<SavingsAccount>& accounts) {
    int n;
    cout << "Nhap so luong so tiet kiem: ";
    cin >> n;
    cin.ignore(); 

    for (int i = 0; i < n; ++i) {
        string code, type, name, id, date;
        double amount;

        cout << "Nhap thong tin cho so tiet kiem thu " << i + 1 << ":\n";

        do {
            cout << "Ma so: ";
            getline(cin, code);
            if (!isValidAccountCode(code)) {
                cout << "Ma so khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidAccountCode(code));

        do {
            cout << "Loai tiet kiem: ";
            getline(cin, type);
            if (!isValidAccountType(type)) {
                cout << "Loai tiet kiem khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidAccountType(type));

        do {
            cout << "Ho ten khach hang: ";
            getline(cin, name);
            if (!isValidCustomerName(name)) {
                cout << "Ho ten khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidCustomerName(name));

        do {
            cout << "Chung minh nhan dan: ";
            getline(cin, id);
            if (!isValidIDNumber(id)) {
                cout << "Chung minh nhan dan khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidIDNumber(id));

        do {
            cout << "Ngay mo so (dd/mm/yyyy): ";
            getline(cin, date);
            if (!isValidDate(date)) {
                cout << "Ngay mo so khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidDate(date));

        do {
            cout << "So tien gui: ";
            cin >> amount;
            if (!isValidAmount(amount)) {
                cout << "So tien gui khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidAmount(amount));

        cin.ignore(); 

        accounts.emplace_back(code, type, name, id, date, amount);
    }
}

void updateInterestRate(vector<SavingsAccount>& accounts, double rate) {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    for (auto& account : accounts) {
        int day, month, year;
        sscanf(account.openingDate.c_str(), "%d/%d/%d", &day, &month, &year);

        tm openDate = {0};
        openDate.tm_mday = day;
        openDate.tm_mon = month - 1;
        openDate.tm_year = year - 1900;

        double diff = difftime(now, mktime(&openDate)) / (60 * 60 * 24 * 30); // số tháng

        double interest = 0;
        if (account.accountType == "ngan han" && diff <= 6) {
            interest = account.depositAmount * rate * diff / 12;
        } else if (account.accountType == "dai han" && diff > 6) {
            interest = account.depositAmount * rate * diff / 12;
        } else {
            interest = account.depositAmount * 0.005 * diff / 12; // lãi suất thấp hơn nếu rút trước hạn
        }

        cout << "So tien lai cua so " << account.accountCode << " la: " << interest << "\n";
    }
}

// Rut tien
void withdrawMoney(vector<SavingsAccount>& accounts, const string& code, double amount) {
    for (auto& account : accounts) {
        if (account.accountCode == code) {
            if (amount > account.depositAmount) {
                cout << "So tien rut vuot qua so tien gui. Vui long nhap lai.\n";
                return;
            }

            account.depositAmount -= amount;
            cout << "So tien con lai trong so " << account.accountCode << " la: " << account.depositAmount << "\n";
            return;
        }
    }
    cout << "Khong tim thay so tiet kiem voi ma " << code << ".\n";
}

// Tim kiem voi ma so hoac CMND
void searchAccountByIDOrCode(const vector<SavingsAccount>& accounts, const string& keyword) {
    for (const auto& account : accounts) {
        if (account.idNumber == keyword || account.accountCode == keyword) {
            account.printInfo();
            cout << "-------------------\n";
        }
    }
}

// Liet ke cac so tiet kiem mo trong thoi gian xac dinh
void listAccountsInTimeRange(const vector<SavingsAccount>& accounts, const string& startDate, const string& endDate) {
    for (const auto& account : accounts) {
        if (account.openingDate >= startDate && account.openingDate <= endDate) {
            account.printInfo();
            cout << "-------------------\n";
        }
    }
}

// Ham so sanh
int cmp1(SavingsAccount &a, SavingsAccount &b){
   return a.depositAmount > b.depositAmount;
}

// Sap xep theo so tien
void sortAccountsByAmount(vector<SavingsAccount>& accounts) {
    sort(accounts.begin(), accounts.end(),cmp1);
}

// Ham so sanh
int cmp2(SavingsAccount &a, SavingsAccount &b){
   return a.openingDate < b.openingDate;
}

// Sap xep theo ngay
void sortAccountsByDate(vector<SavingsAccount>& accounts) {
    sort(accounts.begin(), accounts.end(),cmp2);
}

int main() {
    vector<SavingsAccount> accounts;
    inputAccountInfo(accounts);

    cout << "\nDanh sach so tiet kiem:\n";
    for (const auto& account : accounts) {
        account.printInfo();
        cout << "-------------------\n";
    }

    double rate;
    cout << "\nNhap lai suat (%/nam): ";
    cin >> rate;
    updateInterestRate(accounts, rate / 100);

    string code;
    double amount;
    cout << "\nNhap ma so va so tien can rut: ";
    cin >> code >> amount;
    withdrawMoney(accounts, code, amount);

    string keyword;
    cout << "\nNhap CMND va ma so can tim: ";
    cin >> keyword;
    searchAccountByIDOrCode(accounts, keyword);

    string startDate, endDate;
    cout << "\nNhap khoang thoi gian (dd/mm/yyyy - dd/mm/yyyy): ";
    cin >> startDate >> endDate;
    listAccountsInTimeRange(accounts, startDate, endDate);

    cout << "\nDanh sach so tiet kiem sap xep theo so tien giam dan:\n";
    sortAccountsByAmount(accounts);
    for (const auto& account : accounts) {
        account.printInfo();
        cout << "-------------------\n";
    }

    cout << "\nDanh sach so tiet kiem sap xep theo ngay mo so tang dan:\n";
    sortAccountsByDate(accounts);
    for (const auto& account : accounts) {
        account.printInfo();
        cout << "-------------------\n";
    }

    return 0;
}

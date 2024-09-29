#include<bits/stdc++.h>
using namespace std;

class ChuyenBay {
private:
    string maChuyenBay;
    string ngayBay;
    string gioBay;
    string noiDi;
    string noiDen;

public:
    ChuyenBay(string ma, string ngay, string gio, string di, string den)
        : maChuyenBay(ma), ngayBay(ngay), gioBay(gio), noiDi(di), noiDen(den) {}

    string getMaChuyenBay() const { return maChuyenBay; }
    string getNgayBay() const { return ngayBay; }
    string getGioBay() const { return gioBay; }
    string getNoiDi() const { return noiDi; }
    string getNoiDen() const { return noiDen; }

    static bool kiemTraMaChuyenBay(const  string& ma) {
        return  regex_match(ma,  regex("^[A-Za-z0-9]{1,5}$"));
    }

    static bool kiemTraNgayBay(const  string& ngay) {
        regex pattern("^\\d{2}/\\d{2}/\\d{4}$");
        if (! regex_match(ngay, pattern)) return false;

        istringstream iss(ngay);
        int day, month, year;
        char delimiter;
        iss >> day >> delimiter >> month >> delimiter >> year;

        if (month < 1 || month > 12 || day < 1 || year < 1) return false;

        int daysInMonth[] = { 31, (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return day <= daysInMonth[month - 1];
    }

    static bool kiemTraGioBay(const  string& gio) {
        return  regex_match(gio,  regex("^([01]\\d|2[0-3]):([0-5]\\d)$"));
    }

    static bool kiemTraDiaDanh(const  string& diaDanh) {
        return  regex_match(diaDanh,  regex("^[A-Za-z\\s]{1,20}$"));
    }

    void hienThi() const {
        cout << "Ma chuyen bay: " << maChuyenBay << "\nNgay bay: " << ngayBay << "\nGio bay: " << gioBay
             << "\nNoi di: " << noiDi << "\nNoi den: " << noiDen << "\n";
    }
};
void nhapChuyenBay( vector<ChuyenBay>& danhSach) {
    string ma, ngay, gio, di, den;

    cout << "Nhap ma chuyen bay: ";
    cin >> ma;
    while (!ChuyenBay::kiemTraMaChuyenBay(ma)) {
        cout << "Ma chuyen bay khong hop le. Nhap lai: ";
        cin >> ma;
    }

    cout << "Nhap ngay bay (dd/mm/yyyy): ";
    cin >> ngay;
    while (!ChuyenBay::kiemTraNgayBay(ngay)) {
        cout << "Ngay bay khong hop le. Nhap lai: ";
        cin >> ngay;
    }

    cout << "Nhap gio bay (hh:mm): ";
    cin >> gio;
    while (!ChuyenBay::kiemTraGioBay(gio)) {
        cout << "Gio bay khong hop le. Nhap lai: ";
        cin >> gio;
    }

    cout << "Nhap noi di: ";
    cin.ignore();
    getline( cin, di);
    while (!ChuyenBay::kiemTraDiaDanh(di)) {
        cout << "Noi di khong hop le. Nhap lai: ";
        getline( cin, di);
    }

    cout << "Nhap noi den: ";
    getline( cin, den);
    while (!ChuyenBay::kiemTraDiaDanh(den)) {
        cout << "Noi den khong hop le. Nhap lai: ";
        getline( cin, den);
    }

    danhSach.emplace_back(ma, ngay, gio, di, den);
}

void hienThiDanhSach(const  vector<ChuyenBay>& danhSach) {
    for (const auto& cb : danhSach) {
        cb.hienThi();
        cout << "-------------------------\n";
    }
}
void timKiemChuyenBay(const  vector<ChuyenBay>& danhSach, const  string& tuKhoa) {
    for (const auto& cb : danhSach) {
        if (cb.getMaChuyenBay() == tuKhoa || cb.getNoiDi() == tuKhoa || cb.getNoiDen() == tuKhoa) {
            cb.hienThi();
            cout << "-------------------------\n";
        }
    }
}

int cmp(ChuyenBay &a , ChuyenBay &b) {
    if (a.getNgayBay() != b.getNgayBay()) return a.getNgayBay() < b.getNgayBay();
    return a.getGioBay() < b.getGioBay();
}

void sapXepChuyenBay( vector<ChuyenBay>& danhSach) {
    sort(danhSach.begin(), danhSach.end(), cmp);
}
void hienThiChuyenBayTheoNoiDi(const  vector<ChuyenBay>& danhSach, const  string& noiDi, const  string& ngay) {
    for (const auto& cb : danhSach) {
        if (cb.getNoiDi() == noiDi && cb.getNgayBay() == ngay) {
            cb.hienThi();
            cout << "-------------------------\n";
        }
    }
}

int demChuyenBay(const  vector<ChuyenBay>& danhSach, const  string& noiDi, const  string& noiDen) {
    int count = 0;
    for (const auto& cb : danhSach) {
        if (cb.getNoiDi() == noiDi && cb.getNoiDen() == noiDen) {
            count++;
        }
    }
    return count;
}
int main() {
    vector<ChuyenBay> danhSach;
    int luaChon;

    do {
        cout << "1. Nhap chuyen bay\n2. Hien thi danh sach chuyen bay\n3. Tim kiem chuyen bay\n4. Sap xep chuyen bay\n5. Hien thi chuyen bay theo noi di\n6. Dem chuyen bay\n0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1:
            nhapChuyenBay(danhSach);
            break;
        case 2:
            hienThiDanhSach(danhSach);
            break;
        case 3: {
            string tuKhoa;
            cout << "Nhap ma chuyen bay, noi di hoac noi den: ";
            cin.ignore();
            getline( cin, tuKhoa);
            timKiemChuyenBay(danhSach, tuKhoa);
            break;
        }
        case 4:
            sapXepChuyenBay(danhSach);
            break;
        case 5: {
            string noiDi, ngay;
            cout << "Nhap noi di: ";
            cin.ignore();
            getline( cin, noiDi);
            cout << "Nhap ngay (dd/mm/yyyy): ";
            getline( cin, ngay);
            hienThiChuyenBayTheoNoiDi(danhSach, noiDi, ngay);
            break;
        }
        case 6: {
            string noiDi, noiDen;
            cout << "Nhap noi di: ";
            cin.ignore();
            getline( cin, noiDi);
            cout << "Nhap noi den: ";
            getline( cin, noiDen);
            int count = demChuyenBay(danhSach, noiDi, noiDen);
            cout << "So luong chuyen bay tu " << noiDi << " den " << noiDen << " la: " << count << "\n";
            break;
        }
        case 0:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            break;
        }
    } while (luaChon != 0);

    return 0;
}

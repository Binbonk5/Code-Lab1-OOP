#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <sstream>
#include <iomanip> // Thêm thư viện này
#include <ctime>

class SoTietKiem {
private:
    std::string maSo;
    std::string loaiTietKiem;
    std::string hoTenKhachHang;
    std::string cmnd;
    std::string ngayMoSo;
    double soTienGui;

public:
    SoTietKiem(std::string ma, std::string loai, std::string hoTen, std::string cmnd, std::string ngay, double soTien)
        : maSo(ma), loaiTietKiem(loai), hoTenKhachHang(hoTen), cmnd(cmnd), ngayMoSo(ngay), soTienGui(soTien) {}

    std::string getMaSo() const { return maSo; }
    std::string getLoaiTietKiem() const { return loaiTietKiem; }
    std::string getHoTenKhachHang() const { return hoTenKhachHang; }
    std::string getCMND() const { return cmnd; }
    std::string getNgayMoSo() const { return ngayMoSo; }
    double getSoTienGui() const { return soTienGui; }
     void setSoTienGui(double soTien) { soTienGui = soTien; }
    static bool kiemTraMaSo(const std::string& ma) {
        return std::regex_match(ma, std::regex("^[A-Za-z0-9]{1,5}$"));
    }

    static bool kiemTraLoaiTietKiem(const std::string& loai) {
        return std::regex_match(loai, std::regex("^[A-Za-z\\s]{1,10}$"));
    }

    static bool kiemTraHoTen(const std::string& hoTen) {
        return std::regex_match(hoTen, std::regex("^[A-Za-z\\s]{1,30}$"));
    }

    static bool kiemTraCMND(const std::string& cmnd) {
        return std::regex_match(cmnd, std::regex("^\\d{9}$|^\\d{12}$"));
    }

    static bool kiemTraNgayMoSo(const std::string& ngay) {
        std::regex pattern("^\\d{2}/\\d{2}/\\d{4}$");
        if (!std::regex_match(ngay, pattern)) return false;

        std::istringstream iss(ngay);
        int day, month, year;
        char delimiter;
        iss >> day >> delimiter >> month >> delimiter >> year;

        if (month < 1 || month > 12 || day < 1 || year < 1) return false;

        int daysInMonth[] = { 31, (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return day <= daysInMonth[month - 1];
    }

    static bool kiemTraSoTienGui(double soTien) {
        return soTien > 0;
    }

    void hienThi() const {
        std::cout << "Ma so: " << maSo << "\nLoai tiet kiem: " << loaiTietKiem << "\nHo ten khach hang: " << hoTenKhachHang
                  << "\nCMND: " << cmnd << "\nNgay mo so: " << ngayMoSo << "\nSo tien gui: " << soTienGui << "\n";
    }
};
void nhapSoTietKiem(std::vector<SoTietKiem>& danhSach) {
    std::string ma, loai, hoTen, cmnd, ngay;
    double soTien;

    std::cout << "Nhap ma so: ";
    std::cin >> ma;
    while (!SoTietKiem::kiemTraMaSo(ma)) {
        std::cout << "Ma so khong hop le. Nhap lai: ";
        std::cin >> ma;
    }

    std::cout << "Nhap loai tiet kiem: ";
    std::cin.ignore();
    std::getline(std::cin, loai);
    while (!SoTietKiem::kiemTraLoaiTietKiem(loai)) {
        std::cout << "Loai tiet kiem khong hop le. Nhap lai: ";
        std::getline(std::cin, loai);
    }

    std::cout << "Nhap ho ten khach hang: ";
    std::getline(std::cin, hoTen);
    while (!SoTietKiem::kiemTraHoTen(hoTen)) {
        std::cout << "Ho ten khong hop le. Nhap lai: ";
        std::getline(std::cin, hoTen);
    }

    std::cout << "Nhap CMND: ";
    std::cin >> cmnd;
    while (!SoTietKiem::kiemTraCMND(cmnd)) {
        std::cout << "CMND khong hop le. Nhap lai: ";
        std::cin >> cmnd;
    }

    std::cout << "Nhap ngay mo so (dd/mm/yyyy): ";
    std::cin >> ngay;
    while (!SoTietKiem::kiemTraNgayMoSo(ngay)) {
        std::cout << "Ngay mo so khong hop le. Nhap lai: ";
        std::cin >> ngay;
    }

    std::cout << "Nhap so tien gui: ";
    std::cin >> soTien;
    while (!SoTietKiem::kiemTraSoTienGui(soTien)) {
        std::cout << "So tien gui phai la so duong. Nhap lai: ";
        std::cin >> soTien;
    }

    danhSach.emplace_back(ma, loai, hoTen, cmnd, ngay, soTien);
}

void hienThiDanhSach(const std::vector<SoTietKiem>& danhSach) {
    for (const auto& stk : danhSach) {
        stk.hienThi();
        std::cout << "-------------------------\n";
    }
}
void capNhatLaiSuat(std::vector<SoTietKiem>& danhSach, double laiSuat) {
    for (auto& stk : danhSach) {
        double soTienLai = 0;
        if (stk.getLoaiTietKiem() == "ngan han") {
            soTienLai = stk.getSoTienGui() * (laiSuat / 100) * 0.5; // Giả sử kỳ hạn ngắn là 6 tháng
        } else if (stk.getLoaiTietKiem() == "dai han") {
            soTienLai = stk.getSoTienGui() * (laiSuat / 100); // Giả sử kỳ hạn dài là 1 năm
        }
        std::cout << "So tien lai cua so tiet kiem " << stk.getMaSo() << " la: " << soTienLai << "\n";
    }
}

void tinhTienLai(const SoTietKiem& stk) {
    std::tm tm = {};
    std::istringstream ss(stk.getNgayMoSo());
    ss >> std::get_time(&tm, "%d/%m/%Y");
    std::time_t ngayMoSo = std::mktime(&tm);

    std::time_t hienTai = std::time(nullptr);
    double soNgayGui = std::difftime(hienTai, ngayMoSo) / (60 * 60 * 24);

    double laiSuat = (stk.getLoaiTietKiem() == "ngan han") ? 0.5 : 1.0; // Giả sử lãi suất ngắn hạn là 0.5%/năm và dài hạn là 1%/năm
    double soTienLai = stk.getSoTienGui() * (laiSuat / 100) * (soNgayGui / 365);

    std::cout << "So tien lai cua so tiet kiem " << stk.getMaSo() << " la: " << soTienLai << "\n";
}

void rutTien(SoTietKiem& stk, double soTienRut) {
    if (soTienRut > stk.getSoTienGui()) {
        std::cout << "So tien rut vuot qua so tien gui. Khong the rut.\n";
    } else {
         stk.setSoTienGui(stk.getSoTienGui() - soTienRut);
        std::cout << "Rut tien thanh cong. So tien con lai trong so: " << stk.getSoTienGui() << "\n";
    }
}
void timKiemSoTietKiem(const std::vector<SoTietKiem>& danhSach, const std::string& tuKhoa) {
    for (const auto& stk : danhSach) {
        if (stk.getMaSo() == tuKhoa || stk.getCMND() == tuKhoa) {
            stk.hienThi();
            std::cout << "-------------------------\n";
        }
    }
}

void lietKeSoTietKiemTheoThoiGian(const std::vector<SoTietKiem>& danhSach, const std::string& ngayBatDau, const std::string& ngayKetThuc) {
    std::tm tmBatDau = {}, tmKetThuc = {};
    std::istringstream ssBatDau(ngayBatDau), ssKetThuc(ngayKetThuc);
    ssBatDau >> std::get_time(&tmBatDau, "%d/%m/%Y");
    ssKetThuc >> std::get_time(&tmKetThuc, "%d/%m/%Y");
    std::time_t timeBatDau = std::mktime(&tmBatDau);
    std::time_t timeKetThuc = std::mktime(&tmKetThuc);

    for (const auto& stk : danhSach) {
        std::tm tmMoSo = {};
        std::istringstream ssMoSo(stk.getNgayMoSo());
        ssMoSo >> std::get_time(&tmMoSo, "%d/%m/%Y");
        std::time_t timeMoSo = std::mktime(&tmMoSo);

        if (timeMoSo >= timeBatDau && timeMoSo <= timeKetThuc) {
            stk.hienThi();
            std::cout << "-------------------------\n";
        }
    }
}

int cmp(SoTietKiem &a, SoTietKiem &b) {
    return a.getSoTienGui() > b.getSoTienGui();
}

void sapXepTheoSoTienGui(std::vector<SoTietKiem>& danhSach) {
    std::sort(danhSach.begin(), danhSach.end(), cmp);
}

int cmp2(SoTietKiem &a, SoTietKiem &b) {
    std::tm tmA = {}, tmB = {};
    std::istringstream ssA(a.getNgayMoSo()), ssB(b.getNgayMoSo());
    ssA >> std::get_time(&tmA, "%d/%m/%Y");
    ssB >> std::get_time(&tmB, "%d/%m/%Y");
    return std::mktime(&tmA) < std::mktime(&tmB);
}

void sapXepTheoNgayMoSo(std::vector<SoTietKiem>& danhSach) {
    std::sort(danhSach.begin(), danhSach.end(), cmp2);
}
int main() {
    std::vector<SoTietKiem> danhSach;
    int luaChon;

    do {
        std::cout << "1. Nhap so tiet kiem\n2. Hien thi danh sach so tiet kiem\n3. Tim kiem so tiet kiem\n4. Sap xep so tiet kiem\n5. Liet ke so tiet kiem theo thoi gian\n6. Cap nhat lai suat\n7. Tinh tien lai\n8. Rut tien\n0. Thoat\n";
        std::cout << "Nhap lua chon: ";
        std::cin >> luaChon;

        switch (luaChon) {
        case 1:
            nhapSoTietKiem(danhSach);
            break;
        case 2:
            hienThiDanhSach(danhSach);
            break;
        case 3: {
            std::string tuKhoa;
            std::cout << "Nhap ma so hoac CMND: ";
            std::cin.ignore();
            std::getline(std::cin, tuKhoa);
            timKiemSoTietKiem(danhSach, tuKhoa);
            break;
        }
        case 4: {
            int luaChonSapXep;
            std::cout << "1. Sap xep theo so tien gui\n2. Sap xep theo ngay mo so\n";
            std::cout << "Nhap lua chon: ";
            std::cin >> luaChonSapXep;
            if (luaChonSapXep == 1) {
                sapXepTheoSoTienGui(danhSach);
            } else if (luaChonSapXep == 2) {
                sapXepTheoNgayMoSo(danhSach);
            } else {
                std::cout << "Lua chon khong hop le.\n";
            }
            break;
        }
        case 5: {
            std::string ngayBatDau, ngayKetThuc;
            std::cout << "Nhap ngay bat dau (dd/mm/yyyy): ";
            std::cin.ignore();
            std::getline(std::cin, ngayBatDau);
            std::cout << "Nhap ngay ket thuc (dd/mm/yyyy): ";
            std::getline(std::cin, ngayKetThuc);
            lietKeSoTietKiemTheoThoiGian(danhSach, ngayBatDau, ngayKetThuc);
            break;
        }
        case 6: {
            double laiSuat;
            std::cout << "Nhap lai suat (%/nam): ";
            std::cin >> laiSuat;
            capNhatLaiSuat(danhSach, laiSuat);
            break;
        }
        case 7: {
            std::string maSo;
            std::cout << "Nhap ma so tiet kiem: ";
            std::cin.ignore();
            std::getline(std::cin, maSo);
            for (const auto& stk : danhSach) {
                if (stk.getMaSo() == maSo) {
                    tinhTienLai(stk);
                    break;
                }
            }
            break;
        }
        case 8: {
            std::string maSo;
            double soTienRut;
            std::cout << "Nhap ma so tiet kiem: ";
            std::cin.ignore();
            std::getline(std::cin, maSo);
            std::cout << "Nhap so tien can rut: ";
            std::cin >> soTienRut;
            for (auto& stk : danhSach) {
                if (stk.getMaSo() == maSo) {
                    rutTien(stk, soTienRut);
                    break;
                }
            }
            break;
        }
        case 0:
            std::cout << "Thoat chuong trinh.\n";
            break;
        default:
            std::cout << "Lua chon khong hop le. Vui long chon lai.\n";
            break;
        }
    } while (luaChon != 0);

    return 0;
}

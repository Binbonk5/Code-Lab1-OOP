#include <bits/stdc++.h>
using namespace std;

class PhanSo {
private:
	int tu;
	int mau;

public:
	PhanSo() : tu(0), mau(1) {}

	PhanSo(int tu, int mau) : tu(tu), mau(mau) {}

	void Nhap() {
		cin >> tu >> mau;
	}
	bool Check() {
		if (mau == 0)return false;
		return true;
	}

	void Xuat() const {
		cout << tu << "/" << mau << endl;
	}

	void Rutgon() {
		int gcd = __gcd(tu, mau);
		if (tu * mau < 0) gcd *= -1;
		tu /= gcd;
		mau /= gcd;
	}

	PhanSo Tong(const PhanSo& other) const {
		int TuMoi = tu * other.mau + mau * other.tu;
		int MauMoi = mau * other.mau;
		PhanSo PsMoi(TuMoi, MauMoi);
		PsMoi.Rutgon();
		return PsMoi;
	}

	PhanSo Hieu(const PhanSo& other) const {
		int TuMoi = tu * other.mau - mau * other.tu;
		int MauMoi = mau * other.mau;
		PhanSo PsMoi(TuMoi, MauMoi);
		PsMoi.Rutgon();
		return PsMoi;
	}

	PhanSo Tich(const PhanSo& other) const {
		int TuMoi = tu * other.tu;
		int MauMoi = mau * other.mau;
		PhanSo PsMoi(TuMoi, MauMoi);
		PsMoi.Rutgon();
		return PsMoi;
	}

	PhanSo Thuong(const PhanSo& other) const {
		int TuMoi = tu * other.mau;
		int MauMoi = mau * other.tu;
		PhanSo PsMoi(TuMoi, MauMoi);
		PsMoi.Rutgon();
		return PsMoi;
	}
};

int main() {
	PhanSo ps1, ps2;
	cout << "Nhap tu va mau cua phan so thu nhat: ";

	while (1) {
		ps1.Nhap();
		if (ps1.Check() == true) {
			break;
		}
		cout << "Nhap lai tu va mau. Chu y mau khong duoc bang 0: ";
	}

	cout << "Nhap tu va mau cua phan so thu hai: ";

	while (1) {
		ps2.Nhap();
		if (ps2.Check() == true) {
			break;
		}
		cout << "Nhap lai tu va mau. Chu y mau khong duoc bang 0: ";
	}

	PhanSo Tong = ps1.Tong(ps2);
	PhanSo Hieu = ps1.Hieu(ps2);
	PhanSo Tich = ps1.Tich(ps2);
	PhanSo Thuong = ps1.Thuong(ps2);

	cout << "Tong hai phan so: ";
	Tong.Xuat();

	cout << "Hieu hai phan so: ";
	Hieu.Xuat();

	cout << "Tich hai phan so: ";
	Tich.Xuat();

	cout << "Thuong hai phan so: ";
	Thuong.Xuat();

	return 0;
}

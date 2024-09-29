#include <bits/stdc++.h>
using namespace std;

class PhanSo {
private:
	int tu, mau;
public:
	PhanSo() {
		tu = 0;
		mau = 1;
	}
	PhanSo(int t, int m) {
		tu = t;
		mau = m;
	}
	void nhap() {
		cin >> tu >> mau;
	}
	bool check() {
		if (mau == 0)return false;
		return true;
	}
	void rutgon() {
		int GCD = __gcd(tu, mau);
		if(tu * mau < 0) GCD*= -1;
		tu /= GCD;
		mau /= GCD;
	}
	void xuat() {
		cout << "Phan so lon hon la: " << tu << "/" << mau << endl;
	}
	double giatri() const {
		return 1.0 * tu / mau;
	}
	bool operator > (const PhanSo& ps) const {
		return int(giatri()*1000000) > int(ps.giatri()*1000000);
	}
	bool operator < (const PhanSo& ps) const {
		return int(giatri()*1000000) < int(ps.giatri()*1000000);
	} 

};

int main() {

	PhanSo a, b;
	cout << "Nhap tu va mau cua phan so thu nhat: ";

	while (1) {
		a.nhap();
		if (a.check() == true) {
			break;
		}
		cout << "Nhap lai tu va mau. Chu y mau khong duoc bang 0: ";
	}

	cout << "Nhap tu va mau cua phan so thu hai: ";

	while (1) {
		b.nhap();
		if (b.check() == true) {
			break;
		}
		cout << "Nhap lai tu va mau. Chu y mau khong duoc bang 0: ";
	}

	if(a > b) a.xuat();
	else if(a < b)b.xuat();
	else cout << "Hai phan so bang nhau." << endl;

	return 0;
}
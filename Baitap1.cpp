#include <bits/stdc++.h>
using namespace std;

class PhanSo{
private: 
	int tu, mau;
public:
	PhanSo(){ 
		tu = 0; 
		mau = 1; 
	}	
	PhanSo(int t, int m){
		tu = t;
		mau = m;
	}
	void nhap(){
		cin >> tu >> mau;
	}
	bool check(){
		if(mau == 0)return false;
		return true;
	}	
	void rutgon(){
		int GCD = __gcd(tu, mau);
		tu /= GCD;
		mau /= GCD;
	}
	void xuat(){
		cout << "Phan so sau khi toi gian: " << tu << "/" << mau << endl; 
	}
};

int main() {
	
	PhanSo a;
	cout << "Nhap tu va mau cua phan so: ";	

	while(1){
		a.nhap();
		if(a.check() == true){
			break;
		}
		cout << "Nhap lai tu va mau. Chu y mau khong duoc bang 0: ";
	}

	a.rutgon();
	a.xuat();




	return 0;
}
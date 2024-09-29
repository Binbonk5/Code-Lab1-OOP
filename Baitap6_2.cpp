#include<bits/stdc++.h>
using namespace std;

struct hocsinh {
	string HoTen;
	string DanhHieu;
	double Toan;
	double Van;
	double NgoaiNgu, DTB;
} a[5];

// Kiem tra ten co hop le chua
bool CheckName(string s) {
	s = ' ' + s;
	bool ok = true;
	for (int i = 1 ; i < s.size(); i++) {
		if (s[i - 1] == ' ') {
			if (!('A' <= s[i] && s[i] <= 'Z')) {
				ok = false;
				break;
			}
		}
		else {
			if (!('a' <= s[i] && s[i] <= 'z') && s[i] != ' ') {
				ok = false;
				break;
			}
		}
	}
	return ok;
}

// Kiem tra diem co hop le chua
bool CheckMark(double diem) {
	if (0 * 1.0 <= diem && diem <= 10 * 1.0) return true;
	else return false;
}

// Nhap thong tin hoc sinh
void GetInformation() {
	for (int i = 1; i <= 3; i++) {
		cout << "Nhap Ho va Ten hoc sinh " << i << ": ";
		getline(cin, a[i].HoTen);

		while (!CheckName(a[i].HoTen)) {
			cout << "Nhap lai Ho va Ten hoc sinh " << i << ": ";
			getline(cin, a[i].HoTen);
		}

		cout << "Nhap diem mon Toan: ";
		cin >> a[i].Toan;

		while (!CheckMark(a[i].Toan)) {
			cout << "Nhap lai diem mon Toan: ";
			cin >> a[i].Toan;
		}

		cout << "Nhap diem mon Van: ";
		cin >> a[i].Van;

		while (!CheckMark(a[i].Van)) {
			cout << "Nhap lai diem mon Van: ";
			cin >> a[i].Van;
		}

		cout << "Nhap diem mon Ngoai ngu: ";
		cin >> a[i].NgoaiNgu;

		while (!CheckMark(a[i].NgoaiNgu)) {
			cout << "Nhap lai diem mon Ngoai ngu: ";
			cin >> a[i].NgoaiNgu;
		}

		cout << endl;

		cin.ignore();
	}
}

// Tinh diem trung binh
void CalGPA() {
	for (int i = 1; i <= 3; i++) {
		a[i].DTB = 1.0 * (2 * a[i].Toan + a[i].Van + a[i].NgoaiNgu) / 4;
	}
}

// Phan loai hoc sinh
void StudentFilter() {
	for (int i = 1; i <= 3; i++) {
		if (a[i].DTB >= 9) a[i].DanhHieu = "Xuat sac";
		else if (a[i].DTB >= 8) a[i].DanhHieu = "Gioi";
		else if (a[i].DTB >= 6.5) a[i].DanhHieu = "Kha";
		else if (a[i].DTB >= 5) a[i].DanhHieu = "Trung binh";
		else a[i].DanhHieu = "Yeu";
	}
}

// Xuat bang diem trung binh va phan loai
void ListInformation() {
	cout << "Xuat diem trung binh va phan loai " << endl;
	for (int i = 1; i <= 3; i++) {
		cout << a[i].HoTen << " ----- " << a[i].DTB << " ----- " << a[i].DanhHieu << endl;
	}
	cout << endl;
}

// Tim hoc sinh co diem trung binh cao nhat
void FindMax() {
	int MAX = 0;
	for (int i = 1; i <= 3; i++) {
		if (a[i].DTB > MAX) {
			MAX = a[i].DTB;
		}
	}
	cout << "Hoc sinh co diem trung binh cao nhat la: " << endl;

	for (int i = 1; i <= 3; i++) {
		if (a[i].DTB == MAX) {
			cout << a[i].HoTen << endl;
		}
	}
	cout << endl;
}

// Tim kiem theo ten
void FindName() {
	cout << "Ban co muon tim kiem hoc sinh theo ten khong?" << endl;
	while (1) {
		bool ok = false;
		cout << "Nhap 1 de tim hoac 0 de bo qua" << endl;
		int x;
		cin >> x;
		if (x == 0) {
			cout << endl;
			break;
		}
		cout << "Nhap ten ban muon tim: ";
		string s;
		cin >> s;
		cout << endl;
		if ('a' <= s[0] && s[0] <= 'z') s[0] -= 32;
		for (int i = 1 ; i < s.size(); i++) {
			if ('A' <= s[i] && s[i] <= 'Z') s[i] += 32;
		}
		for (int i = 1; i <= 3; i++) {
			string newname = "";
			for (int j = a[i].HoTen.size() - 1; j >= 0 && a[i].HoTen[j] != ' '; j--) {
				newname += a[i].HoTen[j];
			}
			reverse(newname.begin(), newname.end());
			if (s == newname) {
				ok = true;
				cout << a[i].HoTen << endl;
				cout << "Diem trung binh: " << a[i].DTB << endl;
			}
		}
		if(!ok) cout << "Khong tim thay ten trung khop." << endl;
		cout << endl;
	}
	return;
}

// Tim hoc sinh co diem Toan thap nhat
void FindMinMath() {
	cout << "Danh sach hoc sinh co diem Toan thap nhat: " << endl;
	int MIN = 11;
	for (int i = 1; i <= 3; i++) {
		if (a[i].Toan < MIN) MIN = a[i].Toan;
	}
	for (int i = 1; i <= 3; i++) {
		if (a[i].Toan == MIN) {
			cout << a[i].HoTen << endl;
		}
	}
	cout << endl;
	return;
}

int main() {
	GetInformation();
	CalGPA();
	StudentFilter();
	ListInformation();
	FindMax();
	FindName();
	FindMinMath();
	return 0;
}
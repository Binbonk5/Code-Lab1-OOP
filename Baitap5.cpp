#include <bits/stdc++.h>
using namespace std;

class Time {
private:
	int Day, Month, Year;
	int DayOfMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
public:
	Time() {
		Day = 1;
		Month = 1;
		Year = 2024;
	}

	Time(int D, int M, int Y) {
		Day = D;
		Month = M;
		Year = Y;
	}

	void nhap() {
		cout << "Nhap ngay thang nam: ";
		cin >> Day >> Month >> Year;
	}

	bool check() {
		if (Year % 100 == 0) {
			if (Year % 400 == 0)
				return true;
		}
		else {
			if (Year % 4 == 0)
				return true;
		}
		return false;
	}

	void incr() {
		DayOfMonth[2] += 1;
	}

	void NextDay() {
		if (Day == DayOfMonth[Month]) {
			Day = 1;
			if (Month != 12) {
				Month += 1;
			}
			else {
				Month = 1;
				Year += 1;
			}
		}
		else Day += 1;
		
	}

	void PreviousDay(){
		if (Day == 1) {
			if (Month != 1) {
				Month -= 1;
				Day = DayOfMonth[Month];
			}
			else {
				Day = 31;
				Month = 12;
				Year -= 1;
			}
		}
		else Day -= 1;
	}

	int CalDay() {
		int ans = 0;
		for (int i = 1; i <= 12; i++) {
			if (Month > i) {
				ans += DayOfMonth[i];
			}
			else break;
		}
		ans += Day;
		return ans;
	}
	void Display(){
		cout << Day << " " << Month << " " << Year << endl;
	}

};

int main() {
	Time a;
	a.nhap();
	if (a.check()) a.incr();

	cout << "Ngay ke tiep la: ";
	a.NextDay();
	a.Display();

	cout << "Ngay truoc do la: ";
	a.PreviousDay();
	a.PreviousDay();
	a.Display();

	a.NextDay();

	cout << "Day la ngay thu ";
	cout << a.CalDay() << " trong nam" << endl;

	return 0;
}
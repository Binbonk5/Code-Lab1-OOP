#include <bits/stdc++.h>

using namespace std;

// ham tinh gia tri sin
double cal(double x) {
    double term = x; // Khoi tao gia tri dau tien cua chuoi Talor
    double sum = term; // Tong ban dau la gia tri dau tien
    int n = 1; // Bat dau tu n = 1

    while (fabs(term) >= 0.00001) {
        term *= -x * x / ((2 * n) * (2 * n + 1)); // Tinh gia tri cua hang tu
        sum += term; // Cong hang tu vao tong
        n++;
    }

    return sum;
}

int main() {
    double x;
    cout << "Nhap gia tri cua x (radian): ";
    cin >> x;

    double result = cal(x);
    cout << "Gia tri cua sin(" << x << ") la: " << result << endl;

    return 0;
}

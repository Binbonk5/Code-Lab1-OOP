#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Sub {
private:
    vector<int> A;
    vector<int> B;

    bool isSub(int pos) {
        for (int j = 0; j < A.size(); ++j) {
            if (B[pos + j] != A[j]) {
                return false;
            }
        }
        return true;
    }
public:
    Sub (const vector<int>& A, const vector<int>& B) : A(A), B(B) {}

    void CountSub() {
        int cnt = 0;
        vector<int> pos;

        for (int i = 0; i <= B.size() - A.size(); ++i) {
            if (isSub(i)) {
                cnt++;
                pos.push_back(i);
            }
        }

        cout << "So lan xuat hien cua A trong B: " << cnt << endl;
        cout << "Cac vi tri xuat hien: ";
        for (int i : pos) {
            cout << i << " ";
        }
        cout << endl;
    }


};

int main() {
    int n, m;
    cout << "Nhap so phan tu cua A va B: ";
    cin >> n >> m;

    vector<int> A(n), B(m);
    cout << "Nhap cac phan tu cua A: ";
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    cout << "Nhap cac phan tu cua B: ";
    for (int i = 0; i < m; ++i) {
        cin >> B[i];
    }

    Sub counter(A, B);
    counter.CountSub();

    return 0;
}

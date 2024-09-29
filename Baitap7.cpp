#include <bits/stdc++.h>

using namespace std;

class Flight {
public:
    string flightCode;
    string departureDate;
    string departureTime;
    string departurePlace;
    string arrivalPlace;

    Flight(string code, string date, string time, string depPlace, string arrPlace)
        : flightCode(code), departureDate(date), departureTime(time), departurePlace(depPlace), arrivalPlace(arrPlace) {}

    void printInfo() const {
        cout << "Ma chuyen bay: " << flightCode << "\n" << "Ngay bay: " << departureDate << "\n" << "Gio bay: " << departureTime << "\n"
             << "Noi di: " << departurePlace << "\n"
             << "Noi den: " << arrivalPlace << "\n";
    }
};

bool isValidFlightCode(const string& code) {
    return regex_match(code, regex("^[A-Za-z0-9]{1,5}$"));
}

bool isValidDate(const string& date) {
    return regex_match(date, regex("^\\d{2}/\\d{2}/\\d{4}$"));
}

bool isValidTime(const string& time) {
    return regex_match(time, regex("^([01]\\d|2[0-3]):([0-5]\\d)$"));
}

bool isValidPlace(const string& place) {
    return regex_match(place, regex("^[A-Za-z\\s]{1,20}$"));
}

void inputFlightInfo(vector<Flight>& flights) {
    int n;
    cout << "Nhap so luong chuyen bay: ";
    cin >> n;
    cin.ignore(); 

    for (int i = 0; i < n; ++i) {
        string code, date, time, depPlace, arrPlace;

        cout << "Nhap thong tin chuyen bay thu " << i + 1 << ":\n";

        do {
            cout << "Ma chuyen bay: ";
            getline(cin, code);
            if (!isValidFlightCode(code)) {
                cout << "Ma chuyen bay khong hop le. Vui long nhap lai\n";
            }
        } while (!isValidFlightCode(code));

        do {
            cout << "Ngay bay (dd/mm/yyyy): ";
            getline(cin, date);
            if (!isValidDate(date)) {
                cout << "Ngay bay khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidDate(date));

        do {
            cout << "Gio bay (hh:mm): ";
            getline(cin, time);
            if (!isValidTime(time)) {
                cout << "Gio bay khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidTime(time));

        do {
            cout << "Noi di: ";
            getline(cin, depPlace);
            if (!isValidPlace(depPlace)) {
                cout << "Noi di khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidPlace(depPlace));

        do {
            cout << "Noi den: ";
            getline(cin, arrPlace);
            if (!isValidPlace(arrPlace)) {
                cout << "Noi den khong hop le. Vui long nhap lai.\n";
            }
        } while (!isValidPlace(arrPlace));

        flights.emplace_back(code, date, time, depPlace, arrPlace);
    }
}

void searchFlightByCode(const vector<Flight>& flights, const string& code) {
    for (const auto& flight : flights) {
        if (flight.flightCode == code) {
            flight.printInfo();
            return;
        }
    }
    cout << "Khong tim thay chuyen bay voi ma " << code << ".\n";
}

void searchFlightsByPlace(const vector<Flight>& flights, const string& place, bool isDeparture) {
    for (const auto& flight : flights) {
        if ((isDeparture && flight.departurePlace == place) || (!isDeparture && flight.arrivalPlace == place)) {
            flight.printInfo();
            cout << "-------------------\n";
        }
    }
}

int cmp(Flight &a, Flight &b){
	if (a.departureDate == b.departureDate) {
            return a.departureTime < b.departureTime;
        }
        return a.departureDate < b.departureDate;
}

void sortFlightsByDateTime(vector<Flight>& flights) {
    sort(flights.begin(), flights.end(),cmp);
}

void listFlightsOnDateFromPlace(const vector<Flight>& flights, const string& date, const string& place) {
    for (const auto& flight : flights) {
        if (flight.departureDate == date && flight.departurePlace == place) {
            flight.printInfo();
            cout << "-------------------\n";
        }
    }
}

int countFlightsFromTo(const vector<Flight>& flights, const string& from, const string& to) {
    int count = 0;
    for (const auto& flight : flights) {
        if (flight.departurePlace == from && flight.arrivalPlace == to) {
            count++;
        }
    }
    return count;
}

int main() {
    vector<Flight> flights;
    inputFlightInfo(flights);

    cout << "\nDanh sach chuyen bay da sap xep theo thoi gian khoi hanh:\n";
    sortFlightsByDateTime(flights);
    for (const auto& flight : flights) {
        flight.printInfo();
        cout << "-------------------\n";
    }

    string code;
    cout << "\nNhap ma chuyen bay can tim: ";
    getline(cin, code);
    searchFlightByCode(flights, code);

    // Tim cac chuyen bay trong ngay o noi khoi hanh
    string date, place;
    cout << "\nNhap ngay va noi khoi hanh:\n";
    cout << "Nhap ngay (dd/mm/yyy): ";
    getline(cin, date);
    cout << '\n';
    cout << "Nhap noi khoi hanh: ";
    getline(cin, place);
    cout << '\n';
    listFlightsOnDateFromPlace(flights, date, place);


    // Dem so chuyen bay tu noi di toi noi den
    string from, to;
    cout << "\nNhap noi di va noi den de dem so chuyen bay: ";
    cout << "\nNhap noi di:"
    getline(cin, from);
    cout << "\nNhap noi den: ";
    getline(cin, to);
    int count = countFlightsFromTo(flights, from, to);
    cout << "\nSo chuyen bay tu " << from << " den " << to << ": " << count << "\n";

    return 0;
}

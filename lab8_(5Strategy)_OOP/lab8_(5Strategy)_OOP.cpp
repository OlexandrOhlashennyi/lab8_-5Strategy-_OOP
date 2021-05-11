/*
паттерн стратегія.
Клас подорож, що діє за такими стратегіями: 
подорож автобусом в Україні
подорож автобусом за кордоном
відпочинок за кордоном
*/

#include <iostream>
#include <string>
#define NAME 30

using namespace std;

enum currency {
	DOLLAR = 2772,
	EURO = 3301,
	POUND = 3843,
};

class pass {
public:
	pass() {}
	~pass() {}

	virtual double total() = 0;
	virtual void print() = 0;
	virtual void input() = 0;
};

class GobyBus_incountry : public pass {
private:
	string destination;
	double journey_price;
public:
	GobyBus_incountry() {
		destination = "";
		journey_price = 0;
	}
	GobyBus_incountry(string dest, double price): destination(dest), journey_price(price) {}
	~GobyBus_incountry() {}

	double total() { return journey_price; }
	void print() {
		cout << "You traveling in country by bus;\n\tdesination: " << destination << ";  price: " << journey_price << " UAH" << "\ttotal: " << total() << " UAH" << endl;
	}
	void input() {
		cout << "Destenation: "; cin >> destination;
		cout << "Journey price: "; cin >> journey_price;
	}
};

class GobyBus_foregin : public pass {
private:
	string destination;
	double journey_price;
	currency cur;
public:
	GobyBus_foregin() {
		destination = "";
		journey_price = 0;
		cur = DOLLAR;
	}
	GobyBus_foregin(string dest, double price, currency c) : destination(dest), journey_price(price), cur(c) {}
	~GobyBus_foregin() {}

	double total() { return journey_price*cur/100; }
	void print() {
		char c[5];
		switch (cur)
		{
		case DOLLAR:
			strcpy_s(c, " USD");
			break;
		case EURO:
			strcpy_s(c, " EUR");
			break;
		case POUND:
			strcpy_s(c, " GBP");
			break;
		default:
			break;
		}
		cout << "You traveling out country by bus;\n\tdesination: " << destination << ";  price: " << journey_price << " " << c << "\ttotal: " << total() << " UAH" << endl;
	}
	void input() {
		cout << "Destenation: "; cin >> destination;
		cout << "Journey price: "; cin >> journey_price;
		int c;
		cout << "currency(dollar -- 1, euro -- 2, pound -- 3): "; cin >> c;
		switch (c) {
		case 1:
			cur = DOLLAR;
			break;
		case 2:
			cur = EURO;
			break;
		case 3:
			cur = POUND;
		default:
			cur = DOLLAR;
			break;
		}
	}
};

class vacation : public pass {
private:
	string destination;
	double day_price;
	int duration;
	currency cur;
public:
	vacation() {
		destination = "";
		day_price = 0;
		duration = 0;
		cur = DOLLAR;
	}
	vacation(string dest, double price, int dur, currency c) : destination(dest), day_price(price), duration(dur), cur(c) {}
	~vacation() {}

	double total() { return day_price * cur/100; };
	void print() {
		char c[5];
		switch (cur)
		{
		case DOLLAR:
			strcpy_s(c, " USD");
			break;
		case EURO:
			strcpy_s(c, " EUR");
			break;
		case POUND:
			strcpy_s(c, " GBP");
			break;
		default:
			break;
		}
		cout << "You are on the vacation;\n\tdestination: " << destination << "; duration: " << duration << "; price per day: " << day_price << " " << c << "\ttotal: " << total() << " UAH" << endl;
	}

	void input() {
		cout << "Destenation: "; cin >> destination;
		cout << "Duration: "; cin >> duration;
		cout << "Day price: "; cin >> day_price;
		int c;
		cout << "currency(dollar -- 1, euro -- 2, pound -- 3): "; cin >> c;
		switch (c) {
		case 1:
			cur = DOLLAR;
			break;
		case 2:
			cur = EURO;
			break;
		case 3:
			cur = POUND;
		default:
			cur = DOLLAR;
			break;
		}
	}
};

class travel {
private:
	pass* travel_type;
public:
	travel() { travel_type = NULL; }
	travel(pass* type) { travel_type = type; }
	~travel() { delete travel_type; }
	void set_type(pass* type) { 
		delete travel_type;
		travel_type = type; 
	}
	double total() { return travel_type->total(); }
	void print() { travel_type->print(); }
	bool operator>(travel& p) {
		return this->total() > p.total();
	}
	bool operator<(travel& p) {
		return this->total() < p.total();
	}
	void input() {
		travel_type->input();
	}
};

void print_travels(travel* t, int n) {
	cout << "***list of travels***\n";
	for (int i = 0; i < n; i++) {
		t[i].print();
	}
}

void sort(travel* p, int n) {
	travel* ptrtravel;
	travel temp;
	int i, t = 0;
	for (i = 1; i < n; i++) {
		if (p[i] > p[i - 1])
			continue;
		swap(temp, p[i]);
		ptrtravel = p + i - 1;
		while (temp < *ptrtravel) {
			swap(*(ptrtravel + 1), *ptrtravel);
			if (--ptrtravel < p) break;
		}
		swap(*(ptrtravel + 1), temp);
	}
}

void input(travel* t, int n) {
	cout << "Enter travel:\n";
	for (int i = 0; i < n; i++) {
		int type;
		cout << "Enter type of travel(1--bus in country, 2--foregin bus, 3--vacation): "; cin >> type;
		if (type == 1) {
			t[i].set_type(new GobyBus_incountry);
		}
		else if (type == 2) {
			t[i].set_type(new GobyBus_foregin);
		}
		else if (type == 3) {
			t[i].set_type(new vacation);
		}
		t[i].input();
	}
}

int main() {
	travel*t;

	int n;
	cout << "Enter number of pass: ";
	cin >> n;

	t = new travel[n];
	input(t, n);
	cout << "\n\n";
	print_travels(t, n);
	cout << "\n\n";
	sort(t, n);
	print_travels(t, n);

	delete[] t;
	return 0;
}

/*Input template:
5
2
Warsaw
45
2
3
Paris
3
121
2
1
Kyiv
5
1
Lviv
10
2
Rome
10
50
*/
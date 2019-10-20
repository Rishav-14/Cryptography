#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
int a[127]; int conv_factor;

void sfunction(int k) {
	int shuffle;
	for (int i = 126; i > 32; i--) {
		shuffle = (conv_factor) ^ 3 + i ^ 2 + k + 1;
		int j = shuffle % (i - 31) + 32;
		swap(a[i], a[j]);
	}
}

void encrypt() {
	cout << "Enter Message:" << endl;
	string m;
	cin.ignore();
	getline(cin, m);
	char mx[100];
	srand(time(NULL));
	int temp = rand();
	conv_factor = (temp % 95) + 32;
	for (int i = 0; i < m.length(); i++) {
		sfunction(i);
		mx[i] = static_cast<char>(a[int(m[i])]);
	}
	cout << conv_factor << endl;
	int e_s = sqrt(m.length());
	cout << e_s << endl;
	if (e_s % 2 == 0) {
		for (int i = 126; i > (126 - e_s); i--) {
			cout << static_cast<char>(a[i]);
		}
	}
	int q = 0;
	while (q < m.length()) {
		cout << mx[q];
		q++;
		if (q == 1) {
			cout << static_cast<char>(conv_factor);
		}
	}
	if (e_s % 2 != 0) {
		for (int i = 0; i < e_s; i++) {
			cout << static_cast<char>(a[i]);
		}
	}

	char end;
	cin >> end;
}

void decrypt() {
	cout << "Enter Message:" << endl;
	string m;
	cin.ignore();
	getline(cin, m);
	int e_length = m.length();
	int o_length = ((2 * (e_length)+1) - sqrt(1 + 4 * (e_length))) / 2;
	int e_s = e_length - o_length - 1;
	cout << e_length << o_length << e_s << endl;
	char mx[100];
	if (e_s % 2 == 0) {
		mx[0] = m[e_s];
		conv_factor = m[e_s + 1];
		for (int i = 1; i < o_length; i++) {
			mx[i] = m[e_s + 1 + i];
		}
	}
	else {
		mx[0] = m[0];
		conv_factor = m[1];
		for (int i = 1; i < o_length; i++) {
			mx[i] = m[1 + i];
		}
	}
	cout << conv_factor << "CF" << endl;
	for (int i = 0; i < o_length; i++) {
		sfunction(i);
		for (int k = 32; k < 127; k++) {
			if (mx[i] == static_cast<char>(a[k])) {
				cout << static_cast<char>(k);
				break;
			}
		}
	}
	char end;
	cin >> end;
}

int main() {
	int choice;
	cout << "For Encryption(Press 1)\nFor Decryption(Press 2)\n";
	cout << "\nBy: Rishav  1901_CS46\n";
	cin >> choice;
	system("CLS");
	for (int i = 32; i < 127; i++) {
		a[i] = i;
	}
	switch (choice) {
	case 1: encrypt(); break;
	case 2: decrypt(); break;
	}

	return 0;
}


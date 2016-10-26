#include <iostream>

using namespace std;

bool good (int m, int k) {
	int x = 0;
	for (int i = 0; i < k; i++) {
		x += m - 1;
		x %= 2*k - i;
		if (x < k)	return 0;
	}

	return 1;
}

int solve (int k) {
	int m = k + 1;
	while (!good (m, k)) m++;
	return m;
}

int main () {
	int v[15];
	for (int k = 1; k < 14; k++) {
		v[k] = solve (k);
	}
	int k;
	cin >> k;
	while (k != 0) {
		cout << v[k] << '\n';
		cin >> k;
	}
	return 0;
}

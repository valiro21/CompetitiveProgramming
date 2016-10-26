#include <iostream>

#define MMax 101

typedef unsigned long long ull;

void ciur () {
	p.push_back (2);
	for (int i = 3; i < NMax; i++) {
		p.
	}
}

int main () {
	ios_base::sync_with_stdio (false);
	
	cout << tcr (2, 4);
	return 0;
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> n >> k >> m;

		if (m >= n) {
			cout << '0';
			continue;
		}

		long long r1 = get_zero (n - k, m);
		long long r2 = comb(n, k, m);
		cout << (r1 * r2) % m;
	}

	return 0;
}

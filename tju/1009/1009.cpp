#include <iostream>
#include <algorithm>
#include <utility>

#define NMax 121

using namespace std;

bool viz[NMax];
int v[NMax];
int n;
int orig_sum;

int bsearch (int st, int en, int val) {
	int pw = 128;
	for (;pw;pw/=2) {
		st += pw;
		if (st > en || v[st] > val) st -= pw;
	}

	return st;
}

int min (int a, int b) {
	return a < b ? a : b;
}

int dfs (int pos, int sum, int elem) {
	if (sum == 0) {
		int i = n - 1;
		while(i >= 0 && viz[i]) i--;
		if (i < 0) return elem;
		return dfs (i, orig_sum, elem);
	}
	
	int last = -1;
	int fpos = min (bsearch (0, pos, sum), pos);
	for (int i = fpos; i >= 0; i--) {
		if (!viz[i] && v[i] != last) {
			viz[i] = true;
			last = v[i];
			int r = dfs (i - 1, sum - v[i], elem + 1);
			if (r) return r;
			viz[i] = false;
		}
	}

	return 0;
}

int solve () {
	int sum = 0;
	int newN = 0;
	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x <= 50) {
			v[newN] = x;
			sum += x;
			newN++;
		}
	}

	n = newN;
	if (n == 0) return 0;

	sort (v, v+n);
	
	int m = v[n-1] - 1;
	while (m <= sum) {
		m++;
		if (sum % m == 0) {
			int good = 0;
			for (int i = 0; i < n; i++) viz[i] = false;
			orig_sum = m;
			good += dfs (n-1, m, 0);
			//cout << good << '\n';
			if (good == n) return m;
		}
	}

	return -1;
}

int main () {
	cin >> n;
	while (n) {
		cout << solve () << '\n';
		cin >> n;
	}
	
	return 0;
}

#include <iostream>
#include <map>
#include <utility>

using namespace std;

typedef long long uint;
typedef map<uint, pair<short, bool> > MP;

int bitcount (int x) {
	int count = 0;
	while (x) {
		count += x&1;
		x /= 2;
	}
	return count;
}

uint sum[(1<<17)];
uint d;
int t, n, m;

void make_sums (MP *s, int *v, int start, int elem) {
	s->clear ();
	for (int i = 0, pw = 1; i < elem; i++, pw *= 2)
		sum[pw] = v[start+i];
	sum[0] = 0;
	for (int i = 1; i < (1<<elem); i++) {
		sum[i] = sum[i - (i&(i-1))] + sum[i&(i-1)];
		
		//cout << sum [i] << ' ';
		if (sum[i] <= d) {
			pair<short, bool> &p = (*s)[sum[i]];
			int nro = bitcount(i);
			if (p.first == 0) p.first = nro;
			else if (p.first != nro) p.second = true;
		}
	}
	//cout << '\n';
}

MP sums1, sums2;
int v[102];

void assign (pair<short, bool> &result, pair<short, bool> new_elem) {
	if (result.first == -1) {
		result.first = new_elem.first;
		result.second = new_elem.second;
	}
	else if (result.first == new_elem.first)
		result.second |= new_elem.second;
	else
	 	result.second = true;
}

int main () {
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> n >> d;
		for (int j = 0; j < n; j++) cin >> v[j];
		
		make_sums (&sums1, v, 0, n / 2);
		make_sums (&sums2, v, n / 2, n - n / 2);

		pair<short, bool> result = make_pair(-1, 0);
		if (d == 0) result.first = 0;
		for (MP::iterator it = sums1.begin (); it != sums1.end (); it++) {
			MP::iterator it2 = sums2.find (d - it->first);
			if (it2 != sums2.end ()) {
				//cout << it->first << ' ' << it2->first << '\n';
				short nro = it->second.first + it2->second.first;
				bool amb = it->second.second | it2->second.second;
				assign (result, make_pair (nro, amb));
	
				if (result.second) {
					break;
				}
			}
		}
	
		MP::iterator it = sums1.find (d);
		if (it != sums1.end ()) assign (result, it->second);
		it = sums2.find(d);
		if (it != sums2.end ()) assign (result, it->second);
		cout << "Case #" << i+1 << ": ";
		if (result.second) cout << "AMBIGIOUS";
		else if (result.first == -1) cout << "IMPOSSIBLE";
		else cout << result.first;
		cout << '\n';
	}
	return 0;
}

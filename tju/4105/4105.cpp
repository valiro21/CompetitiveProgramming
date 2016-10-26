#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define DEBUG 1
#define NMax 100002

typedef map<int, vector<pair<int, bool> > > MP;
int res[NMax][2], aib[NMax];
vector<pair<int, int> > p, v;
MP mp;

void update (int *v, int pos, int val) {
	while (pos < NMax) {
		v[pos] += val;
		pos += pos - (pos&(pos-1));
	}
}

int query (int *v, int pos) {
	if (pos <= 0)
		return 0;
	int val = 0;
	while (pos) {
		val += v[pos];
		pos -= pos - (pos&(pos-1));
	}
	return val;
}

int n;

int main () {
	int l, r;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> l >> r;
		if (l > r)
			swap (l, r);
		v.push_back (make_pair (l, r));
	}

	int m, l1, l2, r1, r2;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> l1 >> r1 >> l2 >> r2;
		mp[l1].push_back (make_pair (i, 0));
		mp[r1].push_back (make_pair (i, 1));
		p.push_back (make_pair (l2, r2));
	}

	sort (v.begin (), v.end ());
	int x = 0;
	for (MP::iterator it = mp.begin (); it != mp.end (); it++) {
		//cout << it->first << '\n';
		while (x < n && v[x].first<it->first) {
			update (aib, v[x].second, 1);
			//cout << x << ' ' << '0' << '\n';
			x++;
		}
		for (int i = 0; i < it->second.size (); i++) {
			if (it->second[i].second == 1) continue;
			int index = it->second[i].first;
			
			int result = query (aib, p[index].second) - query (aib, p[index].first - 1);
			res[index][0] = result;
		}

		while (x < n && v[x].first == it->first) {
			update (aib, v[x].second, 1);
			//cout << x << ' ' << '1' << '\n';
			x++;
		}
		for (int i = 0; i < it->second.size (); i++) {
			if (it->second[i].second == 0) continue;
			int index = it->second[i].first;
			
			int result = query (aib, p[index].second) - query (aib, p[index].first - 1);
			res[index][1] = result;
		}
	}

	for (int i = 0; i < m; i++) {
		cout << res[i][1] - res[i][0] << '\n';
	}

	return 0;
}

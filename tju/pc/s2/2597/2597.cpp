#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<int> v, pos;
string str;
int s = 0;

int find (int s) {
	for (int i = 0; i < v.size (); i++) {
		if (v[i] == s) return i;
	}
	return 0;
}

int find_r (int s, int pos) {
	for (int i = pos; i < v.size (); i++) {
		if (v[i] && v[i] % 3 == s) return i;
	}
	return -1;
}

int main () {
	cin >> str;
	for (int i = 0; i < str.size (); i++) {
		v.push_back (str[i] - '0');
		s += v.back ();
	}
	s %= 3;

	sort (v.begin (), v.end ());
	if (v.back () != 0) {
		int pz = find (5);
		if (pz == -1) return false;

		swap (v[pz], v[0]);
		sort (v.begin () + 1, v.end ());
	}


	if (s != 0) {
		int pz = find_r (s, 0);
		if (pz == -1) {
			if (s % 3 == 2) {
				pz = find_r (1, 0);
				if (pz == -1) return false;
				pos.push_back (pz);
				pz = find_r (1, pz + 1);
				if (pz == -1) return false;
				pos.push_back (pz);
			}
			else if (s % 3 == 1) {
				pz = find_r (2, 0);
				pos.push_back (pz);
				pz = find_r (2, pz + 1);
			}
		}
		else {
			pos.push_back (pz);
		}
	}

	str = "";
	for (int i = v.size () - 1; i >= 0; i--) {
		bool found = false;
		for (int j = 0; j < pos.size (); j++)
			if (v[i] == pos[j])
				found = true;
		if (!found)
			str += v[i] + '0';
	}

	if (str[0] == '0') {
		cout << 0;
	}
	else {
		cout << str;
	}

	cout << '\n';

	return 0;
}

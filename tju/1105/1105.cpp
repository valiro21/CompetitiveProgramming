#include <iostream>
#include <map>
#include <algorithm>
#include <utility>
#include <string>
#include <cstring>

using namespace std;

map<string, int> mp;

void add (string &s, int e) {
	if (e == s.size ()) {
		s += 'a';
		return;
	}

	s[e]++;
	while (s[e] > 'z') {
		add (s, e + 1);
		s[e] = s[e + 1] + 1;
	}
}

void preproc () {
	string s = "a";
	int index = 0;
	while (s.size () < 6) {
		index++;
		mp[s] = index;
		//cout << s << '\n';
		add (s, 0);
	}
	//cout << s << '\n';
	//add (s, 0);
	//cout << s << '\n';
}

int main () {
	preproc ();
	string s;
	cin >> s;
	while (!cin.eof ()) {
		reverse (s.begin (), s.end ());
		cout << mp[s] << '\n';
		cin >> s;
	}
	return 0;
}

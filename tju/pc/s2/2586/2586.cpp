#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#define DEBUG 0

using namespace std;

pair<int, int> mp1 = make_pair (-1, -1);
pair<int, int> d[4];
vector<pair<pair<int, int>, pair<int, int> > > v;
queue<pair<int, int> > q;
pair<int, int> p[10][10];

bool check (int x11, int x12, int x21, int x22) {
	if (x11 > x12) swap (x11, x12);
	if (x21 > x22) swap (x21, x22);
	return x11 <= x21 && x22 <= x12;
}

void printp (pair<int, int> p) {
	cout << '{' << p.first << ", " << p.second << '}';
}

bool find (pair<int, int> p1, pair<int, int> p2) {
	for (int i = 0; i < 3; i++) {
		if (v[i].first.first == v[i].second.first) {
			//x equal
			if (p1.first == p2.first && v[i].first.first == p1.first) {
				if (DEBUG) {printp (v[i].first); printp(v[i].second); printp (p1); printp(p2); cout << i<<'\n';}
				if (check (v[i].first.second, v[i].second.second, p1.second, p2.second))
					return 0;
			}
		}
		else if (v[i].first.second == v[i].second.second) {
			if (p1.second == p2.second && v[i].first.second == p1.second) {
				if (check (v[i].first.first, v[i].second.first, p1.first, p2.first))
					return 0;
			}
		}
	}
	return 1;
}

bool outOfBounds (pair<int, int> p) {
	return !(1<=p.first&&p.first<=6&&1<=p.second&&p.second<=6);
}

int find_in_d (pair<int, int> p) {
	for (int i = 0; i < 4; i++) {
		if (d[i] == p) return i;
	}
	return -1;
}

char dif (pair<int, int> x, pair<int, int> y) {
	pair<int, int> diff = make_pair (y.first - x.first, y.second - x.second);
	int k = find_in_d(diff);

	switch (k) {
		case 0: return 'N';
		case 1: return 'E';
		case 2: return 'S';
		case 3: return 'W';
	}
}

void print (pair<int, int> now) {
	if (p[now.first][now.second] == mp1) return;
	print (p[now.first][now.second]);
	
	cout << dif (p[now.first][now.second], now);
}

bool good (pair<int, int> now, int dir) {
	int i = now.first, j = now.second;
	switch (dir) {
		case 0:
			return find (make_pair (i-1 , j-1), make_pair (i, j-1));
		break;
		case 1:
			return find (make_pair (i , j-1), make_pair (i, j));
		break;
		case 2:
			return find (make_pair (i-1, j), make_pair (i, j));
		break;
		case 3:
			return find (make_pair (i-1 , j-1), make_pair (i-1, j));
		break;
	}
}

void lee (pair<int, int> st, pair<int, int> en) {
	while (!q.empty ()) q.pop();
	q.push(st);
	while (!q.empty ()) {
		pair<int, int> now = q.front ();
		q.pop();
		if (now == en) break;

		for (int i = 0; i < 4; i++) {
			pair<int, int> next = make_pair (now.first + d[i].first, now.second + d[i].second);
			if (!outOfBounds (next)) { 
				if (p[next.first][next.second] == mp1 && next != st) {
					if (good (now, i)) {
						q.push (next);
						p[next.first][next.second] = now;
					}
				}
			}
		}
	}

	print (en);
}

void load () {
	d[0] = make_pair (0, -1); //N
	d[1] = make_pair (1, 0); //E
	d[2] = make_pair (0, 1); //S
	d[3] = make_pair (-1, 0); //W
}

int main () {
	load ();
	int n, x1, x2, y1, y2;
	pair<int, int> st, en;
	cin >> x1 >> y1;
	while (x1 && y1) {
		st = make_pair (x1, y1);
		cin >> x1 >> y1;
		en = make_pair (x1, y1);
		v.clear ();
		for (int i = 1; i < 7; i++)
			for (int j = 1; j < 7; j++) {
				p[i][j] = mp1;
			}
		for (int i = 0; i < 3; i++) {
			cin >> x1 >> y1 >> x2 >> y2;
			v.push_back (make_pair (make_pair (x1, y1), make_pair (x2, y2)));		
		}
		lee (st, en);
		cout << '\n';
		cin >> x1 >> y1;
	}	
	
	return 0;
}

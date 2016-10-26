#include <iostream>
#include <utility>
#include <vector>
#include <cstdio>
#include <cmath>

#define DEBUG 0
#define eps 0.000000001

using namespace std;

typedef pair<double, double> point;
vector<point> v;

double myabs (double x) {
	return x >= 0 ? x : -x;
}

struct line {
	bool inf;
	double m;
	double n;
	
	line (point p1, point p2) {
		if (p1.first == p2.first) {
			inf = true;
			m = p1.first;
		}
		else {
			inf = false;
			m = (p2.second - p1.second) / (p2.first - p1.first);
			n = p2.second - m * p2.first;
		}
	}
};

void print (point &p) {
	cout << "{" << p.first << ", " << p.second << "}";
}

void print (line &l) {
	cout << "{";
	if (l.inf) cout << "inf: 1 ";
	cout << "m:" << l.m << " n:" << l.n << "}"; 
}

bool intersect (line l1, line l2, point &p) {
	if (l1.inf && l2.inf || l1.m == l2.m) {
		return 0;
	}

	if (l1.inf) {
		p.first = l1.m;
		p.second = p.first * l2.m + l2.n;
	}
	else if (l2.inf) {
		p.first = l2.m;
		p.second = p.first * l1.m + l1.n;
	}
	else {
		p.first = (l2.n - l1.n) / (l1.m - l2.m);
		p.second = p.first * l1.m + l1.n;
	}

	return true;
}

double dist (point &p1, point &p2) {
	double x = p2.first - p1.first;
	double y = p2.second - p1.second;
	return sqrt(x * x + y * y);
}

bool inBetween (point p1, point p, point p2) {
	return myabs (dist (p1, p) + dist (p, p2) - dist (p1, p2)) < eps;
}

bool intersect (point fl1, point fl2, point sl1, point sl2, point &p) {
	line l1(fl1, fl2), l2(sl1, sl2);
	bool in = intersect (l1, l2, p);
	if (DEBUG) {
		print (l1);print (l2);
		print (fl1); print (p); print (fl2);
		cout << '\n';
	}
	return in && inBetween (fl1, p, fl2);
}

void add_area (double &area, point p1, point p2) {
	double x = p2.first - p1.first;
	area += x * (p1.second + p2.second) / 2.;
}


void solve (int n) {
	double x, y;
	v.clear ();
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		if (v.empty () || make_pair (x, y) != v.back ())
			v.push_back (make_pair (x, y));
	}

	cin >> x >> y;
	point p1 = make_pair (x, y);
	cin >> x >> y;
	point p2 = make_pair (x, y);
	v.push_back (v[0]);
	point i1, i2;

	double a_tot = 0, a2 = 0;
	point p;
	int first_intersect = 0;
	for (int i = 0; i < v.size () - 1; i++) {
		if (first_intersect == 0 && intersect (v[i], v[i+1], p1, p2, p)) {
			add_area (a2, p, v[i+1]);
			i1 = p;
			first_intersect = 1;
		}
		else if (first_intersect == 1 && intersect (v[i], v[i+1], p1, p2, p) && v[i] != p) {
			add_area (a2, v[i], p);
			i2 = p;
			first_intersect++;
		}
		else if (first_intersect == 1) {
			add_area (a2, v[i], v[i+1]);
		}

		add_area (a_tot, v[i], v[i+1]);
	}
	add_area (a2, i2, i1);

	double a1 = a_tot - a2;
	if (a1 < a2) {
		swap (a1, a2);
	}

	printf ("%.0lf %.0lf\n", a1, a2);
}

int main () {
	int n;
	cin >> n;
	while (n) {
		solve (n);
		cin >> n;
	}
	return 0;
}

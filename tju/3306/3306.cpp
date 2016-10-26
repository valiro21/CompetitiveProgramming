#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class parser {
	const static int MAX_BUFFER_SIZE = 2097151;
	char *buffer;
	int BUFFER_SIZE;
	bool eof;
	istream *c;
	int pointer;
public:
	parser (istream &cin) {
		c = &cin;
		buffer = new char[MAX_BUFFER_SIZE];
		eof = false;
		readNextBlock ();
	}

	~parser () {
		delete[] buffer;
	}

	char getNext () {
		if (eof) return 0;
		char result = buffer[pointer++];
		if (pointer == BUFFER_SIZE)
			readNextBlock ();
        	return result;
	}

	int getNextNumber () {
		char ch;
		do {
			ch = getNext ();
		} while (!eof && (ch < '0' || ch > '9'));

		if (eof) return 0;
		int nr = 0;
		do {
			nr = nr * 10 + ch - '0';
			ch = getNext ();
		} while (!eof && ('0' <= ch && ch <= '9'));
		return nr;
	}

	string getNextBlock () {
		string s;
		char ch;
		do {
			ch = getNext ();
		} while (!eof && (ch == ' ' || ch == '\n'));

		if (eof) return string();

		while (!eof && ch != ' ' && ch != '\n') {
			s += ch;
			ch = getNext ();
		};

		return s;
	}

	void readNextBlock () {
		c->read (buffer, MAX_BUFFER_SIZE);
		BUFFER_SIZE = c->gcount();
		pointer = 0;
		eof = (c->eof() && pointer == BUFFER_SIZE);
	}

	bool isEof () {
		return eof && pointer == BUFFER_SIZE;
	}
};

#define NMax 1003
int n, m;
int index[NMax];
int v[NMax][NMax];
string s[NMax];

void qsort (int st, int en, int ln) {
	if (st >= en) return;

	int middle = st + (en - st) / 2;
	swap (index[st], index[middle]);

	int pivot = st;
	for (int i = st + 1; i < en; i++) {
		if (v[ln][index[st]] < v[ln][index[i]])
			swap (index[++pivot], index[i]);
	}
	swap (index[st], index[pivot]);

	qsort (st, pivot, ln);
	qsort (pivot+1, en, ln);
}

int line;
bool cmp (int a, int b) {
	return v[line][a] > v[line][b];
}

int getArea (int i) {
	int min = v[i][index[0]], maxa = min;
	for (int j = 1; j < m && v[i][index[j]]; j++) {
		if (v[i][index[j]] < min) min = v[i][index[j]];
		int area = (j+1) * min;
		if (area > maxa) maxa = area;
	}

	return maxa;
}

int main () {
	parser *pr = new parser (cin);
	ios_base::sync_with_stdio(false);
	while (true) {
		n = pr->getNextNumber ();
		m = pr->getNextNumber ();
		if (pr->isEof () || n == 0 || m == 0) break;

		for (int i = 0; i < n; i++) {
			s[i] = pr->getNextBlock ();
		}

		for (int j = 0; j < m; j++) {
			int consec = 0;
			for (int i = n - 1; i >= 0; i--) {
				if (s[i][j] == '0')
					consec = 0;
				else consec++;

				v[i][j] = consec;
			}
		}

		int maxg = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) index[j] = j;
			qsort (0, m, i);
			//line = i;
			//sort (index, index+m, cmp);
			int goodness = getArea (i);
			if (goodness > maxg)
				maxg = goodness;
		}

		cout << maxg << '\n';
	}
	return 0;
}

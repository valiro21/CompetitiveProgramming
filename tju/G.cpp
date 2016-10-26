#include <iostream>
#include <fstream>
#include <string>

class parser {
	const static int MAX_BUFFER_SIZE;
	char *buffer;
	int BUFFER_SIZE;
	bool eof;
	istream *c;
public:
	parser (istream &cin) {
		c = &cin;
		buffer = new char[MAX_BUFFER_SIZE];
		eof = false;
		readNextblock ();
	}
	
	~parser () {
		delete[] buffer;	
	}

	char getNext () {
		if (eof) return 0;
		char result = buffer[pointer++];
		if (pointer == BUFFER_SIZE)
			readNextBlock ();
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

	void readNextblock () {
		eof = c->eof();
		c->read (buffer, MAX_BUFFER_SIZE);
		BUFFER_SIZE = c->gcount();
		pointer = 0;
	}

	bool isEof () {
		return eof && pointer == BUFFER_SIZE;	
	}
};

parser pr(cin);

#define NMax 1003
int n, m;
int index[NMax];
int v[NMax][NMax];
string s[NMax];

void qsort (int st, int en, int ln) {
	if (st+1 >= en) return;

	int middle = st + (en - st) / 2;
	swap (index[st], index[middle]);
	
	int pivot = st;
	for (int i = st + 1; i < en; i++) {
		if (v[ln][index[st]] < v[ln][index[i]])
			swap (index[++pivot], index[i]);		
	}

	qsort (st, pivot-1, ln);
	qsort (pivot+1, en, ln);
}

int getArea (int i) {
	int min = v[i][index[0]], maxa = min;
	for (int j = 1; j < m && v[j]; j++) {
		if (v[index[j]] < min) min = v[index[j]];
		int area = (j+1) * min;
		if (area > maxa) maxa = area;
	}

	return maxa;
}

int main () {
	while (true) {
		n = pr->getNumber ();
		m = pr->getNumber ();
		if (n == 0 || m == 0) break;

		for (int i = 0; i < m; i++) {
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
			qsort (0, n, i);

			int goodness = getArea (i);
			if (goodness > maxg)
				maxg = goodness;
		}
		
		cout << maxg << '\n';
	}
	return 0;
}

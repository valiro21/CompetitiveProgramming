#include <iostream>

using namespace std;

int main () {
	int x;
	cin >> x;
	while (!cin.eof ()) {
		cout << (char)x;
		cin >> x;
	}
	return 0;
}

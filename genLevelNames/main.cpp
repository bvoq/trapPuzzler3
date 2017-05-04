#include <iostream>
#include <vector>
using namespace std;
int main() {
	int start,end;
	cin >> start >> end;
	for(int i = start; i <= end; ++i) cout << "levels.push_back(l"<< i <<");" << endl;
	return 0;
}

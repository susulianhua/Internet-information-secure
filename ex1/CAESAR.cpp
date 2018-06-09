#include<iostream>
#include <stdio.h>
#include<string>
#include<string.h>
#define LOCAL

using namespace std;

int main()
{

	int key;

	cin >> key;
    #ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
    #endif

    string lower_letter = "abcdefghijklmnopqrstuvwxyz";
    string upper_letter = "ABCDEFGHIJKIMNOPQRSTUVWXYZ";


	string test;

	while (getline(cin, test)) {
		for (int i = 0; i < test.size(); i++) {
			if (test[i] != '\r' && test[i] != '\n' ) {
				if (test[i] > 'a' && test[i] < 'z') {
					if (key >= 0) cout << lower_letter[(test[i] - 'a' + key) % 26];
					else cout << lower_letter[(test[i] - 'a' - key) % 26];
				}
				else if (test[i] > 'A' && test[i] < 'Z') {
					if (key >= 0) cout << upper_letter[(test[i] - 'A' - key) % 26];
					else cout << upper_letter[(test[i] - 'A' - key) % 26];
				}
				else cout << test[i];
			}
		}
	}
    return 0;
}


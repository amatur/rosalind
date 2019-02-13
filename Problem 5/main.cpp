#include <iostream>
#include <string>
#include <cstring>

using namespace std;


int main() {
    string s, t;

    getline(cin, s);
    getline(cin, t);

    int d = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i]!=t[i])
            d++;
    }
    cout<<d;

    return 0;
}

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    char base[1005];
    fgets( base, 1000, stdin );
    for (int i = 0; i < strlen(base); i++) {
        if (base[i]=='T') base[i]='U';
        cout << base[i];
    }
    return 0;
}

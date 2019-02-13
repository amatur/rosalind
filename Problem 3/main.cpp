#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    char base[1005];
    gets(base);
    for (int i = 0; i < strlen(base); i++) {
        if (base[i]=='A') base[i]='T';
        else if (base[i]=='C') base[i]='G';
        else if (base[i]=='G') base[i]='C';
        else if (base[i]=='T') base[i]='A';
    }
    for (int i = strlen(base)-1; i >= 0 ; i--) {
        cout << base[i];
    }
    //cout << endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    char base[1005];
    int a=0, c=0, g=0, t=0;
    scanf("%s",base);
    for (int i = 0; i < strlen(base); i++) {
        if (base[i]=='A') a++;
        else if (base[i]=='C') c++;
        else if (base[i]=='G') g++;
        else if (base[i]=='T') t++;
    }
    cout<<a<<" "<<c<<" "<<g<<" "<<t<<"\n";
    return 0;
}

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

string reverseComp (string base){

    int n = base.length();
    string reverse = base.substr(0, n);
    string comp = base.substr(0, n);
    for (int i = 0; i < n; i++) {
        if (base[i]=='A') comp[i]='T';
        else if (base[i]=='C') comp[i]='G';
        else if (base[i]=='G') comp[i]='C';
        else if (base[i]=='T') comp[i]='A';
    }


    for (int i = n-1; i >= 0 ; i--) {
        reverse[n-i-1] = comp[i];
    }
    //cout<<base<<" "<<comp<<" "<<reverse<<endl;
    return reverse;
}

int main() {
    string s;
    char base[1002];
    getline(cin, s); //>Rosalind ::: label

    int cnt = 0;
    while(getline(cin, s)){
        for (size_t i = 0; i < s.length(); i++) {
            if(s[i]=='A' || s[i]=='T' || s[i]=='G' || s[i]=='C'){
                base[cnt++] = s[i];
            }
        }
    }
    base[cnt] = '\0';

    string bps(base);
    //cout<<(bps);
    for (size_t pos = 0; pos < bps.length(); pos++) {
        for (size_t len = 4; len <= 12; len++) {
            string sub = bps.substr(pos, len);
            if(sub.length()!=len){
                break;
            }
            //cout<<pos<< " " << sub<<" " << reverseComp(sub)<<endl;
            if((reverseComp(sub)).compare(sub)==0){
                cout<<pos+1<<" "<<len<<" "<<endl;
                //cout<<pos+1<<" "<<len<<" "<<reverseComp(sub)<<" "<<sub<<endl;
            }
        }
    }

    return 0;
}

// pcov

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include<vector>
#include<algorithm>

using namespace std;


vector<string> collection;

string purifyString(string s){
    char base[51];
    int cnt = 0;
    for (size_t i = 0; i < s.length(); i++) {
        if(s[i]=='A' || s[i]=='T' || s[i]=='G' || s[i]=='C' ){
            base[cnt++] = s[i];
        }
    }
    base[cnt] = '\0';
    string s1(base);
    return s1;
}


string reverseComplement(string base){
    int len =  base.length();
    char* out = new char[len+1];
    out[len] = '\0';
    for (int i = 0; i < len; i++) {
        if (base[i]=='A') out[len-i-1]='T';
        else if (base[i]=='C') out[len-i-1]='G';
        else if (base[i]=='G') out[len-i-1]='C';
        else if (base[i]=='T') out[len-i-1]='A';
    }
    string outString(out);
    free(out);
    return outString;
}



bool hasEdge(string from, string to, int k){
    string overlapFrom = from.substr(1, k-1);
    string overlapTo = to.substr(0, k-1);
    return overlapFrom.compare(overlapTo)==0;
}

string assemble(int k){
    int n = collection.size();
    // n is the size of the final superstring
    //cout<<n<<endl;
    vector<string>::iterator it;

    // for ( it = collection.begin(); it != collection.end(); it++ )
    // {
    //     cout << '(' << *it << ')'<<endl;
    // }

    string assembled = collection.back();
    collection.pop_back();
    while(assembled.length() != n){
        string overlapTo = assembled.substr(0, k-1);
        for (int i = collection.size()-1; i >=0 ; i--) {
            string current = collection.at(i);
            if(hasEdge(current, overlapTo, k)){
                assembled= current[0] + assembled;
                //iter_swap(collection.begin()+i,collection.end());
                //collection.pop_back();
                collection.erase (collection.begin()+i);
                break;
            }
            /* code */
            //iter_swap(collection+3,collection.begin()+2);
            // collection.erase (collection.begin()+i);
        }
    }
    return assembled;

}


int main() {

    string kmer;
    getline(cin, kmer);
    kmer = purifyString(kmer);
    int k = kmer.length();
    collection.push_back(kmer);

    while(getline(cin, kmer)){
        kmer = purifyString(kmer);
        collection.push_back(kmer);
    }

    cout<<assemble(k);

    return 0;
}

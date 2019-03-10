// DBG graph construction

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include<map>
//#include<iterator>
#include<set>

using namespace std;

map<string, set<string> > adjList;

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


void makeEdgesFromK1mer(string k1mer, int k){
    //cout<<"main: "<<k1mer<<" ";
    string kmer1, kmer2;

    kmer1 = k1mer.substr(0, k);
    kmer2 = k1mer.substr(1, k);

    if(adjList.count(kmer1)==0){
        adjList[kmer1] = set<string>();
    }
    adjList[kmer1].insert(kmer2);

    k1mer = reverseComplement(k1mer);
    //cout<<" reverse: "<<k1mer<<endl;
    kmer1 = k1mer.substr(0, k);
    kmer2 = k1mer.substr(1, k);
    //cout<<adjList.count(kmer1);

    if(adjList.count(kmer1)==0){
        adjList[kmer1] = set<string>();
    }
    adjList[kmer1].insert(kmer2);
}

int main() {

    string k1mer;
    getline(cin, k1mer);
    k1mer = purifyString(k1mer);
    int k = k1mer.length() - 1;
    makeEdgesFromK1mer(k1mer, k);

    while(getline(cin, k1mer)){
        k1mer = purifyString(k1mer);
        //cout<<k1mer<<endl;
        makeEdgesFromK1mer(k1mer, k);
    }

    map<string, set<string> >::iterator it;

    for ( it = adjList.begin(); it != adjList.end(); it++ )
    {
        //cout<<it->first<<" :::: ";
        set<string> v = it->second;

        for (set<string> :: iterator i = v.begin(); i != v.end(); ++i){
            cout << '(' << it->first <<", " << *i << ')'<<endl;
        }
        //cout<<endl;
    }

    return 0;
}

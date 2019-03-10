//error correction

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include<map>
#include<set>

using namespace std;

map<string, int> readMap;
set<string> correct;
set<string> incorrect;



string letters[] = {"A", "C", "G", "T"};


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


int main() {

    string s;
    int readLength;
    while(getline(cin, s)){
        if (s.substr(0, 9) == ">Rosalind") continue;
        s = (purifyString(s));
        readLength = s.length();
        if(readMap.count(s)==0){
            readMap[(s)] = 1;
        }else{
            readMap[(s)]++;
        }
    }


    map<string, int >::iterator it;
    for ( it  = readMap.begin(); it != readMap.end(); it++ )
    {
        //cout << '(' << it->first <<", " << it->second << ')'<<endl;
        //cout<<endl;

        //reverse complement count
        string revcom = reverseComplement(it->first);
        if(it->second > 1){
            it->second = 10;
            correct.insert(it->first);
        }else if(revcom.compare(it->first)!=0 && readMap.count(revcom)!=0){
            it->second = 10;
            correct.insert(it->first);
        }else{
            incorrect.insert(it->first);
        }
    }

    // cout<<endl;
    // for ( it = readMap.begin(); it != readMap.end(); it++ )
    // {
    //         cout << '(' << it->first <<", " << it->second << ')'<<endl;
    //
    // }

    readMap.clear();

    set<string> ::iterator it2;
    // cout<<"correct list: "<<endl;
    // for (it2 = correct.begin(); it2 != correct.end(); it2++ )
    // {
    //         cout << '(' << *it2 << ')'<<endl;
    //
    // }
    //
    // cout<<"incorrect list: "<<endl;
    for (it2 = incorrect.begin(); it2 != incorrect.end(); it2++ )
    {

            bool found = false;

            //cout << '(' << *it2 << ')'<<endl;

            string incorrectStr = *it2;
            string corrected;
            for (size_t i = 0; i < readLength; i++) {
                for (size_t j = 0; j < 4; j++) {
                    if(incorrectStr.substr(i, 1).compare(letters[j])!=0){
                        string corrected(incorrectStr);
                        corrected = corrected.replace(i, 1, letters[j]);
                        if(correct.count(corrected) > 0){
                            cout<<incorrectStr << "->" << corrected<< endl;
                            found = true;
                        }
                    }

                    if(found) break;
                }
                if(found) break;
            }

            //reverse search
            if(found) continue;
            string reverseIncorrect = reverseComplement(incorrectStr);
            for (size_t i = 0; i < readLength; i++) {
                for (size_t j = 0; j < 4; j++) {
                    if(reverseIncorrect.substr(i, 1).compare(letters[j])!=0){
                        string corrected(reverseIncorrect);
                        corrected = corrected.replace(i, 1, letters[j]);
                        if(correct.count(corrected) > 0){
                            cout<<incorrectStr << "->" << reverseComplement(corrected)<< endl;
                        }
                    }
                }
                /* code */
            }


    }

    return 0;
}

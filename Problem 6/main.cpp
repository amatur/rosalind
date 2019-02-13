#include <iostream>
#include <string>
#include<sstream>
#include <cstring>
#include<map>

using namespace std;

char dict[] = "UUU F      CUU L      AUU I      GUU V UUC F      CUC L      AUC I      GUC V UUA L      CUA L      AUA I      GUA V UUG L      CUG L      AUG M      GUG V UCU S      CCU P      ACU T      GCU A UCC S      CCC P      ACC T      GCC A UCA S      CCA P      ACA T      GCA A UCG S      CCG P      ACG T      GCG A UAU Y      CAU H      AAU N      GAU D UAC Y      CAC H      AAC N      GAC D UAA Stop   CAA Q      AAA K      GAA E UAG Stop   CAG Q      AAG K      GAG E UGU C      CGU R      AGU S      GGU G UGC C      CGC R      AGC S      GGC G UGA Stop   CGA R      AGA R      GGA G UGG W      CGG R      AGG R      GGG G";

int main() {
    map<string, string> dictionary;

    string codon[64];
    string protein[64];
    istringstream iss(dict);
    for (size_t i = 0; i < 64; i++) {
        iss >> codon[i] >> protein[i];
        dictionary[codon[i]] = protein[i];
        //cout<<p<<" "<<e<<endl;
    }
    string rna;
    getline(cin, rna);
    for (size_t i = 0; i < rna.length(); i+=3) {
        string substr = rna.substr(i,3);
        if (dictionary [substr] == "Stop") break;
        cout << dictionary [substr];
    }

    return 0;
}

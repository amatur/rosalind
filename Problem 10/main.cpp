// GLOB - Global Alignment with Scoring Matrix

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include<map>

using namespace std;

map<char, int> charMap;
int** costMatrix;

int parseBlosum62(string filename="blosum62.txt"){
    string line;
    ifstream myfile (filename);
    if (!myfile.is_open())
        return -1;

    getline (myfile,line); //character titles
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    //cout<<line;

    char chars[20];
    for (size_t i = 0; i < 20; i++) {
        chars[i] = line[i];
        charMap[chars[i]] = i;
    }
    //cout<<"\n "<<chars[19]<<endl;


    costMatrix = new int*[20];
    for (size_t i = 0; i < 20; i++) {
        costMatrix[i] = new int[20];
    }

    for (size_t i = 0; i < 20; i++) {
        getline (myfile,line);
        stringstream ss(line);
        char c;
        ss>>c;
        for (size_t j = 0; j < 20; j++) {
            ss>>costMatrix[i][j];
            //costMatrix[i][j] *= -1;
        }

    }
    // for (size_t i = 0; i < 20; i++) {
    //     for (size_t j = 0; j < 20; j++) {
    //         cout<<costMatrix[i][j] << " ";
    //     }
    //     cout<<endl;
    // }

    myfile.close();
    return 0;
}


int alignCost(string X, string Y, int** cost, int gap){
    int m = X.length();
    int n = Y.length();
    //cout<<m<< " , "<<n<<endl;


    int** opt;
    opt = new int*[m+1];
    for (size_t i = 0; i <= m; i++) {
        opt[i] = new int[n+1];
    }

    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            opt[i][j] = 0;
        }
    }

    for (size_t i = 1; i <= m; i++) {
        opt[i][0] = -i*gap;
    }

    for (size_t j = 1; j <= n; j++) {
        opt[0][j] = -j*gap;
    }
    //opt[0][0] = 0;


    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            int a = charMap[X[i-1]];
            int b = charMap[Y[j-1]];
            //cout<<"a b "<<a<<" "<<b<<endl;
            int x = cost[a][b] + opt[i-1][j-1];
            int y = -gap + opt[i-1][j];
            int z = -gap + opt[i][j-1];
            opt[i][j] = max(max(x, y), z);
        }
    }

    // for (size_t i = 0; i < m; i++) {
    //     for (size_t j = 0; j < n; j++) {
    //         cout<<opt[i][j] << " ";
    //     }
    //     cout<<endl;
    // }
    return opt[m][n];

}

int main() {
    string s;
    getline(cin, s); //>Rosalind ::: label

    char base[1002];
    int cnt = 0;
    while(getline(cin, s)){
        if (s.substr(0, 9) == ">Rosalind") break;
        for (size_t i = 0; i < s.length(); i++) {
            if(isalnum(s[i])){
                base[cnt++] = s[i];
            }

        }
    }
    base[cnt] = '\0';
    string s1(base);

    cnt = 0;
    while(getline(cin, s)){
        for (size_t i = 0; i < s.length(); i++) {
            if(isalnum(s[i])){
                base[cnt++] = s[i];
            }
        }
    }
    base[cnt] = '\0';
    string s2(base);


    // s1.erase(remove(s1.begin(), s1.end(), ' '), s1.end());
    // s2.erase(remove(s2.begin(), s2.end(), ' '), s2.end());


    parseBlosum62();
    cout<<alignCost(s2, s1, costMatrix, 5);
    return 0;
}

//******* Problem Name: Local Alignment with Affine Gap Penalty (LAFF)  *****//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include<map>

using namespace std;
#define INFTY 99999999

map<char, int> charMap;
int** scoreMatrix;
int** traceback;

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


    scoreMatrix = new int*[20];
    for (size_t i = 0; i < 20; i++) {
        scoreMatrix[i] = new int[20];
    }

    for (size_t i = 0; i < 20; i++) {
        getline (myfile,line);
        stringstream ss(line);
        char c;
        ss>>c;
        for (size_t j = 0; j < 20; j++) {
            ss>>scoreMatrix[i][j];
            //scoreMatrix[i][j] *= -1;
        }

    }
    // for (size_t i = 0; i < 20; i++) {
    //     for (size_t j = 0; j < 20; j++) {
    //         cout<<scoreMatrix[i][j] << " ";
    //     }
    //     cout<<endl;
    // }

    myfile.close();
    return 0;
}


int alignscore(string X, string Y, int** score, int gapStart, int gapExtend, int& bestI, int& bestJ){
    int m = X.length();
    int n = Y.length();

    int** M, **XGAP, **YGAP;
    M = new int*[m+1];
    XGAP = new int*[m+1];
    YGAP = new int*[m+1];
    traceback = new int*[m+1];

    for (size_t i = 0; i <= m; i++) {
        M[i] = new int[n+1];
        XGAP[i] = new int[n+1];
        YGAP[i] = new int[n+1];
        traceback[i] = new int[n+1];
        // traceback[i] = new int*[n+1];
        // for (size_t j = 0; j <= n; j++) {
        //     traceback[i][j] = new int[3];
        // }
    }


    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            M[i][j] = 0;
            XGAP[i][j] = 0;
            YGAP[i][j] = 0;
            traceback[i][j] = 0;
        }
    }

    gapStart = -gapStart;
    gapExtend = -gapExtend;


    //base cases
    // for (size_t i = 1; i <= m; i++) {
    //     XGAP[i][0] =  0; //-INFTY if global alignment
    //     M[i][0] = 0;    //-INFTY if global alignment
    //     YGAP[i][1] = gapStart + gapExtend*(i-1);
    // }
    //
    //
    // for (size_t j = 1; j <= n; j++) {
    //     XGAP[1][j] =  gapStart + gapExtend*(j-1);
    //     YGAP[0][j] =  0; //-INFTY if global alignment
    //     M[0][j] = 0;    //-INFTY if global alignment
    // }

    int maxScore = -INFTY;

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            int a = charMap[X[i-1]];
            int b = charMap[Y[j-1]];
            //
            // M[i][j] = max(score[a][b] + max(max(XGAP[i-1][j-1], YGAP[i-1][j-1]),  M[i-1][j-1]), 0);
            //
            // XGAP[i][j] =  (max(max(gapStart + gapExtend + M[i][j-1], gapStart + gapExtend + YGAP[i][j-1]),  gapExtend + XGAP[i][j-1]));
            //
            // YGAP[i][j] =  (max(max(gapStart + gapExtend + M[i-1][j], gapStart + gapExtend + XGAP[i-1][j]),  gapExtend + YGAP[i-1][j]));
            //
            // if(M[i][j] > maxScore){
            //     maxScore = M[i][j] ;
            //
            // }
            M[i][j] = max(score[a][b] + max(max(XGAP[i-1][j-1], YGAP[i-1][j-1]),  M[i-1][j-1]), 0);
            if(M[i][j] > maxScore){
                maxScore = M[i][j] ;
                bestI = i;
                bestJ = j;

            }


            if(M[i][j] - score[a][b] == M[i-1][j-1]){
                traceback[i][j] = 1;
            }else if(M[i][j] - score[a][b] == XGAP[i-1][j-1]){
                traceback[i][j] = 2;
            }else if(M[i][j] - score[a][b] == YGAP[i-1][j-1]){
                traceback[i][j] = 3;
            }else{
                traceback[i][j] = 0;
            }


            XGAP[i][j] =  (max(max(gapStart + M[i][j-1], gapStart + YGAP[i][j-1]),  gapExtend + XGAP[i][j-1]));

            YGAP[i][j] =  (max(max(gapStart + M[i-1][j], gapStart  + XGAP[i-1][j]),  gapExtend + YGAP[i-1][j]));


        }
    }

//     for (size_t i = 0; i <= m; i++) {
//         for (size_t j = 0; j <= n; j++) {
//             cout<<M[i][j] << " ";
//         }
//         cout<<endl;
//     }
//
// cout<<endl;
//     for (size_t i = 0; i <= m; i++) {
//         for (size_t j = 0; j <= n; j++) {
//             cout<<XGAP[i][j] << " ";
//         }
//         cout<<endl;
//     }
// cout<<endl;
//
//     for (size_t i = 0; i <= m; i++) {
//         for (size_t j = 0; j <= n; j++) {
//             cout<<YGAP[i][j] << " ";
//         }
//         cout<<endl;
//     }
    return maxScore;

}

int main() {
    string s;
    getline(cin, s); //>Rosalind ::: label

    char base[10002];
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

    int gapStart = 11;
    int gapExtend = 1;

    int i, j, bestI, bestJ;
    parseBlosum62();
    cout<<alignscore(s1, s2, scoreMatrix, gapStart, gapExtend, bestI, bestJ)<<endl;

    i = bestI;
    j = bestJ;
    while(traceback[i][j] != 0 && (i!=0 || j!=0) ){
        if(traceback[i][j] == 1){ //from M
            i--;
            j--;
        }else if(traceback[i][j] == 2){ //from X
            j--;
        }else if(traceback[i][j] == 3){ //from Y
            i--;
        }
    }
    cout<<s1.substr(i, bestI-i)<<endl;
    cout<<s2.substr(j, bestJ-j)<<endl;

    return 0;
}

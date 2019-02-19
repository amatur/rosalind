// Global Alignment with Scoring Matrix, Linear Space (Hirschberg)

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include<map>

#define DIAG 1
#define LEFT 2
#define DOWN 3

#define INFTY 999999


using namespace std;

map<char, int> charMap;
int** costMatrix;

int parseBlosum62(){
    stringstream blosumString("A  C  D  E  F  G  H  I  K  L  M  N  P  Q  R  S  T  V  W  Y\nA  4  0 -2 -1 -2  0 -2 -1 -1 -1 -1 -2 -1 -1 -1  1  0  0 -3 -2\nC  0  9 -3 -4 -2 -3 -3 -1 -3 -1 -1 -3 -3 -3 -3 -1 -1 -1 -2 -2\nD -2 -3  6  2 -3 -1 -1 -3 -1 -4 -3  1 -1  0 -2  0 -1 -3 -4 -3\nE -1 -4  2  5 -3 -2  0 -3  1 -3 -2  0 -1  2  0  0 -1 -2 -3 -2\nF -2 -2 -3 -3  6 -3 -1  0 -3  0  0 -3 -4 -3 -3 -2 -2 -1  1  3\nG  0 -3 -1 -2 -3  6 -2 -4 -2 -4 -3  0 -2 -2 -2  0 -2 -3 -2 -3\nH -2 -3 -1  0 -1 -2  8 -3 -1 -3 -2  1 -2  0  0 -1 -2 -3 -2  2\nI -1 -1 -3 -3  0 -4 -3  4 -3  2  1 -3 -3 -3 -3 -2 -1  3 -3 -1\nK -1 -3 -1  1 -3 -2 -1 -3  5 -2 -1  0 -1  1  2  0 -1 -2 -3 -2\nL -1 -1 -4 -3  0 -4 -3  2 -2  4  2 -3 -3 -2 -2 -2 -1  1 -2 -1\nM -1 -1 -3 -2  0 -3 -2  1 -1  2  5 -2 -2  0 -1 -1 -1  1 -1 -1\nN -2 -3  1  0 -3  0  1 -3  0 -3 -2  6 -2  0  0  1  0 -3 -4 -2\nP -1 -3 -1 -1 -4 -2 -2 -3 -1 -3 -2 -2  7 -1 -2 -1 -1 -2 -4 -3\nQ -1 -3  0  2 -3 -2  0 -3  1 -2  0  0 -1  5  1  0 -1 -2 -2 -1\nR -1 -3 -2  0 -3 -2  0 -3  2 -2 -1  0 -2  1  5 -1 -1 -3 -3 -2\nS  1 -1  0  0 -2  0 -1 -2  0 -2 -1  1 -1  0 -1  4  1 -2 -3 -2\nT  0 -1 -1 -1 -2 -2 -2 -1 -1 -1 -1  0 -1 -1 -1  1  5  0 -2 -2\nV  0 -1 -3 -2 -1 -3 -3  3 -2  1  1 -3 -2 -2 -3 -2  0  4 -3 -1\nW -3 -2 -4 -3  1 -2 -2 -3 -3 -2 -1 -4 -4 -2 -3 -3 -2 -3 11  2\nY -2 -2 -3 -2  3 -3  2 -1 -2 -1 -1 -2 -3 -1 -2 -2 -2 -1  2  7");

    string line;

    getline (blosumString,line); //character titles
    line.erase(remove(line.begin(), line.end(), ' '), line.end());

    char chars[20];
    for (size_t i = 0; i < 20; i++) {
        chars[i] = line[i];
        charMap[chars[i]] = i;
    }

    costMatrix = new int*[20];
    for (size_t i = 0; i < 20; i++) {
        costMatrix[i] = new int[20];
    }

    for (size_t i = 0; i < 20; i++) {
        getline (blosumString,line);
        stringstream ss(line);
        char c;
        ss>>c;
        for (size_t j = 0; j < 20; j++) {
            ss>>costMatrix[i][j];
        }
    }

    // for (size_t i = 0; i < 20; i++) {
    //     for (size_t j = 0; j < 20; j++) {
    //         cout<<costMatrix[i][j] << " ";
    //     }
    //     cout<<endl;
    // }

    return 0;
}

int scoreNW_linearSpace(string X, string Y, int** cost, int gap, int* lastLine){
    int m = X.length();
    int n = Y.length();

    // let the matrix OPT size be 2*Ylen = 2n
    int** opt;
    opt = new int*[2];    //num of rows = 2
    for (size_t i = 0; i < 2; i++) {
        opt[i] = new int[n+1];
    }

    opt[0][0] = 0;
    //opt[1][0] = -gap;
    for (size_t j = 1; j <= n; j++) {
        opt[0][j] = - j*gap;
    }


    for (size_t i = 1; i <= m; i++) {
        opt[1][0] = opt[0][0] - gap;
        for (size_t j = 1; j <= n; j++) {
            //replace i with 1, i-1 with 0

            int a = charMap[X[i-1]];    // careful with index here
            int b = charMap[Y[j-1]];
            //cout<<"a b "<<a<<" "<<b<<endl;
            int x = cost[a][b] + opt[0][j-1]; //cost[a][b] + opt[i-1][j-1];
            int y = -gap + opt[0][j]; //-gap + opt[i-1][j];
            int z = -gap + opt[1][j-1]; //-gap + opt[i][j-1];
            opt[1][j] = max(max(x, y), z);
        }

        // copy row 1 to row 0
        for (size_t j = 0; j <= n; j++) {
            opt[0][j] = opt[1][j];
        }

    }


    for (size_t j = 0; j <= n; j++) {
        lastLine[j] = opt[1][j];
    }
    // for (size_t i = 0; i < m; i++) {
    //     for (size_t j = 0; j < n; j++) {
    //         cout<<opt[i][j] << " ";
    //     }
    //     cout<<endl;
    // }
    return opt[1][n];

}


void alignedStringsNW(string X, string Y, int** cost, int gap, string& Z, string& W){
    int m = X.length();
    int n = Y.length();

    int** opt;
    int** traceback;

    opt = new int*[m+1];
    traceback = new int*[m+1];

    for (size_t i = 0; i <= m; i++) {
        opt[i] = new int[n+1];
        traceback[i] = new int[n+1];
    }

    for (size_t i = 0; i < 2; i++) {
        opt[i] = new int[n+1];
        traceback[i] = new int[n+1];
    }

    opt[0][0] = 0;
    traceback[0][0] = 0;

    for (size_t i = 1; i <= m; i++) {
        opt[i][0] = -i*gap;
        traceback[i][0] = DOWN;
    }

    for (size_t j = 1; j <= n; j++) {
        opt[0][j] = -j*gap;
        traceback[0][j] = LEFT;
    }

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            int a = charMap[X[i-1]];
            int b = charMap[Y[j-1]];
            //cout<<"a b "<<a<<" "<<b<<endl;
            int x = cost[a][b] + opt[i-1][j-1];
            int y = -gap + opt[i-1][j];
            int z = -gap + opt[i][j-1];
            opt[i][j] = max(max(x, y), z);

            if(opt[i][j] == x){
                traceback[i][j] = DIAG; //diag
            }else if(opt[i][j] == y){
                traceback[i][j] = DOWN;//from down
            }else if(opt[i][j] == z){
                traceback[i][j] = LEFT;//from left
            }


        }
    }

    Z = "";
    W = "";
    int i = m;
    int j = n;
    while(traceback[i][j] != 0){
        if(traceback[i][j] == DIAG){
            W = Y[j-1] + W;
            Z = X[i-1] + Z;
            i--;
            j--;
        }else if(traceback[i][j] == LEFT){
            W = Y[j-1] + W;
            Z = "-" + Z;
            j--;
        }else if(traceback[i][j] == DOWN){
            W = "-" + W;
            Z = X[i-1] + Z;
            i--;
        }
    }

    // for (size_t i = 0; i <= m; i++) {
    //     for (size_t j = 0; j <= n; j++) {
    //         cout<<opt[i][j] << " ";
    //     }
    //     cout<<endl;
    // }
    //
    //
    // for (size_t i = 0; i <= m; i++) {
    //     for (size_t j = 0; j <= n; j++) {
    //         cout<<traceback[i][j] << " ";
    //     }
    //     cout<<endl;
    // }

    return;
}


void Hirschberg(string X, string Y, int** cost, int gap, string& Z, string& W){

    // Following the pseudocode in wikipedia

    int m = X.length();
    int n = Y.length();

    if (m==0){
        for (size_t j = 1; j <= n; j++){
            Z = Z + "-"; //optimization: use char array
            W = W + Y[j-1];
        }
    }else if(n==0){
        for (size_t i = 1; i <= m; i++){
            Z = Z + X[i-1];
            W = W + "-";
        }

    }else if(m == 1 || n == 1){
        alignedStringsNW(X, Y, cost, gap, Z, W);
    }else{
        int xlen = m;
        int xmid = m/2;
        int ylen = n;

        string XLeft = X.substr(0, xmid);
        string XRight =  X.substr(xmid, xlen-xmid);

        string XRightRev(XRight);
        string YRev(Y);
        reverse(YRev.begin(), YRev.end());
        reverse(XRightRev.begin(), XRightRev.end());

        int* scoreLeft = new int[n+1];
        int* scoreRight = new int[n+1];

        scoreNW_linearSpace(XLeft, Y, cost, gap, scoreLeft);
        scoreNW_linearSpace(XRightRev, YRev, cost, gap, scoreRight);

        int maxscore = -INFTY;
        int ymid = 0;
        for (size_t j = 0; j <=n ; j++) {
            if(scoreLeft[j] + scoreRight[n-j] > maxscore){
                maxscore = scoreLeft[j] + scoreRight[n-j];
                ymid = j;
            }
        }

        string YDown = Y.substr(0, ymid);
        string YTop = Y.substr(ymid, ylen);

        string Z1, Z2, W1, W2;
        Hirschberg(XLeft, YDown, cost, gap, Z1, W1);
        Hirschberg(XRight, YTop, cost, gap, Z2, W2);
        Z = Z1 + Z2;
        W = W1 + W2;
    }
}



int main() {

    // read two lines s1 and s2
    string X, Y;
    getline(cin, X);
    getline(cin, Y);

    parseBlosum62();

    string Z = "";
    string W = "";

    int* p = new int[Y.length()+1];
    cout<<scoreNW_linearSpace( X,  Y,  costMatrix, 5, p)<<endl;
    //alignedStringsNW(Y, X, costMatrix, 5, Z, W);
    Hirschberg(X, Y, costMatrix, 5, Z, W);
    cout<<Z<<endl;
    cout<<W<<endl;


    return 0;
}

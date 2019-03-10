// pcov

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include<vector>
#include <algorithm>
#include<map>
#include<set>
#include<stack>

using namespace std;


vector <string>  kmerList;


string purifyString(string s){
    char base[51];
    int cnt = 0;
    for (int i = 0; i < s.length(); i++) {
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

int countEdges(map<string, vector<string> > adjList){
    int cnt  = 0;
    for(map<string, vector<string> > :: iterator it = adjList.begin(); it!=adjList.end(); it++){
        cnt += (it->second).size();
    }
    return cnt;
}


void printGraph(map<string, vector<string> > adjList){

        for (map<string, vector<string> > ::iterator it = adjList.begin(); it != adjList.end(); it++ )
        {
            //cout<<it->first<<" :::: ";
            vector<string> v = it->second;

            if(v.empty()){
                cout << '(' << it->first <<", " << " --- " << ')'<<endl;
            }

            for (vector<string> :: iterator i = v.begin(); i != v.end(); ++i){
                cout << '(' << it->first <<", " << *i << ')'<<endl;
            }
            //cout<<endl;
        }
}


vector<string> DFS(int k, map<string, vector<string> > adjList, string v, vector<string> circuitSoFar){
    //cout<<"call";
    //printGraph(adjList);
    vector<string> circuit(circuitSoFar.begin(),circuitSoFar.end());
    //cout<<adjList[v].size();
    if(adjList[v].size() != 0){
        int i = 0;
        int n = adjList[v].size() ;
        while(true){
            //cout<<i<<endl;
            if(i==n) break;
            string neighborString = adjList[v].at(i);
            //remove edge
            circuit.push_back(adjList[v].at(i));
            //map<string, vector<string> > adjListCopy;
            //adjListCopy.insert(adjList.begin(), adjList.end());
            adjList[v].erase(adjList[v].begin() + i);
            //cout<<adjList[v].size();
            //edgeCount[s.nodeLabel]--;

            //printGraph(adjList);
            DFS(k, adjList, neighborString, circuit);
            //cout<<"after"<<endl;
            //printGraph(adjList);
            adjList[v].push_back(neighborString);

            i++;

            //add edge back
        }
    }else{
        //circuit.push_back(v);
        //
        //print circuit so circuitSo circuitSoFar
        for (int i = 0; i<circuitSoFar.size(); i++) {
            cout<<circuitSoFar.at(i)<< " ";
        }
        cout<<endl;
       // Back-tracking
    }
    return circuit;
}




void assemble(int k, map<string, vector<string> > adjList){
    string start = kmerList.at(0).substr(1, k-1);
    vector<string> ck;
    ck.push_back(start);

    vector<string>::iterator it = find(adjList[kmerList.at(0).substr(0, k-1)].begin(), adjList[kmerList.at(0).substr(0, k-1)].end(), start);
    adjList[kmerList.at(0).substr(0, k-1)].erase(it);
    printGraph(adjList);

    vector<string> vec = DFS(k, adjList, start, ck);
    for (int i = 0; i<vec.size(); i++) {
        cout<<vec.at(i)<< " ";
    }
    cout<<endl;
}

map<string, vector<string> > makeDBGfromKmers(vector<string> kmerList, int k){
    map<string, vector<string> > adjList; //simple cycle

    for(vector<string>:: iterator it=kmerList.begin(); it!=kmerList.end(); ++it){
        string kmer = *it;
        //cout<<"main: "<<k1mer<<" ";

        string kmerFrom, kmerTo;

        kmerFrom = kmer.substr(0, k-1);
        kmerTo = kmer.substr(1, k-1);

        // if(adjList.count(kmerFrom)==0){
        //     adjList[kmerFrom] = vector<string>();
        // }
        adjList[kmerFrom].push_back(kmerTo);
        //cout<<kmerFrom<<" -> "<<kmerTo<<endl;
        //added
        if(adjList.count(kmerTo)==0){
            adjList[kmerTo] = vector<string>();
        }

        string kmerToRC = reverseComplement(kmerTo);
        string kmerFromRC = reverseComplement(kmerFrom);

        //cout<<kmerToRC<<" -> "<<kmerFromRC<<endl;
        adjList[kmerToRC].push_back(kmerFromRC);
        if(adjList.count(kmerFromRC)==0){
            adjList[kmerFromRC] = vector<string>();
        }
    }

    return adjList;
}



int main() {


    map<string, vector<string> > adjList;

    string kmer;
    getline(cin, kmer);
    kmer = purifyString(kmer);
    int k = kmer.length();  //l = read length
    kmerList.push_back(kmer);


    while(getline(cin, kmer)){
        kmer = purifyString(kmer);
        kmerList.push_back(kmer);
    }

    adjList = makeDBGfromKmers(kmerList, k); //edge: (k+1) mer, node: k mer, however k is +1
//printGraph(adjList);
    assemble(k, adjList);


    return 0;
}

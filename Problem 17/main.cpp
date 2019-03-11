// grep

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
int glob;
int line2;
set<string> results;


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
    cout<<"PRINTING GRAPH: "<<endl;
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

void printVector(vector<string> v){
    for (size_t i = 0; i < v.size(); i++) {
        cout<<v[i]<< " ";
    }
    cout<<endl;

}


vector<string> DFS(int k, map<string, vector<string> > & adjList, string v, vector<string> circuit){
    glob++;
    //cout<<glob<<endl;
    //cout<<"call";
    //printGraph(adjList);
    vector<string> circuitLocal(circuit.begin(),circuit.end());
    //cout<<adjList[v].size();
    if(adjList[v].size() != 0){

        int n = adjList[v].size() ;
        int i = n-1;
        while(true){
            //cout<<i<<endl;
            if(i==-1) break;
            string neighborString = adjList[v].at(i);
            //remove edge
            circuitLocal.push_back(adjList[v].at(i));

            adjList[v].erase(adjList[v].begin() + i);

            //if(line2==10) cout<<adjList["CA"][1]<<" SSXXXXXS"<<endl;

            //map<string, vector<string> > adjListCopy;
            //adjListCopy.insert(adjList.begin(), adjList.end());
            //adjListCopy[v] = neighList;
            //cout<<adjList[v].size();
            //edgeCount[s.nodeLabel]--;

            //vector<string> neighList2;
            //for (int x=0; x<adjList[neighborString].size(); x++)
            //  neighList2.push_back(adjList[neighborString][x]);
            //printGraph(adjList);

            //if(glob<100)
            DFS(k, adjList, neighborString, circuitLocal);
            //cout<<"after"<<endl;
            //printGraph(adjList);
            adjList[v].push_back(neighborString);
            circuitLocal.pop_back();
            // while(!circuitLocal.empty()){
            //     circuitLocal.pop_back();
            // }
            // for (size_t x = 0; x < circuit.size(); x++) {
            //     circuitLocal.push_back(circuit[]);
            // }

            i--;

            //add edge back
        }
    }else{
        //circuit.push_back(v);
        //
        //print circuit so circuitSo circuitSoFar
        line2++;

        if(circuitLocal.size() == kmerList.size()+1){
            for (int i = 0; i<circuitLocal.size(); i++) {
                //cout<<circuitLocal.at(i)<< " ";
            }
            string out = "";
            for (int i = 0; i<kmerList.size(); i++) {
                out+=circuitLocal.at(i)[0];
            }
            results.insert(out);

            //cout<<out<<endl;

        }

        //printGraph(adjList);
        //cout<<endl;
       // Back-tracking
    }
    return circuit;
}




void assemble(int k, map<string, vector<string> > adjList){

    string startVertex = kmerList.at(0).substr(1, k-1);
    //cout<<startVertex;

    vector<string> ck;
    ck.push_back(kmerList.at(0).substr(0, k-1));
    ck.push_back(startVertex);

    vector<string>::iterator it = find(adjList[kmerList.at(0).substr(0, k-1)].begin(), adjList[kmerList.at(0).substr(0, k-1)].end(), startVertex);
    //
    adjList[kmerList.at(0).substr(0, k-1)].erase(it);
     //printGraph(adjList);


    vector<string> vec = DFS(k, adjList, startVertex, ck);
}

bool hasEdge(string from, string to, int k){
    string overlapFrom = from.substr(1, k-1);
    string overlapTo = to.substr(0, k-1);
    return overlapFrom.compare(overlapTo)==0;
}

map<string, vector<string> > makeDBGfromKmers(vector<string> kmerList, int k){

    map<string, vector<string> > adjList; //simple cycle


    for(vector<string>:: iterator it=kmerList.begin() ; it!=kmerList.end(); ++it){
        string kmer = *it;

        string kmerFrom = kmer.substr(0, k-1);
        string kmerTo = kmer.substr(1, k-1);

        adjList[kmerFrom].push_back(kmerTo);
        //cout<<kmerFrom<<" -> "<<kmerTo<<endl;
        //added
        if(adjList.count(kmerTo)==0){
            adjList[kmerTo] = vector<string>();
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

   for(set<string> :: iterator it=results.begin(); it!=results.end(); ++it){
       cout<<*it<<endl;
   }
 // printGraph(adjList);

    return 0;
}

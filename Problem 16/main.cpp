// pcov

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include<vector>
#include<map>
#include<set>
#include<stack>

using namespace std;

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

int countEdges(map<string, set<string> > adjList){
    int cnt  = 0;
    for(map<string, set<string> > :: iterator it = adjList.begin(); it!=adjList.end(); it++){
        cnt += (it->second).size();
    }
    return cnt;
}


void printGraph(map<string, set<string> > adjList){

        for (map<string, set<string> > ::iterator it = adjList.begin(); it != adjList.end(); it++ )
        {
            //cout<<it->first<<" :::: ";
            set<string> v = it->second;

            if(v.empty()){
                cout << '(' << it->first <<", " << " --- " << ')'<<endl;
            }
            for (set<string> :: iterator i = v.begin(); i != v.end(); ++i){
                cout << '(' << it->first <<", " << *i << ')'<<endl;
            }
            //cout<<endl;
        }
}


bool hasEdge(string from, string to, int k){
    string overlapFrom = from.substr(1, k-1);
    string overlapTo = to.substr(0, k-1);
    return overlapFrom.compare(overlapTo)==0;
}

bool assemble(int k, map<string, set<string> > adjList){  //dfs


    // Initially mark all verices as not visited
    //printGraph(adjList);
    //make a copy of adjlist
    map<string, set<string> > adjListCopy;
    adjListCopy.insert(adjList.begin(), adjList.end());

    int numVertices = adjList.size();
    //cout<<"edges: "<<countEdges(adjList)<<endl;
    //inefficient
    map<string, bool> visited;
    for ( map<string, set<string> > :: iterator it = adjList.begin(); it != adjList.end(); ++it){
        visited[it->first] = false;
    }

    // Create a stack for DFS
    stack<string> stack;
    string s;
    string start = adjList.begin()->first;
    stack.push(adjList.begin()->first);

    string assembled = "";

    //cout<<"starting at: "<<start<<endl;
    while(!stack.empty()){
        s = stack.top();
        stack.pop();

        if (!visited[s])
        {
            //cout << s << " ";
            assembled = assembled + s[k-2] ;
            visited[s] = true;
        }

        set<string> adjS = adjList[s];

        if(!adjS.empty()){
            string firstNeighbor = *(adjS.begin());
            adjListCopy[s].erase(firstNeighbor);

            if (!visited[firstNeighbor]){
                stack.push(firstNeighbor);
            }else{
                //assembled = assembled + firstNeighbor[k-2];
                //cout<< (firstNeighbor)  <<endl;
                break;
            }
        }else{
            break;
        }
    }



    while(!stack.empty()){
        stack.pop();
    }
    start = reverseComplement(start);
    stack.push((start));

    //cout<<endl;
    //cout<<"starting RC: "<<start<<endl;


    while(!stack.empty()){
        s = stack.top();
        stack.pop();

        if (!visited[s])
        {
            //cout << s << " ";
            visited[s] = true;
        }

        set<string> adjS = adjList[s];

        if(!adjS.empty()){
            string firstNeighbor = *(adjS.begin());
            adjListCopy[s].erase(firstNeighbor);

            if (!visited[firstNeighbor]){
                stack.push(firstNeighbor);
            }else{
                //cout<< (firstNeighbor)  <<endl;
                break;
            }
        }else{
            break;
        }
    }

    //cout<<"copy edges: "<<countEdges(adjListCopy)<<endl;

    //cout<<"FINAL: "<<assembled<<endl;

    if(countEdges(adjListCopy) == 0){
        cout<<assembled;
    }
    return countEdges(adjListCopy) == 0;
}



map<string, set<string> > makeDBGfromKmers(set<string> kmer_set, int k){
    map<string, set<string> > adjList; //simple cycle

    for(set<string>:: iterator it=kmer_set.begin(); it!=kmer_set.end(); ++it){
        string kmer = *it;
        //cout<<"main: "<<k1mer<<" ";

        string kmerFrom, kmerTo;

        kmerFrom = kmer.substr(0, k-1);
        kmerTo = kmer.substr(1, k-1);

        if(adjList.count(kmerFrom)==0){
            adjList[kmerFrom] = set<string>();
        }
        adjList[kmerFrom].insert(kmerTo);


        //added
        if(adjList.count(kmerTo)==0){
            adjList[kmerTo] = set<string>();
        }
    }

    return adjList;
}


set<string> splitReadsToKmers(vector<string> reads, int k, int l){
    set<string> kmerset;

    //cout<<"for k = "<<k<<endl;
    for ( vector<string>::iterator it = reads.begin(); it != reads.end(); it++ )
   {
       string read = *it;
       //cout << "Read: (" << *it << ')'<<endl;
       for (int i = 0; l - i + 1 > k; i++) {
           string kmer = read.substr(i, k);
           kmerset.insert(kmer);
           kmerset.insert(reverseComplement(kmer));

           //cout<<kmer<< " ";
       }

   }
    //cout<<endl;
    return kmerset;
}


int main() {

    set<string> kmer_set;
    vector<string> reads;
    map<string, set<string> > adjList;

    string read;
    getline(cin, read);
    read = purifyString(read);
    int l = read.length();  //l = read length
    reads.push_back(read);


    while(getline(cin, read)){
        read = purifyString(read);
        reads.push_back(read);
    }

    //try assemble for all k
    for (int k = l; k >= 2; k--) {
        kmer_set = splitReadsToKmers(reads, k, l);
        adjList = makeDBGfromKmers(kmer_set, k); //edge: kmer, node: k-1 mer
        //We have a dBG constructed at this point
        bool twoCycle = assemble(k, adjList);
        //cout<<"k " << k << ", ASSEMBLED " <<endl;
        if(twoCycle) break;
    }





    return 0;
}

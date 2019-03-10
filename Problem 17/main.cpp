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


vector <string>  kmerList;

class elem
{
    public:
    string nodeLabel;
    string assembled;
    elem(string n, string a)
    {
        nodeLabel = n;
        assembled = a;
    }

    // ostream& operator<< (ostream &out, elem const& data) {
    //     out << data.nodeLabel << ':';
    //     out << data.assembled << '';
    //
    //     return out;
    // }
};

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


bool hasEdge(string from, string to, int k){
    string overlapFrom = from.substr(1, k-1);
    string overlapTo = to.substr(0, k-1);
    return overlapFrom.compare(overlapTo)==0;
}


bool assemble(int k, map<string, vector<string> > adjList){  //dfs


    // Initially mark all verices as not visited
    //printGraph(adjList);
    //make a copy of adjlist
    map<string, vector<string> > adjListCopy;
    adjListCopy.insert(adjList.begin(), adjList.end());
    //printGraph(adjListCopy);
    //
    int numVertices = adjList.size();
    // //cout<<"edges: "<<countEdges(adjList)<<endl;
    //inefficient
    map<string, int> edgeCount;
    for ( map<string, vector<string> > :: iterator it = adjList.begin(); it != adjList.end(); ++it){
        edgeCount[it->first] = it->second.size();
    }



    // Create a stack for DFS
    stack<elem> stack;



//string start = kmerList.at(0).substr(0, k-1);
    string start = kmerList.at(0).substr(1, k-1);
    string assembled = "";
    //cout<<start;

    elem s(start, assembled);
    stack.push(s);


        // vector to store final circuit
        vector<string> circuit;

    cout<<"starting at: "<<start<<endl;
    while(!stack.empty()){
        // If there's remaining edge
        if (edgeCount[s.nodeLabel]!=0)
        {
            // Push the vertex
            stack.push(s);

            // Find the next vertex using an edge
            string nextNodeLabel = adjList[s.nodeLabel].back();

            // and remove that edge
            edgeCount[s.nodeLabel]--;
            adjList[s.nodeLabel].pop_back();

            // Move to next vertex
            elem nextNode(nextNodeLabel, assembled);
            s = nextNode;
        }

        // back-track to find remaining circuit
        else
        {
            circuit.push_back(s.nodeLabel);

            // Back-tracking
            s = stack.top();
            stack.pop();
        }




        // s = stack.top();
        // stack.pop();
        //
        // //if (!visited[s])
        // //{
        // cout << "elem: " <<s.nodeLabel << ", " <<s.assembled<<endl;
        // assembled = assembled + s.nodeLabel[0] ;
        //     //visited[s] = true;
        // //}
        // //
        // vector<string> adjS = adjList[s.nodeLabel];
        // if(adjS.empty()){
        //     cout<<"copy edges: "<<countEdges(adjList)<<endl;
        //     if(countEdges(adjList) == 0){
        //         cout<<assembled<<" asss"<<endl;
        //     }
        //     //continue;
        // }
        // for(vector<string> :: iterator it = adjS.begin(); it!= adjS.end(); it++){
        //     string neighbor = (*it);
        //     stack.push(elem(neighbor,assembled));
        // }



    }


     for (int i=circuit.size()-1; i>=0; i--) {
        cout<<circuit.at(i)<<" ";
    }
    cout<<endl;


    cout<<"copy edges: "<<countEdges(adjListCopy)<<endl;

    cout<<"FINAL: "<<assembled<<endl;

    if(countEdges(adjListCopy) == 0){
        cout<<assembled;
    }
    return countEdges(adjListCopy) == 0;
    //return false;
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
        cout<<kmerFrom<<" -> "<<kmerTo<<endl;
        //added
        if(adjList.count(kmerTo)==0){
            adjList[kmerTo] = vector<string>();
        }

        string kmerToRC = reverseComplement(kmerTo);
        string kmerFromRC = reverseComplement(kmerFrom);

        cout<<kmerToRC<<" -> "<<kmerFromRC<<endl;
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
    bool twoCycle = assemble(k, adjList);


    return 0;
}

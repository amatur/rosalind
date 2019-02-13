#include<iostream>
#include<cstring>
#include<cctype>
#include<fstream>
#include <vector>

#define ALPHABET_SIZE 4
// A C G T - 4 characters possible in DNA string

using namespace std;


char arrIndex(char base)
{
    switch(base) {
        case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
		case '$': return 4;
        default: return -1;
    }
}




class Node
{
public:
	Node *parent = NULL;

	int startIndex = 0;
	int endIndex = -1;
    int suffixIndex;
	Node* children[ALPHABET_SIZE+1];


	void init(){
		for (size_t i = 0; i < ALPHABET_SIZE + 1; i++) {
			children[i] = NULL;
		}
	}

	Node(){
		init();
	}

	Node(int start, int end, Node* parent){
		init();
		this->startIndex = start;
		this->endIndex = end;
		this->parent = parent;
	}

	bool isRoot(){
		return parent == NULL;
	}

	string edgeString(string str){
		if (isRoot()) return "";
		string s = str.substr(startIndex, endIndex - startIndex + 1);
		return s;
	}

	int edgeLength(){
		if (isRoot()) return 0;
		return endIndex - startIndex + 1;
	}
};




class SuffixTree
{

public:
	string str;
	Node* root;

	void postorder(Node* roott){
		if(roott==NULL){
			return;
		}
		for (size_t i = 0; i < ALPHABET_SIZE+1; i++) {
			postorder(roott->children[i]);
		}
		if(roott!=root)
            cout<<roott->edgeString(str)<<" ";
	}

	void preorder(Node* roott){
		if(roott==NULL){
			return;
		}
        if(roott!=root){
            cout<<roott->edgeString(str)<<endl;

        }

		for (size_t i = 0; i < ALPHABET_SIZE+1; i++) {
			preorder(roott->children[i]);
		}
	}

	SuffixTree(string inputString)	//build the suffix tree with inputString
	{
		int n = inputString.length();		// n = size of string
		this->str = inputString;
		this->root = new Node(0, -1, NULL);

		Node *activeNode = this->root;

        for (size_t i = 0; i < n; i++) {
            //if(i==3) break;
            if(i==0){
                Node* nd = new Node(0, n-1, root);
                nd->suffixIndex = 0;
                int childIndex = arrIndex(str.at(i));
                root->children[childIndex] = nd;

            }else{
                activeNode = this->root;
                int childIndex = arrIndex(str.at(i));

                if (activeNode->children[childIndex] == NULL){
                    Node* nd = new Node(i, n-1, activeNode);
                    nd->suffixIndex = i;
                    activeNode->children[childIndex] = nd;


                }else{
                    activeNode = activeNode->children[childIndex] ;
                    int childI = activeNode->startIndex;
                    int activeStrI = i;
                    int lenMatched = 0;
                    int lenEdge = activeNode->edgeLength();

                    while(1){
                        if(str.at(childI)==str.at(activeStrI)){
                            childI++;
                            activeStrI++;
                            lenMatched++;
                            if(lenMatched == lenEdge){
                                //cout<<"yes";
                                childIndex = arrIndex(str.at(activeStrI));


                                if (activeNode->children[childIndex] == NULL){
                                    Node* nd = new Node(activeStrI, n-1, activeNode);
                                    nd->suffixIndex = i;
                                    activeNode->children[childIndex] = nd;
                                    break;
                                }else{
                                    activeNode = activeNode->children[childIndex] ;
                                    childI = activeNode->startIndex;
                                    lenEdge = activeNode->edgeLength();
                                    lenMatched = 0;
                                    continue;
                                }

                            }
                        }else{
                            Node* start = activeNode->parent ;
                            Node* end = activeNode;
                            Node* split = new Node(activeNode->startIndex, childI-1, start);
                            start->children[ arrIndex(str.at(activeNode->startIndex)) ] = split;

                            Node* splitEnd = new Node(activeStrI, n-1, split);
                            splitEnd->suffixIndex = i;
                            activeNode->startIndex = childI;
                            activeNode->parent = split;

                            split->children[arrIndex(str.at(childI)) ] = activeNode;
                            split->children[arrIndex(str.at(activeStrI)) ] = splitEnd;
                            break;
                        }
                    }


                }

            }


        }

	}

	~SuffixTree() {	}
};


int main(){

    string s;
    char base[1002];
    getline(cin, s); //>Rosalind ::: label
    //cout<<s;
    //cout<<s.length();
    int x = 0;
    for (size_t i = 0; i < s.length(); i++) {
        /* code */
        //cout<<s.at(i)<<endl;
        if(s.at(i)=='A' || s.at(i)=='T' || s.at(i)=='G' || s.at(i)=='C' || s.at(i)=='$' ){
            base[x++] = s.at(i);
        }

    }
    base[x] = '\0';
    //cout<<base;
    string Str = string(base);

	SuffixTree t(Str);
    //SuffixTree t(s);

	// cout<<"Postorder: "<<endl;
	// t.postorder(t.root);
	// cout<<"PostO done\n"<<endl;

	//cout<<"Preorder: "<<endl;
	t.preorder(t.root);
	//cout<<"PreO done\n"<<endl;

	return 0;
}

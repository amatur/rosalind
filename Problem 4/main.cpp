#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;


bool startsWith(string s, string startSubstr){
  string s1 = s.substr(0, 1);
  return ((s1.compare(startSubstr)) == 0);
}
//
// while (std::getline(infile, line))
// {
//     std::istringstream iss(line);
//     int a, b;
//     if (!(iss >> a >> b)) { break; } // error
//
//     // process pair (a,b)
// }


int main() {
    char bp[1002];
    string labels[1002];
    double gc[1002];
    int count = 0;
    int g, c, total;
    //read lines
    string line;
    while (getline(cin, line)){
        if (startsWith(line, ">")){
            labels[0] = line.substr(1, 13);
            while (getline(cin, line)){

                if (!startsWith(line, ">")){
                    for (int i = 0; i < line.length(); i++) {
                        if (line[i]=='A' || line[i]=='T' ) total++;
                        else if (line[i]=='C') {total++; c++;}
                        else if (line[i]=='G') {total++; g++;}
                    }
                }else{
                    //cout<<g<<" "<<c<<" "<<total<<endl;
                    gc[count] = (g+c)*100.0/total;
                    g = c = total = 0;
                    labels[++count] = line.substr(1, 13);
                }
            }
            gc[count] = (g+c)*100.0/total;
        }
    }

    int maxi = 0;
    double maxv = 0;
    for (size_t i = 0; i < count+1; i++) {
        //cout<<labels[i]<<" "<<gc[i]<<endl;
        if (gc[i] > maxv){
            maxi = i;
            maxv = gc[i];
        }
    }
    printf("%s\n%.10f", labels[maxi].c_str(), maxv);


    return 0;
}

/*
ID: wjl1241
PROG: beads
LANG: C++
*/

#include<fstream>
#include<string>
#include<vector>
using namespace std;

int main(){
    ifstream fin("beads.in");
    ofstream fout("beads.out");
    int nb,max=0;
    char left='w',last='w';
    string necklace;
    vector<char> color;
    vector<int> amt;
    fin>>nb>>necklace;
    necklace=necklace+necklace;

    color.push_back('w');
    amt.push_back(0);
    for(int i=0,tempnum=0;i<necklace.length();i++){
        if(necklace[i]==last)tempnum++;
        else if(last=='w'){
            if(left==necklace[i]){
                tempnum+=amt.back()+1;
                amt.pop_back();
                color.pop_back();
                last=necklace[i];
            }
            else {
                color.push_back(last);
                amt.push_back(tempnum);
                left=last;
                last=necklace[i];
                tempnum=1;
            }
        }
        else {
            color.push_back(last);
            amt.push_back(tempnum);
            left=last;
            last=necklace[i];
            tempnum=1;
        }
    }
    for(int i=1;i<color.size()-1;i++){
        int temp=0;
        if(color[i]!='w'){
            int j=i+1;
            for(;j<color.size();j++)if(color[j]!='w')break;
            temp=amt[i]+amt[j];
            if(i>0)if(color[i-1]=='w')temp+=amt[i-1];
            if(color[i+1]=='w')temp+=amt[i+1];
            if(j<color.size()-1)if(color[j+1]=='w')temp+=amt[j+1];
            if(temp>max)max=temp;
        }
    }
    if(max==0||max>nb)max=nb;
    fout<<max<<endl;
}
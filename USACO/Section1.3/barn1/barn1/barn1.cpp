/*
ID: wjl1241
PROG: barn1
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<list>
using namespace std;
const int maxstall=201;

int main(){
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");
    int stalls[maxstall]={0};
    int boardnum,stallnum,cownum;
    list<int> inter;
    fin>>boardnum>>stallnum>>cownum;
    for(int i=0;i<cownum;i++){
        int tmp;
        fin>>tmp;
        stalls[tmp]=1;
    }
    int cvdstl=0,j=0;
    while(stalls[j]==0)j++;
    int last=j;
    for(j++;j<=stallnum;j++){
        if(stalls[j]){
            cvdstl+=j-last;
            inter.push_back(j-last);
            last=j;
        }
    }

    if(boardnum>=cownum){
        fout<<cownum<<endl;
    }else {
        for(int i=0;i<boardnum-1;i++){
            list<int>::iterator itvptr=inter.begin();
            for(list<int>::iterator itr=inter.begin();itr!=inter.end();itr++){
                if(*itr>*itvptr){
                    itvptr=itr;
                }
            }
            cvdstl-=*itvptr;
            inter.erase(itvptr);
        }
        fout<<cvdstl+boardnum<<endl;
    }

    return 0;
}
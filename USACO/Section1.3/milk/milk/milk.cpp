/*
ID: wjl1241
PROG: milk
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<list>
#include<utility>
using namespace std;

int main(){
    int totalamt,fmnum,totalsum=0;
    list<pair<int,int> > farmers;
    list<pair<int,int> >::iterator fmitr;
    ifstream fin("milk.in");
    ofstream fout("milk.out");

    fin>>totalamt>>fmnum;
    for(int i=0;i<fmnum;i++){
        int price,limit;
        fin>>price>>limit;
        farmers.push_back(pair<int,int>(price,limit));
    }
    while(totalamt>0){
        int minprice=2147483647;
        for(list<pair<int,int> >::iterator tmpitr=farmers.begin();tmpitr!=farmers.end();tmpitr++){
            if(tmpitr->first<minprice){
                minprice=tmpitr->first;
                fmitr=tmpitr;
            }
        }
        if(totalamt>=fmitr->second){
            totalsum+=(fmitr->first)*(fmitr->second);
            totalamt-=fmitr->second;
        }
        else {
            totalsum+=(fmitr->first)*totalamt;
            totalamt-=totalamt;
        }
        farmers.erase(fmitr);
    }
    fout<<totalsum<<endl;

    return 0;
}
/*
ID: wjl1241
PROG: hamming
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

vector<int> hamnum;

int dist(const int a, const int b){
    //return the hamming distance between a and b
    // 0 <= a,b < 256
    int dd=a^b;

    dd=(dd&0x00000055) + ((dd>>1)&0x00000055);
    dd=(dd&0x00000033) + ((dd>>2)&0x00000033);
    dd=(dd&0x0000000F) + ((dd>>4)&0x0000000F);

    return dd;
}

bool IsSuit(const int distance, const int num){
    for(vector<int>::iterator itr=hamnum.begin();itr!=hamnum.end();++itr){
        if(dist(num,*itr)<distance)return false;
    }
    return true;
}

int main(){
    ifstream fin("hamming.in");
    ofstream fout("hamming.out");

    int n,b,d,num=0;
    fin>>n>>b>>d;
    while(hamnum.size()<n){
        if(IsSuit(d,num)){
            hamnum.push_back(num);
        }
        ++num;
    }

    for(int i=0;i<n;){
        if(i%10 == 0)fout<<hamnum[i];
        else fout<<' '<<hamnum[i];
        ++i;
        if(i%10 == 0)fout<<'\n';
    }
    if(n%10!=0)fout<<endl;

    return 0;
}
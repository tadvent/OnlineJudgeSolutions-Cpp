/*
ID: wjl1241
PROG: checker
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

ifstream fin("checker.in");
ofstream fout("checker.out");
int arrange[15];
int n,ans,partans[15],nowrow;
bool xx1[26],xx2[26],col[15];

//bool check(int row,int pos){
//    for(int i=0;i<row;++i){
//        if(arrange[i]==pos)return false;
//        if(row-i==pos-arrange[i])return false;
//        if(row-i==arrange[i]-pos)return false;
//    }
//    return true;
//}

void put(int row){
    for(int i=0;i<n;++i){
        if(col[i] || xx1[row+n-1-i] || xx2[row+i])continue;
        arrange[row]=i;
        col[i]=xx1[row+n-1-i]=xx2[row+i]=true;
        if(row==n-1){   //one answer
            if(ans<3){  //output solution
                fout<<arrange[0]+1;
                for(int j=1;j<n;++j)
                    fout<<' '<<arrange[j]+1;
                fout<<endl;
            }
            ++ans;
            ++partans[nowrow];
        }
        else {  //arrange next row
            put(row+1);
        }
        col[i]=xx1[row+n-1-i]=xx2[row+i]=false;
    }
}

int main(){
    fin>>n;

    ans=0;
    for(int i=0;i<26;++i)xx1[i]=xx2[i]=false;
    for(int i=0;i<15;++i)col[i]=false;

    for(nowrow=0;nowrow<=(n+1)/2 || ans<3 ;++nowrow){
        partans[nowrow]=0;
        arrange[0]=nowrow;
        xx1[n-1-nowrow]=true;
        xx2[nowrow]=true;
        col[nowrow]=true;
        put(1);
        xx1[n-1-nowrow]=false;
        xx2[nowrow]=false;
        col[nowrow]=false;
    }
    //put(0);

    ans=0;
    for(int i=0;i<n/2;++i)ans+=partans[i];
    ans*=2;
    if(n%2)ans+=partans[n/2];
    fout<<ans<<endl;
    return 0;
}
/*
ID: wjl1241
PROG: inflate
LANG: C++
*/

#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

//struct prob{
//    int minute;
//    int score;
//};

vector<int> minu;
vector<int> sco;
vector<int> totalsave;

int main(){
    ifstream fin("inflate.in");
    ofstream fout("inflate.out");
    int m,n;
    fin>>m>>n;
    minu.resize(n);
    sco.resize(n);
    totalsave.resize(m+1,0);
    for(int i=0;i<n;++i){
        fin>>sco[i]>>minu[i];
    }

    totalsave[0]=0;
    for(int i=0;i<n;++i){
        //int tmpminu=minu[i];
        for(int minute=minu[i];minute<=m;++minute){
            totalsave[minute]=max(totalsave[minute],totalsave[minute-minu[i]]+sco[i]);
        }
    }
    //for(int minute=0;minute<m;++minute){
    //    for(int i=0;i<n;++i){
    //        int tmpm;
    //        if((tmpm=minute+minu[i])<=m){
    //            totalsave[tmpm]=max(totalsave[minute]+sco[i],totalsave[tmpm]);
    //        }
    //    }
    //}
    fout<<totalsave[m]<<endl;
    return 0;
}

//====================================================================================

//#include <fstream>
//using namespace std;
//
//ifstream fin("inflate.in");
//ofstream fout("inflate.out");
//
//const short maxm = 10010;
//long best[maxm], m, n;
//
//int main()
//{
//    short i, j, len, pts;
//
//    fin >> m >> n;
//
//    for (j = 0; j <= m; j++)
//        best[j] = 0;
//
//    for (i = 0; i < n; i++) {
//        fin >> pts >> len;
//        for (j = len; j <= m; j++)
//            if (best[j-len] + pts > best[j])
//                best[j] = best[j-len] + pts;
//    }
//    fout << best[m] << endl;
//
//    return 0;
//}

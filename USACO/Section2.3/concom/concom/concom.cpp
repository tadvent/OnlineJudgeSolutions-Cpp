/*
ID: wjl1241
PROG: concom
LANG: C++
*/

bool control[101][101];
int own[101][101];

#include<fstream>
using namespace std;

bool IsControl(int h, int s){
    int con=0;
    for(int i=1;i<101;++i)if(control[h][i])con+=own[i][s];
    if(con>50)return true;
    return false;
}

bool fillcontrol(int h, int s){
    if(h==s)return false;
    if(control[h][s])return false;
    if(IsControl(h,s)){
        control[h][s]=true;
        return true;
    }
    return false;
}

int main(){
    ifstream fin("concom.in");
    ofstream fout("concom.out");

    int n;
    fin>>n;
    for(int i=0;i<101;++i)for(int j=0;j<101;++j)control[i][j]=false;
    for(int i=0;i<n;++i){
        int h,s;
        fin>>h>>s;
        fin>>own[h][s];
        if(own[h][s]>50)control[h][s]=true;
    }
    for(int i=1;i<101;++i)control[i][i]=true;

    bool update=true;
    while(update){
        update=false;
        for(int i=1;i<101;++i)for(int j=1;j<101;++j)
            if(fillcontrol(i,j))update=true;
    }

    for(int i=1;i<101;++i)for(int j=1;j<101;++j){
        if(i==j)continue;
        if(control[i][j]){
            fout<<i<<' '<<j<<'\n';
        }
    }

    return 0;
}

//the results are not well stored to save time in the previous method, although it can pass all the tests.
//the method below is to make full use of own[101][101] array but there is a bug that i can't find....

//bool control[101][101];
//int own[101][101];
//
//#include<fstream>
//using namespace std;
//
//void addcon(int h, int s){
//    if(control[h][s])return;
//
//    control[h][s]=true;
//    for(int i=1;i<101;++i){
//        if(i==h || i==s)continue;
//        own[h][i]+=own[s][i];
//    }
//    for(int i=1;i<101;++i)if(control[i][h])addcon(i,s);
//    for(int i=1;i<101;++i){
//        if(h == i)continue;
//        if(own[h][i]>50 && !control[h][i])addcon(h,i);
//    }
//}
//
//int main(){
//    ifstream fin("concom.in");
//    ofstream fout("concom.out");
//
//    int n;
//    fin>>n;
//    for(int i=0;i<101;++i)for(int j=0;j<101;++j){
//        control[i][j]=false;
//        own[i][j]=0;
//    }
//    for(int i=0;i<n;++i){
//        int h,s;
//        fin>>h>>s;
//        fin>>own[h][s];
//    }
//    for(int i=1;i<101;++i)control[i][i]=true;
//
//    for(int i=1;i<101;++i)for(int j=1;j<101;++j){
//        if(i == j)continue;
//        if(own[i][j]>50 && !control[i][j])addcon(i,j);
//    }
//
//    for(int i=1;i<101;++i)for(int j=1;j<101;++j){
//        if(i==j)continue;
//        if(control[i][j]){
//            fout<<i<<' '<<j<<'\n';
//        }
//    }
//
//    return 0;
//}
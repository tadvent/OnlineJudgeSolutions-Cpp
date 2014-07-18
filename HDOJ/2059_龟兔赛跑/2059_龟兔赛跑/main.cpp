#include<iostream>
#include<algorithm>
using namespace std;
const int NMax = 110;

int Len, N, C, T;
int VR, VTauto, VTpedal;
int Pos[NMax] = {0};
double TT[NMax] = {0.0};

bool IsRabbitWin(){
    double TR = (double)(Len) / VR;
    Pos[N+1] = Len;
    for(int n = 1; n <= N+1; ++n){
        if(Pos[n] <= C)TT[n] = (double)(Pos[n]) / VTauto;
        else TT[n] = (double)(C) / VTauto + (double)(Pos[n] - C) / VTpedal;
        for(int i = 1; i < n; ++i){
            double t = TT[i] + T;
            if(Pos[n] - Pos[i] <= C)
                t += (double)(Pos[n] - Pos[i]) / VTauto;
            else
                t += (double)(C) / VTauto + (double)(Pos[n] - Pos[i] - C) / VTpedal;
            if(t < TT[n])TT[n] = t;
        }
        if(TT[n] > TR)return true;
    }
    return false;
}

int main(){
    //freopen("i.txt", "r", stdin);
    //freopen("o.txt", "w", stdout);
    while(cin>>Len>>N>>C>>T>>VR>>VTauto>>VTpedal){
        for(int i=1; i<=N; ++i)cin>>Pos[i];
        if(!cin)break;
        rotate();
        cout<< (IsRabbitWin()? "Good job,rabbit!\n":"What a pity rabbit!\n");
    }
}

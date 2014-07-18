#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

int w, h, a, b, s, t, p, q;

int main(){
#ifdef LOCAL
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    cin >> w >> h >> a >> b >> s >> t >> p >> q;
    int tw = 10*a + 3*b;
    int th = 3*a + 2*b;
    long long ans = (long long)(w - tw + 1) * (h - th + 1);
    
    int L = max(0, s-tw+1);
    int R = min(w-tw, s-1);
    int T = max(0, t-th+1);
    int B = min(h-th, t);

    for(int bx = L; bx <= R; ++bx)for(int by = T; by <= B; ++by){
        int rx = s - bx;
        int ry = t - by;
        //cout << rx << ',' << ry << '\n';
        if(rx < a) --ans;
        else if(rx < a+b){
            if(ry < b-a){
                if(!(
                    6*a+2*b-rx >= p && b-a-ry >= q ||
                    3*a+b-rx >= p && b+a-ry >= q
                    )) --ans;
            } else if(ry < b){
                if(3*a+b-rx < p || b-ry < q) --ans;
            } else if(ry < b+a){
                if(6*a+2*b-rx < p || b+a-ry < q) --ans;
            } else if(ry < b+2*a){
                --ans;
            } else if(ry < 2*b+2*a){
                if(a+b-rx < p || 2*b+2*a-ry < q) --ans;
            } else if(ry < 2*b+3*a){
                --ans;
            }
        } else if(rx < 2*a+b){
            if(ry < b-a){
                if(!(
                    6*a+2*b-rx >= p && b-a-ry >= q ||
                    3*a+b-rx >= p && b+a-ry >= q
                    )) --ans;
            } else if(ry < b){
                if(3*a+b-rx < p || b-ry < q) --ans;
            } else if(ry < b+a){
                if(6*a+2*b-rx < p || b+a-ry < q) --ans;
            } else if(ry < 2*b+3*a){
                --ans;
            }
        } else if(rx < 3*a+b){
            if(ry < b-a){
                if(!(
                    6*a+2*b-rx >= p && b-a-ry >= q ||
                    3*a+b-rx >= p && 2*b+3*a-ry >= q
                    )) --ans;
            } else if(ry < b){
                if(3*a+b-rx < p || 2*b+3*a-ry < q) --ans;
            } else if(ry < b+a){
                if(!(
                    6*a+2*b-rx >= p && b+a-ry >= q ||
                    3*a+b-rx >= p && 2*b+3*a-ry >= q
                    )) --ans;
            } else if(ry < 2*b+3*a){
                if(3*a+b-rx < p || 2*b+3*a-ry < q) --ans;
            }
        } else if(rx < 
    }
}

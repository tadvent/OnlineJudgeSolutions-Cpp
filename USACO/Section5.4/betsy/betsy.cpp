/*
ID: wjl1241
LANG: C++
TASK: betsy
*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

unsigned char mat[10][10];  // 0x udlr cunt; 0x00 visited or wall
int N, N2, visit;

void init(){
    memset(mat, 0, sizeof(mat));
    for(int i=2; i<=N-1; ++i){
        mat[1][i] = 0x73;
        mat[N][i] = 0xb3;
        mat[i][1] = 0xd3;
        mat[i][N] = 0xe3;
    }
    mat[1][1] = 0x52;
    mat[1][N] = 0x62;
    mat[N][1] = 0x92;
    mat[N][N] = 0xa2;
    for(int i=2; i<=N-1; ++i)for(int j=2; j<=N-1; ++j)
        mat[i][j] = 0xf4;
    N2 = N*N;
    visit = 0;
}

int count(const int x, const int y){
    unsigned char ost = mat[x][y];
    unsigned char ust, dst, lst, rst, todo = 0xf;
    mat[x][y] = 0x00;
    ++visit;

    int ret = 0;

    if(ost == 0x00 || (x == N && y == 1)){
        if(x == N && y == 1 && visit == N2) ret = 1;
        todo = 0;
    } else if(ost == 0x32 || ost == 0xc2) {
	todo = 0;
    } else if(x == N-1 && y == 2 && ((ost & 0x60) == 0x60)) {
	todo = 0;
    } else if(
                (mat[x-1][y] & 0x0f) == 1 ||
                (mat[x+1][y] & 0x0f) == 1 ||
                (mat[x][y-1] & 0x0f) == 1 ||
                (mat[x][y+1] & 0x0f) == 1
	    ) {
        if((ost & 0x0f) == 1) {
	    if((mat[x-1][y] & 0x0f) == 1) {
		ust = mat[x-1][y];
		mat[x-1][y] = 0x00;
		ret = count(x-1, y);
		mat[x-1][y] = ust;
	    } else if((mat[x+1][y] & 0x0f) == 1) {
		dst = mat[x+1][y];
		mat[x+1][y] = 0x00;
		ret = count(x+1, y);
		mat[x+1][y] = dst;
	    } else if((mat[x][y-1] & 0x0f) == 1) {
		lst = mat[x][y-1];
		mat[x][y-1] = 0x00;
		ret = count(x, y-1);
		mat[x][y-1] = lst;
	    } else if((mat[x][y+1] & 0x0f) == 1) {
		rst = mat[x][y+1];
		mat[x][y+1] = 0x00;
		ret = count(x, y+1);
		mat[x][y+1] = rst;
	    }
	}
	todo = 0;
    } else if(
            (((x-1 != N || y != 1) && (mat[x-1][y] & 0x0f) == 2)? (todo = 8, 1): 0) +
            (((x+1 != N || y != 1) && (mat[x+1][y] & 0x0f) == 2)? (todo = 4, 1): 0) +
            (((x != N || y-1 != 1) && (mat[x][y-1] & 0x0f) == 2)? (todo = 2, 1): 0) +
            (((x != N || y+1 != 1) && (mat[x][y+1] & 0x0f) == 2)? (todo = 1, 1): 0) > 1
        ) {
	todo = 0;
    }

    if(todo) { // have to go forward
        ust = mat[x-1][y];
        dst = mat[x+1][y];
        lst = mat[x][y-1];
        rst = mat[x][y+1];
        if(ust) {
            mat[x-1][y] &= 0xbf;
            mat[x-1][y]--;
        }
        if(dst) {
            mat[x+1][y] &= 0x7f;
            mat[x+1][y]--;
        }
        if(lst) {
            mat[x][y-1] &= 0xef;
            mat[x][y-1]--;
        }
        if(rst) {
            mat[x][y+1] &= 0xdf;
            mat[x][y+1]--;
        }

        if((todo & 8) && ust) ret += count(x-1, y);
        if((todo & 4) && dst) ret += count(x+1, y);
        if((todo & 2) && lst) ret += count(x, y-1);
        if((todo & 1) && rst) ret += count(x, y+1);

        mat[x-1][y] = ust;
        mat[x+1][y] = dst;
        mat[x][y-1] = lst;
        mat[x][y+1] = rst;
    }

    --visit;
    mat[x][y] = ost;
    return ret;
}

int main(){
    freopen("betsy.in", "r", stdin);
    freopen("betsy.out", "w", stdout);
    cin >> N;
    init();
    cout << count(1, 1) << endl;
}


/*
ID: wjl1241
LANG: C++
TASK: latin
*/

/*
// only dps... slow
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MaxSq = 7;
int num[MaxSq][MaxSq], N, cnt;
bool used[MaxSq][MaxSq+1] = {0};  // in col i, has num j been used?

//int layercnt[MaxSq] = {1};
vector<pair<int,int> > layercnt;

void init(){
    FILE *fin = fopen("latin.in", "r");
    fscanf(fin, "%d", &N);
    fclose(fin);
    for(int i=0; i<N; ++i)for(int j=0; j<N; ++j)
        num[i][j] = j+1;
    for(int i=0; i<N; ++i)
        used[i][i+1] = true;
    cnt = 0;
}

void dfs(int row, int col){
    // row, col : 0 ~ N-1
    if(col == N){
        //++layercnt[row];
        if(row == 1){
            layercnt.push_back(pair<int,int>(0,0));
        } else if(row == 2){
            ++layercnt.back().first;
        }
        dfs(row + 1, 0);
    }
    else if(row == N-1){
        ++layercnt.back().second;
        ++cnt;
        return;
    }
    for(int i=col; i<N; ++i)if(!used[col][num[row][i]]){
        used[col][num[row][i]] = true;
        swap(num[row][col], num[row][i]);
        dfs(row, col+1);
        swap(num[row][col], num[row][i]);
        used[col][num[row][i]] = false;
    }
}

void output(){
    FILE *fout = fopen("latin.out", "w");
    fprintf(fout, "%d\n", cnt);
    fclose(fout);
}

int main(){
    init();
    dfs(1, 0);
    output();
}
*/


/*
// incorrect algorithm, wrong answer = =
#include<cstring>
#include<fstream>
#include<algorithm>
using namespace std;

int n;
long long wrp[8] = {1};  // wrong permutation
long long jch[8] = {1, 1};  // n!
int mat[8][8];
bool rowused[8][8];
bool colused[8][8];

void init(){
    memset(rowused, 0, sizeof(rowused));
    memset(colused, 0, sizeof(colused));
    for(int i=1; i<=n; ++i){
        mat[1][i] = mat[i][1] = i;
        rowused[1][i] = colused[1][i] = rowused[i][i] = colused[i][i] = true;
    }
}

long long cnt1 = 0, cnt2 = 0;

void dfs1(int row, int col){
    if(col > n)++cnt1;
    else if(row > n)dfs1(3, col+1);
    else {
        for(int num=1; num<=n; ++num)if(!rowused[row][num] && !colused[col][num]){
            rowused[row][num] = colused[col][num] = true;
            dfs1(row+1, col);
            rowused[row][num] = colused[col][num] = false;
        }
    }
}
void dfs2(int row, int col){
    if(col > n)++cnt2;
    else if(row > n)dfs2(2, col+1);
    else if(row == 2 && col == 3){
        dfs2(3, 3);
    } else {
        for(int num=1; num<=n; ++num)if(!rowused[row][num] && !colused[col][num]){
            rowused[row][num] = colused[col][num] = true;
            dfs2(row+1, col);
            rowused[row][num] = colused[col][num] = false;
        }
    }
}

long long calc(){
    init();
    mat[2][2] = 1;
    rowused[2][1] = colused[2][1] = true;
    for(int i=3; i<n; ++i){
        mat[2][i] = i+1;
        rowused[2][i+1] = colused[i][i+1] = true;
    }
    if(n >= 3){
        mat[2][n] = 3;
        rowused[2][3] = colused[n][3] = true;
    }
    dfs1(3, 2);

    init();
    //mat[2][2] = n;
    //rowused[2][n] = colused[2][n] = true;
    if(n >= 3){
        mat[2][3] = 1;
        rowused[2][1] = colused[3][1] = true;
    }
    //for(int i=4; i<=n; ++i){
    //    mat[2][i] = i-1;
    //    rowused[2][i-1] = colused[i][i-1] = true;
    //}
    dfs2(2, 2);

    return jch[n-1] * (cnt1*wrp[n-2] + cnt2*(n-2));
}

int main(){
    ifstream fin("latin.in");
    ofstream fout("latin.out");
    for(int i=2; i<8; ++i){
        wrp[i] = (i-1) * (wrp[i-1] + wrp[i-2]);
        jch[i] = i * jch[i-1];
    }
    fin >> n;
    fin.close();
    fout << calc() <<endl;
    fout.close();
}

*/

/* right answer, but not fast enough ....
#include<fstream>
#include<algorithm>
using namespace std;

int N;
bool rowUsed[8][8] = {0};   // rowUsed[i][j] : in row i, has the number j been used ?
bool colUsed[8][8] = {0};   // just as above
long long cnt = 0;

void dfs(int row, int col){
    for(int i=1; i<=N; ++i)if(!rowUsed[row][i] && !colUsed[col][i]){
        if(col == N){
            if(row == N-1){
                ++cnt;
            } else {
                rowUsed[row][i] = colUsed[col][i] = true;
                dfs(row+1, 2);
                rowUsed[row][i] = colUsed[col][i] = false;
            }
        } else {
            rowUsed[row][i] = colUsed[col][i] = true;
            dfs(row, col+1);
            rowUsed[row][i] = colUsed[col][i] = false;
        }
    }
}

long long calc(){
    if(N == 2)      return 1;
    else if(N == 3) return 2;

    // fill first row and col
    for(int i = 1; i <= N; ++i){
        rowUsed[1][i] = rowUsed[i][i] = true;
        colUsed[1][i] = colUsed[i][i] = true;
    }

    // fill (2,2) with 3
    rowUsed[2][3] = colUsed[2][3] = true;

    dfs(2, 3);
    cnt *= N-2;

    // change (2,2) to 1
    rowUsed[2][3] = colUsed[2][3] = false;
    rowUsed[2][1] = colUsed[2][1] = true;
    dfs(2, 3);

    // cnt = cnt * (N-1)!
    for(int i = 2; i < N; ++i)
        cnt *= i;
    return cnt;
}

int main(){
    ifstream fin("latin.in");
    ofstream fout("latin.out");
    fin >> N;
    fout << calc() << endl;
    fin.close();
    fout.close();
}
*/

/*
// still slow ... = =
#include<fstream>
#include<algorithm>
using namespace std;

int N;
int mat[8][8];
bool colUsed[8][8] = {0};   // colUsed[i][j] : in col i, has the number j been used ?
long long cnt = 0;

void dfs(int row, int col){
    for(int i = col; i <= N; ++i)if(!colUsed[col][mat[row][i]]){
        if(col == N){
            if(row == N-1) ++cnt;
            else {
                colUsed[col][mat[row][N]] = true;
                dfs(row+1, 2);
                colUsed[col][mat[row][N]] = false;
            }
        } else {
            colUsed[col][mat[row][i]] = true;
            swap(mat[row][col], mat[row][i]);
            dfs(row, col+1);
            swap(mat[row][col], mat[row][i]);
            colUsed[col][mat[row][i]] = false;
        }
    }
}

long long calc(){
    if(N == 2) return 1;
    if(N == 3) return 2;

    // init matrix
    for(int row = 1; row <= N; ++row)
        for(int col = 1; col <= N; ++col)
            mat[row][col] = col;

    // fill first row and col
    for(int i = 1; i <= N; ++i){
        colUsed[1][i] = colUsed[i][i] = true;
        swap(mat[i][1], mat[i][i]);
    }

    // fill (2,2) with 3 and count
    swap(mat[2][2], mat[2][3]);
    colUsed[2][3] = true;
    dfs(2, 3);
    colUsed[2][3] = false;

    cnt *= N-2;

    // change (2,2) to 1 and count
    swap(mat[2][2], mat[2][3]);
    colUsed[2][1] = true;
    dfs(2, 3);
    colUsed[2][1] = false;

    // cnt = cnt * (N-1)!
    for(int i = 2; i < N; ++i)
        cnt *= i;
    return cnt;
}

int main(){
    ifstream fin("latin.in");
    ofstream fout("latin.out");
    fin >> N;
    fout << calc() << endl;
    fin.close();
    fout.close();
}
*/

/*
// standard program
#include <fstream>
using namespace std;

int     N;
bool    row_used[7][7];
bool    col_used[7][7];
int     factorial[7];

int 
searchR (int r, int c)
{
    if (c == N) {
        return searchR (r + 1, 1);
    }
    if (r == N - 1) {
        return 1;
    }

    int     i, t = 0, sum = 0;
    int     s[2] = {-1, -1};

    for (i = 0; i < N; i++) {
        if (row_used[r][i] || col_used[c][i])
            continue;
        if (i > c)
            t = 1;
        if (r == 1 && s[t] != -1) {
            sum += s[t];
        }
        else {
            row_used[r][i] = true;
            col_used[c][i] = true;
            s[t] = searchR (r, c + 1);
            sum += s[t];
            row_used[r][i] = false;
            col_used[c][i] = false;
        }
    }
    return sum;
}

void 
main ()
{
    double  nLatin;
    int     i;

    ifstream fin ("latin.in");
    fin >> N;
    fin.close ();

    factorial[0] = 1;
    for (i = 0; i < N; i++) {
        col_used[i][i] = true;
        row_used[i][i] = true;
        if (i > 0)
            factorial[i] = i * factorial[i - 1];
    }

    nLatin = (double) factorial[N - 1] * (double) searchR (1, 1);

    ofstream fout ("latin.out");
    fout.precision (0);
    fout.setf (ios::fixed);
    fout << nLatin << '\n';
    fout.close ();
}
*/


#include<fstream>
#include<algorithm>
using namespace std;

int N;
int mat[8][8];
bool colUsed[8][8] = {0};   // colUsed[i][j] : in col i, has the number j been used ?

int dfs(int row, int col){
    if(col == N + 1) return dfs(row+1, 2);
    if(row == N) return 1;

    int sum = 0;
    int cnt = -1;

    for(int c = col; c <= N; ++c)if(!colUsed[col][mat[row][c]]){
        colUsed[col][mat[row][c]] = true;
        swap(mat[row][col], mat[row][c]);
        if(row == 2){
            if(mat[row][col] > col){
                if(cnt >= 0) sum += cnt;
                else sum += (cnt = dfs(row, col+1));
            } else {
                sum += dfs(row, col+1);
            }
        } else {
            sum += dfs(row, col+1);
        }
        swap(mat[row][col], mat[row][c]);
        colUsed[col][mat[row][c]] = false;
    }
    return sum;
}

long long calc(){
    if(N == 2) return 1;
    if(N == 3) return 2;

    // init matrix
    for(int row = 1; row <= N; ++row)
        for(int col = 1; col <= N; ++col)
            mat[row][col] = col;

    // fill first row and col
    for(int i = 1; i <= N; ++i){
        colUsed[1][i] = colUsed[i][i] = true;
        swap(mat[i][1], mat[i][i]);
    }

    long long cnt = 1;
    // cnt = cnt * (N-1)!
    for(int i = 2; i < N; ++i)
        cnt *= i;
    return cnt * dfs(2, 2);
}

int main(){
    ifstream fin("latin.in");
    ofstream fout("latin.out");
    fin >> N;
    fout << calc() << endl;
    fin.close();
    fout.close();
}

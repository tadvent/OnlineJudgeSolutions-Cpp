#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int> > matrix;

int main(){
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int n;
    cin>>n;
    matrix.resize(n+1, vector<int>(n+1, 0));
    for(int i=1; i<=n; ++i)for(int j=1; j<=n; ++j)
        cin>>matrix[i][j];
    for(int i=1; i<=n; ++i)for(int j=1; j<=n; ++j)
        matrix[i][j] += matrix[i-1][j] + matrix[i][j-1] - matrix[i-1][j-1];

    int maxsum = 0;
    for(int x1=0; x1<n; ++x1)for(int y1=0; y1<n; ++y1)
        for(int x2=x1+1; x2<=n; ++x2)for(int y2=y1+1; y2<=n; ++y2){
            int sum = matrix[x2][y2] - matrix[x2][y1] - matrix[x1][y2] + matrix[x1][y1];
            maxsum = max(maxsum, sum);
        }

    cout<<maxsum<<endl;
}

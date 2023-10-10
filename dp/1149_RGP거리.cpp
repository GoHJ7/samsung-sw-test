#include <iostream>
#include <algorithm>

using namespace std;

#define R 0
#define G 1
#define B 2

const int MAX = 1001;
int paintPrice[3][MAX];
int dp[3][MAX];

int main(){
    int n;
    cin>>n;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j<3; j++){
            cin>>paintPrice[j][i];
        }
    }

    dp[R][1] = paintPrice[R][1];
    dp[G][1] = paintPrice[G][1];
    dp[B][1] = paintPrice[B][1];

    for(int i =2 ; i<=n; i++){
        dp[R][i] = min(dp[B][i-1] + paintPrice[R][i],dp[G][i-1] + paintPrice[R][i]);
        dp[G][i] = min(dp[B][i-1] + paintPrice[G][i],dp[R][i-1] + paintPrice[G][i]); 
        dp[B][i] = min(dp[R][i-1] + paintPrice[B][i],dp[G][i-1] + paintPrice[B][i]);
    }

    cout<<min(dp[R][n],min(dp[G][n],dp[B][n]));
    return 0;
}
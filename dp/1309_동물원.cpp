#include <iostream>
#include <algorithm>

#define NN 0
#define NL 1
#define LN 2



using namespace std;
const int MAX = 100000;
long long dp[3][MAX];

int main(){
    int n;
    cin>>n;

    dp[NN][0] = 1;
    dp[NL][0] = 1;
    dp[LN][0] = 1;

    for(int i = 1; i<n ; i++){
        dp[NN][i] = dp[NN][i-1] + dp[NL][i-1] + dp[LN][i-1];
        dp[NL][i] = dp[NN][i-1] + dp[LN][i-1];
        dp[LN][i] = dp[NN][i-1] + dp[NL][i-1];
        dp[NN][i] %= 9901;
        dp[NL][i] %= 9901;
        dp[LN][i] %= 9901;
    }

    cout<<(dp[NN][n-1] + dp[NL][n-1] + dp[LN][n-1])%9901;
    return 0;
}
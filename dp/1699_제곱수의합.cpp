#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin>>n;

    int dp[n+1];
    for(int i = 0; i <=n; i++ ) dp[i] = 100001;

    for(int i = 1; i <= n ; i++){
        if(i*i > n) break;
        dp[i*i] = 1;
    }

    for(int i = 1 ; i<= n ; i++){
        for(int j = 1; j <=n ; j++){
            if(i - j*j < 1) break;
            dp[i] = min(dp[i-j*j] +  1, dp[i]);
        }
    }
    cout<<dp[n];
    return 0;
}
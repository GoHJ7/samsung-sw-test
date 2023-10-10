#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 301;
int dp[3][MAX];
int stair[MAX]; 

int main(){
    int s;
    cin>>s;
    for(int i = 1; i <=s ; i++){
        cin>>stair[i];
    }
    dp[1][1] = stair[1];
    dp[1][2] = stair[2];
    dp[2][2] = stair[1] + stair[2];

    for(int i = 3; i<=s; i++){
        dp[1][i] = stair[i];
        dp[2][i] = stair[i];

        if(i - 1>0) dp[2][i] += dp[1][i-1];
        if(i - 2>0) dp[1][i] = max(dp[1][i-2] + stair[i], dp[1][i]);
        if(i - 2>0) dp[1][i] = max(dp[2][i-2] + stair[i], dp[1][i]);
    }
    cout<<max(dp[1][s] , dp[2][s]);
}
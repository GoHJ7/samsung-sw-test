#include <iostream>

using namespace std;

int n,k;

long long divisor = 1000000000;
const int MAX = 201;

//num,n
long long dp[MAX][MAX];

int main(){
    cin>>n>>k;

    for(int i = 0; i<=n ; i++){
        dp[1][i] = 1;
    }

    for(int i = 2; i <=k ;i++){
        for(int j = 0 ; j <=n; j++){
            //i는 개수 j는 합
            for(int z = 0; z <=j ; z++){
                if(j-z >= 0){
                    dp[i][j] += dp[i-1][j-z];
                    dp[i][j] %= divisor;
                }
            }
        }
    }
    cout<< dp[k][n];
    return 0;
}
#include <iostream>

using namespace std;

int fib(int nth){
    if(nth == 0 ) return 0;
    else if(nth == 1) return 1;
    else return fib(nth -1) + fib(nth -2);

}
int dp[46];

int main(){
    int f;
    cin>>f;
    //cout<<fib(f);
    //재귀 사용시 시간 초과
    //점화식으로 풀것
    dp[0] = 0;
    dp[1] = 1;
    for(int i = 2 ; i<=f; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    cout<<dp[f];
}
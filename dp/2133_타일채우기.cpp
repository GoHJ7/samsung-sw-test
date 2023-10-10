#include <iostream>
#include <algorithm>

#define VVV 0
#define VVO 1
#define VOV 2
#define VOO 3
#define OVV 4
#define OVO 5
#define OOV 6
#define OOO 7

using namespace std;
int dp[8][30];

int main(){
    int n;
    cin>>n;
    
    dp[VOO][0] = 1;
    dp[OOV][0] = 1;
    dp[VVV][0] = 1;
    for(int i= 1; i<n;i++){
        //그 전의 있는 걸로 경우의 수 생각
        dp[OOO][i] += dp[VVV][i-1] ;
        
        dp[OOV][i] += dp[VVO][i-1] ;
        
        dp[OVO][i] += dp[VOV][i-1] ;
        
        dp[OVV][i] += dp[VOO][i-1] ;
        dp[OOO][i] += dp[VOO][i-1] ;
        
        dp[VOO][i] += dp[OVV][i-1] ;

        dp[VOV][i] += dp[OVO][i-1] ;

        dp[VVO][i] += dp[OOV][i-1] ;
        dp[OOO][i] += dp[OOV][i-1] ;

        dp[VVV][i] += dp[OOO][i-1] ;
        dp[OOV][i] += dp[OOO][i-1] ;
        dp[VOO][i] += dp[OOO][i-1] ;
    }
    
    cout<<dp[OOO][n-1];
    return 0;
}
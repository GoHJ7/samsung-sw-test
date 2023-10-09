#include <iostream>
#include <algorithm>

using namespace std;

int N,M;

int maze[1000][1000];
int dp[1000][1000];
bool isInRange(int x,int y){
    if(x >= 0 && y>= 0
    && x<N && y<M) return true;
    else return false;
}
int main(){
    cin>>N>>M;

    for(int i = 0; i<N;i++){
        for(int j = 0; j<M ; j++){
            cin>>maze[i][j];
        }
    }
    

    for(int i = 0; i<N;i++){
        for(int j = 0; j<M ; j++){
            dp[i][j] = maze[i][j];
            int temp = dp[i][j];
            if(isInRange(i-1,j)) dp[i][j] = max(dp[i][j],temp + dp[i-1][j]);
            if(isInRange(i,j-1)) dp[i][j] = max(dp[i][j],temp + dp[i][j-1]);
            if(isInRange(i-1,j-1)) dp[i][j] = max(dp[i][j],temp + dp[i-1][j-1]);
        }
    }

    
    cout<<dp[N-1][M-1];
}
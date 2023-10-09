#include <iostream>

using namespace std;
const int MAX = 100;
int map[MAX][MAX];
long long dp[MAX][MAX];
int N;

bool isInRange(int x, int y){
    if(x >= 0 && y>=0 && x<N && y< N) return true;
    else return false;
}
int main(){

    cin >> N;

    for(int i= 0 ; i <N;i++)
        for(int  j = 0 ; j < N ; j++)
            cin >> map[i][j];

    dp[0][0] = 1;

    for(int i= 0 ; i <N;i++){
        for(int  j = 0 ; j < N ; j++){
            for(int k = 1 ; k <= 9 ; k++){
                if(isInRange(i - k ,j) && map[i-k][j] == k){
                    dp[i][j] +=dp[i-k][j];
                }
                if(isInRange(i , j -k)&& map[i][j-k] == k){
                    dp[i][j] +=dp[i][j-k];
                }
            }
        }
    }
    cout<< dp[N-1][N-1];
    
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    vector<int> v;
    int dp[k + 1];
    for(int i = 0; i <= k ; i++)
        dp[i] = 10001;
    
    for(int i =0 ; i < n ; i++){
        int temp;
        cin>>temp;
        if(temp > k) continue;
        v.push_back(temp);
        dp[temp] = 1;
    }

   
    for(int i = 1 ; i <= k ; i ++){
        for(int j = 0 ; j < v.size(); j ++){
            if(i - v[j] >= 0){
                dp[i] = min(dp[i - v[j]] + 1,dp[i]);
            }
        }
    }
    if(dp[k] == 10001) cout<< -1;
    else cout<<dp[k];

}
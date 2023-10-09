#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n,k;
    vector<int> v;

    cin>>n>>k;
    int dp[k+1];
    for(int i = 0; i <=k ; i++) dp[i] = 0;
    
    for(int i = 0; i < n ; i++){
        int temp;
        cin>>temp;
        if(temp > k) continue;

        v.push_back(temp);

    }

    dp[0] = 1;
    for(int i = 0; i<v.size(); i++){
        for(int j = v[i] ; j <=k; j++){
            dp[j] += dp[j- v[i]];
        }
    }
    cout<<dp[k];
    return 0;
}
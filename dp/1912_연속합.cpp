#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    vector<int> v;
    cin>>n;
    int temp;
    int dp[n];
    for(int i = 0; i< n; i++){
        cin>>temp;
        v.push_back(temp);
    }
    dp[0] = v.front();
    int m = dp[0];
    for(int i = 1 ; i < v.size(); i++){
        dp[i] = max(dp[i-1] + v[i], v[i]);
        m = max(dp[i],m);
    }
    cout<<m;
    return 0;
}
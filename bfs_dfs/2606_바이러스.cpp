#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>


using namespace std;

int N,M;
bool network[101][101];
bool visited[101];

int findInfected(){
    int count = 0;
    stack<int> st;
    st.push(1);
    visited[1] = true;

    while(!st.empty()){
        int cur = st.top();
        st.pop();
        for(int i = 1;i<=N;i++){
            if(network[cur][i] && !visited[i]){
                st.push(i);
                visited[i] =true;
                count++;
            }
        }
    }
    return count;
}
int main(){
    cin>>N>>M;
    int a,b;

    for(int i = 0;i<M;i++){
        cin>>a>>b;
        network[a][b] =true;
        network[b][a] = true;
    }

    cout<<findInfected();
    return 0;
}
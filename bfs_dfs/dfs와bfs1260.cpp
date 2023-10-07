#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> graph[1001];
bool visited[1001];
int N,M,V;

void bfs(int start){
    queue<int> q;
    q.push(start);
    while(!q.empty()){
        int cur = q.front();
        cout<<cur<<" ";
        visited[cur] = true;
        q.pop();
        for(int i= 0 ;i<graph[cur].size();i++){
            int nextnode = graph[cur][i];
            if(!visited[nextnode]){
                q.push(nextnode);
                visited[nextnode] = true;
            }
        }
    }
    return;
}
void dfs(int start){
    if(visited[start]) return;
    cout<<start<<" ";
    visited[start] = true;
    for(int i = 0; i< graph[start].size();i++){
        if(!visited[graph[start][i]]){
            dfs(graph[start][i]);
        }
    }
    return;
}   
int main(){
    cin>>N>>M>>V;
    int a,b;
    for(int i= 0 ; i<M;i++){
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for(int i= 1; i<=N;i++){
        sort(graph[i].begin(),graph[i].end());
    }

    dfs(V);
    cout<<"\n";
    fill(visited,visited+1001,false);
    bfs(V);
    return 0;
}
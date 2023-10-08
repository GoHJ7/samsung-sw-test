#include <iostream>
#include <tuple>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

int N,W,V;
int M;

bool visited[101];
bool familyNet[101][101];

int findChon(int w,int v){
    queue<tuple<int,int>> q;
    q.push(make_tuple(w,0));
    visited[w] = true;

    while(!q.empty()){
        int cur,chon;
        tie(cur,chon) = q.front();
        q.pop();

        if(cur == v) return chon;

        for(int i= 1; i<=N; i++){
              if(familyNet[cur][i] && !visited[i]){
                q.push(make_tuple(i,chon+1));
                visited[i] = true;
              }
        }
    }
    return -1;
}

int main(){
    cin>>N>>W>>V>>M;
    
    int a,b;
    for(int i=0; i<M;i++){
        cin>>a>>b;
        familyNet[a][b] = true;
        familyNet[b][a]= true;
    }

    cout<<findChon(W,V);
    return 0;
}
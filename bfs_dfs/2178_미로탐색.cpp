#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <string>
using namespace std;


int N,M;
int maze[101][101];
bool visited[101][101];

bool isValid(int i , int j){
    if(i>=1 && j>=1 && i<=N && j <=M
    && !visited[i][j]
    && maze[i][j]){
        return true;
    }else{
        return false;
    }
}
void findway(){
    queue<tuple<int,int,int> > q;
    q.push(make_tuple(1,1,1));
    visited[1][1]=true;
    while(!q.empty()){
        //find adjacent
        tuple<int,int,int> cur;
        cur=q.front();
        int fc,sc,tc;
        fc = get<0>(cur);
        sc = get<1>(cur);
        tc = get<2>(cur);
        //cout<<fc<<sc<<tc<<endl;
        if(fc==N && sc == M){
            cout<<tc;
            return;
        }
        //right
        if(isValid(fc,sc+1) ){
            q.push(make_tuple(fc,sc+1,tc+1));
            visited[fc][sc+1] = true;
        }
        //down
        if(isValid(fc+1,sc) ){
            q.push(make_tuple(fc+1,sc,tc+1));
            visited[fc+1][sc] = true;
        }
        //up
        if(isValid(fc-1,sc)){
            q.push(make_tuple(fc-1,sc,tc+1));
            visited[fc-1][sc] =true;
        }
        //left
        if(isValid(fc,sc-1)){
            q.push(make_tuple(fc,sc-1,tc+1));
            visited[fc][sc-1] =true;
        }
        q.pop();
    }
}

int main(){
    cin>>N>>M;
    string temp;
    for(int i= 0;i<N;i++){
        cin>>temp;
        for(int j=0;j<M;j++){
            if(temp[j] == '1') maze[i+1][j+1] = 1;
            else maze[i+1][j+1] = 0;
        }
    }

    //start from 1,1
    findway();
    return 0;
}
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;

int subin, sister;
const int MAX = 100001;
bool visited[MAX];

/*
visited 처리하는거 까먹지 좀 말자
BFS의 핵심은 해당 목표지점의 최소 depth를 찾을 수 있다는 것 <- 최단 경로 문제

DFS는 모든 경로를 탐색하거나 경로 자체가 중요할때 사용,
또한 최단 경로 보장하지 않음.
*/

int findSister(){
    queue<tuple<int,int>> q;

    q.push(make_tuple(subin,0));

    while(!q.empty()){
        int cur_pos,cur_time;
        tie(cur_pos,cur_time) = q.front();
        q.pop();
        if(cur_pos == sister) return cur_time;

        if(cur_pos -1 >= 0 && !visited[cur_pos - 1]){
            q.push(make_tuple(cur_pos-1,cur_time + 1));
            visited[cur_pos - 1] = true;
        }
        if(cur_pos +1 < MAX && !visited[cur_pos +1 ]){
            q.push(make_tuple(cur_pos+1,cur_time + 1 ));
            visited[cur_pos + 1] = true;
        }
        if(cur_pos *2 < MAX && !visited[cur_pos *2 ]){
            q.push(make_tuple(cur_pos*2,cur_time + 1 ));
            visited[cur_pos * 2] = true;
        }
    }
}
int main(){
    cin>>subin>>sister;

    fill(visited,visited + MAX ,false);

    cout<<findSister();
    return 0;
}
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

int N;
int map[100][100];

bool isValid(int x,int y ,bool visited[100][100],int height){
    if(x >=0 && y >= 0 && x< N && y<N
    && !visited[x][y]
    && map[x][y]>height) return true;
    else return false;
}
void bfs(int i,int j, bool visited[100][100],int height){
    queue<tuple<int,int>> q;
    q.push(make_tuple(i,j));
    visited[i][j] = true;
    int dirX[4] = {1,-1,0,0};
    int dirY[4] = {0 ,0 ,1, -1};

    while(!q.empty()){
        int x,y;
        tie(x,y) = q.front();
        for(int i =0 ; i< 4; i++){
            if(isValid(x+dirX[i],y + dirY[i],visited,height)){
                q.push(make_tuple(x + dirX[i],y + dirY[i]));
                visited[x + dirX[i]][y + dirY[i]] = true;
            }
        }
        q.pop();
    }
}
int findSafeRegion(int height){
    bool visited[100][100];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            visited[i][j] = false;

    int count =0 ;
    while(true){
        
        for(int i= 0; i < N; i++){
            for(int j =0 ; j <N ; j++){
                if(map[i][j] > height && !visited[i][j]){
                    //bfs
                    //cout<<"find "<<i<<j<<height<<endl;
                    bfs(i,j, visited,height);
                    count++;
                    continue;
                }
            }
        }
        break;
    }
    return count;
}

int main(){
    cin>>N;
    int heighest = 0;
    for(int i =0 ; i < N; i++){
        for(int j= 0 ; j< N; j++){
            cin>>map[i][j];
            if(heighest < map[i][j]) heighest = map[i][j];
        }
    }

    priority_queue<int> pq;
    pq.push(1);
    for(int i = 1; i < heighest ; i++){
        pq.push(findSafeRegion(i));
    }
    cout<<pq.top();
    return 0;
}
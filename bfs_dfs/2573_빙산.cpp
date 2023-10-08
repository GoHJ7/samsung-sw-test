#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int N,M;
const int MAX = 300;
const int dirX[4] = {1,-1, 0, 0};
const int dirY[4] = {0,0,1,-1};

int map[MAX][MAX];

bool isInRange(int x, int y){
    if(x >= 0 && y >= 0 && x < N && y <M) return true;
    else return false;
}

void bfs(int x, int y,bool visited[MAX][MAX]){
    queue<tuple<int,int>> q;

    q.push(make_tuple(x,y));
    visited[x][y] = true;

    while(!q.empty()){
        int posX,posY;
        tie(posX,posY) = q.front();
        q.pop();
        for(int i =0 ; i <4; i++){
            if(isInRange(posX + dirX[i],posY + dirY[i]) 
            && map[posX + dirX[i]][posY + dirY[i]] != 0
            && !visited[posX + dirX[i]][posY + dirY[i]]){
                q.push(make_tuple(posX + dirX[i],posY + dirY[i]));
                visited[posX + dirX[i]][posY + dirY[i]] = true;
            }
        }
    }
}

bool isIcebergApart(){
    bool visited[MAX][MAX];
    for(int i = 0; i<N;i++)
        for(int j= 0; j <M ; j++)
            visited[i][j] = false;

    int startX = 0,startY = 0;
    for(int i = 0; i<N;i++){
        for(int j= 0; j <M ; j++){
            if(map[i][j] != 0){
                startX = i;
                startY = j;
                break;
            }
        }
    }
    bfs(startX,startY,visited);
    for(int i = 0; i<N;i++){
        for(int j= 0; j <M ; j++){
            if(map[i][j] != 0 && !visited[i][j]){
                return true;
            }
        }
    }
    return false;
}

void nextPhase(){
    int adjMap[N][M];
    for(int i = 0; i<N;i++){
        for(int j= 0; j <M ; j++){
            adjMap[i][j] = 0;
        }
    }
    for(int i = 0; i<N;i++){
        for(int j= 0; j <M ; j++){
            if(map[i][j] != 0){
                int adjacentWater = 0;
                for(int k = 0; k <4; k++){
                    if(isInRange(i+dirX[k],j+dirY[k]) && map[i+dirX[k]][j+dirY[k]] == 0) adjacentWater++;
                }
                adjMap[i][j] = adjacentWater;
            }
        }
    }
    for(int i = 0; i<N;i++){
        for(int j= 0; j <M ; j++){
            map[i][j] -= adjMap[i][j];
            if(map[i][j] < 0) map[i][j] = 0; 
        }
    } 
}
bool allMelt(){
    for(int i = 0; i<N;i++){
        for(int j= 0; j <M ; j++){
            if(map[i][j] != 0) return false;
        }
    } 
    return true;
}
int main(){
    cin>>N>>M;
    for(int i = 0; i<N;i++){
        for(int j= 0; j <M ; j++){
            cin>>map[i][j];
        }
    }

    int year = 0 ;
    while(!isIcebergApart() && !allMelt()){
        year++;
        nextPhase();
    }

    
    cout<<(allMelt() ? 0 : year);
    return 0;
}
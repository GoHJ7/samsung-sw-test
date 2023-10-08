#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

int N,M;
const int MAX =50;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dirX[4] = {-1,0,1,0};
int dirY[4] = {0,1,0,-1};

int cnt = 0;

void cleanUp(int x, int y,int dir){
    int initDir = dir;
   
    if(map[x][y]==0){
        visited[x][y] = true;
        map[x][y] = 2;
        cnt++;
    }

    for(int i =1; i <= 4; i++){
        int temp = dir - i;
        if(temp < 0 ) temp += 4;
        if(map[x + dirX[temp]][y + dirY[temp]] == 0){
            //cout<<"dir "<<temp<<endl;
            cleanUp(x + dirX[temp],y + dirY[temp],temp);
            return;
        }
    }

    if(map[x + dirX[(initDir +2)%4]][y + dirY[(initDir +2)%4]] == 2 ){
        //cout<<"후진"<<endl;
        cleanUp(x + dirX[(initDir +2)%4],y + dirY[(initDir +2)%4],initDir);
        return;
    }
}

int main(){
    cin>>N>>M;
    int startX,startY,dir;
    cin>>startX>>startY>>dir;

    for(int  i= 0; i<N;i++){
        for( int j = 0; j< M ; j++){
            cin>>map[i][j];
        }
    }
    cleanUp(startX,startY,dir);
    cout<<cnt;
    return 0;
}
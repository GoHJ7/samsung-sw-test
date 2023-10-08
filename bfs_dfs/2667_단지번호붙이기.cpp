#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>
using namespace std;


int N;

bool house[25][25];
bool visited[25][25];
int campusN = 0;
priority_queue<int,vector<int>,greater<int>> q;

bool isValid(int x, int y){
    if(x>=0 && y>=0 && x<N && y<N
    && !visited[x][y]
    && house[x][y]) return true;
    else return false;
}
void findCampus(int startX, int startY){
    //cout<<"findCampus called: " << startX << startY<<endl;
    queue<tuple<int,int>> bfs;
    
    int campusSize = 1;
    bfs.push(make_tuple(startX,startY));
    visited[startX][startY] = true;
    //up,down,left,right
    int dirX[4] = {0,0,-1,1};
    int dirY[4] = {-1,1,0,0};

    while(!bfs.empty()){
        int x,y;
        tie(x,y) = bfs.front();
        bfs.pop();
        for(int i= 0; i<4; i++){
            if(isValid(x+dirX[i],y+dirY[i])){
                campusSize++;
                bfs.push(make_tuple(x+dirX[i],y+dirY[i]));
                visited[x+dirX[i]][y+dirY[i]] = true;
            }
        }
    }
    q.push(campusSize);
    campusN++;
}

bool findNewCampus(){
    for(int i =0;i<N;i++){
        for(int j =0;j<N;j++){
            if(house[i][j] && !visited[i][j]){
                findCampus(i,j);
                return true;
            }
        }
    }
    return false;
}
int main(){
    cin>>N;
    string s;
    for(int i= 0; i<N;i++){
        cin>>s;
        for(int j=0;j<N;j++){
            if(s[j] == '1') house[i][j] = true;
        }
    }

    while(findNewCampus()){}

    cout<<campusN<<"\n";
    while(!q.empty()){
        cout<<q.top()<<"\n";
        q.pop();
    }
}
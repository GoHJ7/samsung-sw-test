#include <iostream>
#include <queue>
#include <stack>
#include <tuple>

using namespace std;
int N,M,H;
int box[101][101][101];

bool isValid(int i, int j, int k,int ripeDate){
    //범위 밖이면 false
    if(!(i>=1 && j >=1 && k >=1
    && i<=N && j<=M && k<=H)) return false;

    //0이면 true
    if(box[i][j][k]== 0) return true;
    if(box[i][j][k]== -1) return false;
    // -1이 아니고 0이 아니면서 해당 박스 값이 ripeDate보다 작으면 false 크면 true;
    if(box[i][j][k] != -1
    && box[i][j][k] != 0
    && (box[i][j][k] > ripeDate))  return true;

    return false; 
}

void riping(tuple<int,int,int> t){
    queue<tuple<int,int,int>> q;
    q.push(t);
    int dirX[6] = {1,-1,0,0,0,0};
    int dirY[6] = {0,0,1,-1,0,0};
    int dirZ[6] = {0,0,0,0,1,-1};
    
    while(!q.empty()){
        int i,j,k;
        tie(i,j,k) = q.front();
        q.pop();
    
        for(int d = 0; d<6; d++){
            if(isValid(i+dirX[d],j+dirY[d],k+dirZ[d],box[i][j][k] + 1)){
                q.push(make_tuple(i+dirX[d],j+dirY[d],k+dirZ[d]));
                box[i+dirX[d]][j+dirY[d]][k+dirZ[d]] = box[i][j][k] +1;
                
                
            }
        }
    }
}
int findMinRipingDate(){
    
    //notReachable -> -1
    for(int i= 1; i<=N;i++){
        for(int j =1 ; j<=M; j++){
            for(int k = 1; k <= H ; k++){
                if(box[i][j][k]== 0) return -1;
            }
        }
    }

    //cout<<"find maximum called"<<endl;
    priority_queue <int> q;
    // find maximum
    for(int i= 1; i<=N;i++){
        for(int j =1 ; j<=M; j++){
            for(int k = 1; k <= H ; k++){
                if(box[i][j][k] != -1) q.push(box[i][j][k] - 1);
            }
        }
    }
    return q.top();
}

int main(){
    cin>>N>>M>>H;
    queue<tuple<int,int,int>> q;
    for(int k= 1 ; k<=H; k++){
        for(int j= 1; j<=M;j++){
            for(int i =1;i<=N;i++){
                cin>>box[i][j][k];
                if(box[i][j][k] == 1) q.push(make_tuple(i,j,k));
            }
        }
    }

    while(!q.empty()){
        riping(q.front());
        q.pop();
    }

    cout<<findMinRipingDate();
    return 0;
}
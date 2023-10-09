#include <iostream>
#include <queue>

using namespace std;

class compare{
    public:
    bool operator()( const tuple<int,int,int>& a, const tuple<int,int,int>& b){
        if(get<0>(a) == get<0>(b) && get<1>(a) == get<1>(b)){
            return get<2>(a) < get<2>(b);
        }else if(get<0>(a) == get<0>(b) ){
            return get<1>(a) < get<1>(b);
        }else{
            return get<0>(a) < get<0>(b);
        }
    }
};

int N,M;
const int MAX = 500;
int map[MAX][MAX];
int dp[MAX][MAX];

bool isValid(int x, int y, int height){
    if(x >= 0 && y>=0 && x<N && y <M
    && map[x][y] > height) return true;
    else return false;
}

int main(){
    cin>>N>>M;
    dp[0][0] = 1;
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, compare> pq;
    int dirX[4] = {1,-1,0,0};
    int dirY[4] = {0,0,1,-1};

    for(int  i= 0; i<N; i++){
        for(int j = 0; j<M;j++){
            cin>>map[i][j];
            pq.push(make_tuple(map[i][j],i,j));
        }
    }

    while(!pq.empty()){
        int height,x,y;
        tie(height,x,y) = pq.top();
        pq.pop();
        cout<<"height x y "<<height <<x <<y<<endl;
        for(int i = 0; i < 4 ; i++){
            if(isValid(x + dirX[i],y + dirY[i],height)){
                dp[x][y] += dp[x +dirX[i]][y + dirY[i]];
            }
        }
    }

    cout<<dp[N-1][M-1];
}
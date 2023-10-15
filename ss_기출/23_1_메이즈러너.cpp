#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>

using namespace std;

const int N = 11;
int maze[N][N];
vector<pair<int,int>> participant;
pair<int,int> exitCor;
int dirX[5] = {-1,1,0,0,0};
int dirY[5] = {0,0,-1,1,0};
int n,m,k;
int totalMove = 0;

int getManDist(int x,int y,int _x,int _y){
    return abs(x-_x) + abs(y-_y);
}
bool isInrange(int x, int y){
    if(x > 0 && y > 0 && x <= n && y <= n 
    &&  maze[x][y] == 0) return true;
    else return false;
}

void move();
void rotate();

int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin>>n>>m>>k;

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            cin>>maze[i][j];
        }
    }
    for(int i = 0 ; i<m;i++){
        int r, c;
        cin>>r>>c;
        participant.push_back(make_pair(r,c));
    }
    cin>>exitCor.first>>exitCor.second;

    for(int i = 1 ; i <=k ; i++){
        //move
        
        move();
        if(participant.empty()) break;
        //rotate
        rotate();

        
    }
    cout<<totalMove<<endl;
    cout<<exitCor.first<<" "<<exitCor.second;
    return 0;
}

void move(){
    for(vector<pair<int,int>>:: iterator it = participant.begin(); it!= participant.end(); it++){
        int r, c;
        r = it->first;
        c = it->second;
        int curMin = getManDist(r,c,exitCor.first,exitCor.second);
        int curDir = 4;
        for(int i = 0 ; i < 4; i++){
            int mandist = getManDist(r + dirX[i],c + dirY[i],exitCor.first,exitCor.second);
            if((curMin > mandist) && isInrange(r+dirX[i],c+dirY[i])){
                curDir = i;
                curMin = mandist;
            }
        }
        
        if(curDir != 4){
            it->first = r + dirX[curDir];
            it->second =c + dirY[curDir];
            totalMove++;
        }
        
    }

    //pop out the exited
    for(vector<pair<int,int>>:: iterator it = participant.begin(); it!= participant.end();){
        if(it->first == exitCor.first && it->second == exitCor.second){
            //cout<<"pop out "<<it->first<<" "<<it->second<<endl;
            it = participant.erase(it);
        }else{
            it++;
        }
    }
}


bool isInqsquare(int r,int c,int length){
    for(int partN =0 ; partN < participant.size();partN++){
        int partr = participant[partN].first;
        int partc = participant[partN].second;

        if(partr >= r && partr < r + length
        && partc >= c && partc < c+ length){
            //cout<<"participant"<<participant[partN].first<<participant[partN].second<<endl;
            return true;
        }
    } 
    return false; 
}

bool rcIn(int x, int y){
    if(x>0 && y > 0 && x<= n && y <= n) return true;
    else return false;
}
void rotate(){
    //좌상단 rc,length

    //find min length
    int part = -1, length = 100;
    for(vector<pair<int,int>>:: iterator it = participant.begin(); it!= participant.end(); it++){
        int dx = abs(it->first - exitCor.first);
        int dy = abs(it->second - exitCor.second);

        if(length > max(dx,dy)){
            length = max(dx,dy);
        }
    }
    length++;
    int squarer,squarec;
    //find mins sqaure
    bool found = false;
    for(int _r = length - 1; _r >= 0 ; _r --){
        for(int _c = length - 1;_c >= 0; _c--){
            if(found) break;
            squarer = exitCor.first - _r;
            squarec = exitCor.second - _c;
            
            if(rcIn(squarer,squarec) && isInqsquare(squarer,squarec,length)) found = true;
            else continue;
        }
    }
    
    //rotate
    int rotated[length][length];
    int r = 0, c = 0;

    bool visited[participant.size()];
    memset(visited,false,sizeof(visited));
    bool exitvisited = false;
    for(int j = squarec ; j <squarec + length ; j++){
        for(int i = squarer + length - 1; i >= squarer; i--){
            if(exitCor.first == i && exitCor.second == j && !exitvisited){
                exitCor.first = r + squarer;
                exitCor.second = c + squarec;
                exitvisited = true;
                //cout<<"exitCor "<<exitCor.first<<" "<<exitCor.second<<endl;
            }
            
            for(int p = 0 ; p < participant.size();p++){
                if(participant[p].first == i && participant[p].second == j && !visited[p]){
                    //cout<<"회전 전 사람 "<<participant[p].first<<" "<<participant[p].second<<endl;
                    participant[p].first =  r+ squarer;
                    participant[p].second = c + squarec;
                    visited[p]=true;
                    //cout<<"회전 후 사람 "<<participant[p].first<<" "<<participant[p].second<<endl;
                }
             }
            rotated[r][c] = maze[i][j];
            c++;
        }
        r++;
        c= 0;
    }
    /*
    cout<<"rotatebox"<<endl;
    for(int  i= 0; i <length ; i++){
        for(int j = 0 ; j < length; j ++){
            cout<<rotated[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"mazebefore"<<endl;
    for(int i = 1 ; i <= n; i++){
        for(int j = 1 ; j <= n ; j++){
            cout<<maze[i][j]<<" ";
        }
        cout<<"\n";
    }
    */
    for(int i = 0 ; i < length; i++){
        for(int j = 0 ; j < length ; j++){
            if(rotated[i][j] >= 1) maze[squarer + i][squarec + j] = rotated[i][j] -1;
            else if(rotated[i][j] == 0) maze[squarer + i][squarec + j] = 0 ;
            else{
                cout<<"something wrong?"<<rotated[i][j]<<endl;
            }
        }
    }
    /*
    cout<<"maze"<<endl;
    for(int i = 1 ; i <= n; i++){
        for(int j = 1 ; j <= n ; j++){
            cout<<maze[i][j]<<" ";
        }
        cout<<"\n";
    }
    */
}